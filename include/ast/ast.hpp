#pragma once
#include "lexer/token.hpp"
#include "lexer/lexer.hpp"
#include "error/error.hpp"
#include <cstddef>
#include <cstdint>
#include <memory>
#include <optional>
namespace LIRA {
namespace IR{
template<typename T1, typename T2, typename T3>
struct triplet{
    T1 first;
    T2 second;
    T3 third;
    triplet(T1 first, T2 second, T3 third): first(first), second(second), third(third){}
};

class DebugInfo{
    Token tok;//the '!' token for error reporting
    Token file_name;//A string literal
    Token line;//A number literal
    Token column;//A number literal
    public:
    DebugInfo(Token tok, Token file_name, Token line, Token column);

    Token get_file_name() const;
    Token get_line() const;
    Token get_column() const;

    Token get_token() const;
    std::string to_string() const;
};
using DebugInfoPtr = std::shared_ptr<DebugInfo>;

class Expr;
using ExprPtr = std::shared_ptr<Expr>;
class TypeExpr;
using TypeExprPtr = std::shared_ptr<TypeExpr>;

class Attribute{
    //#[name(type:arg1, type:arg2, ... )] or #[name(kwarg1=type:value1, kwarg2=type:value2, ...)] 
    Token tok;//The # token for error reporting
    Token name;
    //The args are supposed to be const literal anyways
    std::vector<std::pair<ExprPtr,TypeExprPtr>> args;
    std::vector<triplet<Token,ExprPtr,TypeExprPtr>> kwargs;//Expects constant literal tokens as values and constant identtifier token as keys
    public:
    Attribute(Token tok, Token name, std::vector<std::pair<ExprPtr,TypeExprPtr>> args, std::vector<triplet<Token,ExprPtr,TypeExprPtr>> kwargs);

    Token get_name() const;
    std::vector<std::pair<ExprPtr,TypeExprPtr>> get_args() const;
    std::vector<triplet<Token,ExprPtr,TypeExprPtr>> get_kwargs() const;
    Token get_token() const;
    std::string to_string() const;
};

using AttributePtr = std::shared_ptr<Attribute>;

enum class TypeExprKind:std::uint8_t{
    NamedTypeExpr, // Stuff like %name,$name
    IntTypeExpr,
    FloatTypeExpr,
    VoidTypeExpr,
    PtrTypeExpr,    
    MetaTypeExpr,
    ArrayTypeExpr,
    SIMDTypeExpr,
    StructTypeExpr,
    FuncTypeExpr,
    LabelTypeExpr,
    ScopeTypeExpr,
    AnyTypeExpr //For internal use. This is used in places where we want to allow any type expression. 
                //Used when there is type error and we want to avoid spamming the error messages with follow up errors caused by the first error due to dependent types
                //Described in https://claude.ai/share/d6bf9b6d-1a2b-4d4b-bd82-7ad6bd3ba813
};
class TypeExpr{
    public:
    virtual TypeExprKind get_kind() const = 0;
    virtual Token get_token() const = 0;
    virtual std::vector<AttributePtr> get_attributes() const = 0;
    virtual std::string to_string() const = 0;
    //TODO:Implement the following
    //virtual bool contains_metatype() const = 0;//If the base type is of type 'type'. We need this to make sure people dont do something like {type,type} 
                                               //or fn(type)->type which are not valid type expressions 
                                               //Only NamedTypeExpr can contain the metatype. 
                                               //We first reduce the types(Because people can typedef) then we check this condition and give error if it is violated
                                               //

    virtual ~TypeExpr() = default;
};

using TypeExprPtr = std::shared_ptr<TypeExpr>;
class NamedTypeExpr : public TypeExpr{
    //name #[attributes]
    Token name;
    std::vector<AttributePtr> attributes;
    public:
    NamedTypeExpr(Token name, std::vector<AttributePtr> attributes);

    Token get_name() const;

    TypeExprKind get_kind() const override;
    Token get_token() const override;
    std::vector<AttributePtr> get_attributes() const override;
    std::string to_string() const override;
};

class IntTypeExpr : public TypeExpr{
    //iN #[attributes]
    Token tok;//the iN token for error reporting
    std::size_t bits;//The N in iN
    std::vector<AttributePtr> attributes;
    public:
    IntTypeExpr(Token tok,std::size_t bits, std::vector<AttributePtr> attributes);

    std::size_t get_bits() const;

    Token get_token() const override;
    TypeExprKind get_kind() const override;
    std::vector<AttributePtr> get_attributes() const override;
    std::string to_string() const override;
};

class FloatTypeExpr : public TypeExpr{
    //fN #[attributes]
    Token tok;//the fN token for error reporting
    bool brain_float;//If bf16
    std::size_t bits;//The N in fN
    std::vector<AttributePtr> attributes;
    public:
    FloatTypeExpr(Token tok,std::size_t bits,bool brain_float, std::vector<AttributePtr> attributes);

    std::size_t get_bits() const;
    bool is_brain_float() const;

    Token get_token() const override;
    TypeExprKind get_kind() const override;
    std::vector<AttributePtr> get_attributes() const override;
    std::string to_string() const override;
};

class VoidTypeExpr : public TypeExpr{
    //void #[attributes]
    Token tok;//the void token for error reporting
    std::vector<AttributePtr> attributes;
    public:
    VoidTypeExpr(Token tok, std::vector<AttributePtr> attributes);

    Token get_token() const override;
    TypeExprKind get_kind() const override;
    std::vector<AttributePtr> get_attributes() const override;
    std::string to_string() const override;
};

class PtrTypeExpr : public TypeExpr{
    //ptr #[attributes]
    Token tok;//the 'ptr' token for error reporting
    std::vector<AttributePtr> attributes;
    public:
    PtrTypeExpr(Token tok, std::vector<AttributePtr> attributes);


    Token get_token() const override;
    TypeExprKind get_kind() const override;
    std::vector<AttributePtr> get_attributes() const override;
    std::string to_string() const override;
};

class MetaTypeExpr : public TypeExpr{
    //type #[attributes]
    Token tok;//the 'type' token for error reporting
    std::vector<AttributePtr> attributes;
    public:
    MetaTypeExpr(Token tok, std::vector<AttributePtr> attributes);

    Token get_token() const override;
    TypeExprKind get_kind() const override;
    std::vector<AttributePtr> get_attributes() const override;
    std::string to_string() const override;
};

class ArrayTypeExpr : public TypeExpr{
    //[type,size] #[attributes]
    Token tok;//the '[' token for error reporting
    std::vector<AttributePtr> attributes;
    
    TypeExprPtr base_type;
    Token size;
    public:
    ArrayTypeExpr(Token tok, TypeExprPtr base_type, Token size, std::vector<AttributePtr> attributes);

    TypeExprPtr get_basetype() const;
    Token get_size() const;
    
    TypeExprKind get_kind() const override;
    Token get_token() const override;
    std::vector<AttributePtr> get_attributes() const override;
    std::string to_string() const override;
};

class SIMDTypeExpr : public TypeExpr{
    // <type,size> #[attributes]
    Token tok;//the '[' token for error reporting
    std::vector<AttributePtr> attributes;
    
    TypeExprPtr base_type;
    Token size;
    public:
    SIMDTypeExpr(Token tok, TypeExprPtr base_type, Token size, std::vector<AttributePtr> attributes);

    TypeExprPtr get_basetype() const;
    Token get_size() const;

    TypeExprKind get_kind() const override;
    Token get_token() const override;
    std::vector<AttributePtr> get_attributes() const override;
    std::string to_string() const override;
};


class StructTypeExpr : public TypeExpr{
    //{field1:type, field2:type, ... } #[attributes]
    Token tok;//the '{' token for error reporting
    std::vector<AttributePtr> attributes;

    std::vector<TypeExprPtr> fields;
    bool packed = false;
    public:
    StructTypeExpr(Token tok, std::vector<TypeExprPtr> fields, bool packed, std::vector<AttributePtr> attributes);

    std::vector<TypeExprPtr> get_fields() const;
    bool is_packed() const;

    TypeExprKind get_kind() const override;
    Token get_token() const override;
    std::vector<AttributePtr> get_attributes() const override;
    std::string to_string() const override;
};

class FuncTypeExpr : public TypeExpr{
    //fn(type1, type2, ... ) -> return_type #[attributes]
    Token tok;//the 'fn' token for error reporting
    std::vector<AttributePtr> attributes;

    std::vector<TypeExprPtr> param_types;
    bool varargs;//whether the function has a ... varargs at the end.
    TypeExprPtr return_type;
    public:
    FuncTypeExpr(Token tok, std::vector<TypeExprPtr> param_types, bool varargs, TypeExprPtr return_type, std::vector<AttributePtr> attributes);

    std::vector<TypeExprPtr> get_param_types() const;
    bool has_varargs() const;
    TypeExprPtr get_return_type() const;

    TypeExprKind get_kind() const override;
    Token get_token() const override;
    std::vector<AttributePtr> get_attributes() const override;
    std::string to_string() const override;
};

class LabelTypeExpr : public TypeExpr{
    //label(type, type, ... )
    Token tok;//the 'label' token for error reporting
    std::vector<AttributePtr> attributes;//Label type has no attribute but we still store it for giving error messages during type checking
    std::vector<TypeExprPtr> params;
    public:
    LabelTypeExpr(Token tok, std::vector<TypeExprPtr> params, std::vector<AttributePtr> attributes);

    std::vector<TypeExprPtr> get_params() const;

    TypeExprKind get_kind() const override;
    Token get_token() const override;
    std::vector<AttributePtr> get_attributes() const override;
    std::string to_string() const override;
};

class ScopeTypeExpr : public TypeExpr{
    //scope
    Token tok;//the 'scope' token for error reporting
    public:
    ScopeTypeExpr(Token tok);

    TypeExprKind get_kind() const override;
    Token get_token() const override;
    std::vector<AttributePtr> get_attributes() const override;
    std::string to_string() const override;
};

class AnyTypeExpr : public TypeExpr{
    //Satisfies every type constrants
    //For internal use. This is used in places where we want to allow any type expression. 
    //Used when there is type error and we want to avoid spamming the error messages with follow up errors caused by the first error due to dependent types
    //Described in https://claude.ai/share/d6bf9b6d-1a2b-4d4b-bd82-7ad6bd3ba813
    TypeExprPtr original_type;//The original type expression that we wanted to use before we encountered the error and had to fall back to using AnyTypeExpr to avoid spamming follow up errors. 
    public:
    AnyTypeExpr(TypeExprPtr original_type);

    TypeExprPtr get_original_type() const;

    TypeExprKind get_kind() const override;
    Token get_token() const override;
    std::vector<AttributePtr> get_attributes() const override;
    std::string to_string() const override;
};
enum class LiteralKind:std::uint8_t{
    NamedLiteralExpr, // Stuff like name,%name,$name
    StringLiteralExpr,
    NumLiteralExpr,
    ArrayLiteralExpr,
    SIMDLiteralExpr,
    StructLiteralExpr,
    NULLLiteralExpr,
    ZeroInitLiteralExpr,
    PoisonLiteralExpr,
};
class LiteralExpr{
    public:
    virtual LiteralKind get_kind() const = 0;
    virtual Token get_token() const = 0;
    virtual std::string to_string() const = 0;

    virtual ~LiteralExpr() = default;
};

using LiteralExprPtr = std::shared_ptr<LiteralExpr>;

class NamedLiteralExpr : public LiteralExpr{
    //name 
    Token name;
    public:
    NamedLiteralExpr(Token name);

    Token get_name() const;

    LiteralKind get_kind() const override;
    Token get_token() const override;
    std::string to_string() const override;
};
class StringLiteralExpr : public LiteralExpr{
    Token value;//the string literal token for error reporting
    public:
    StringLiteralExpr(Token value);

    Token get_value() const;

    LiteralKind get_kind() const override;
    Token get_token() const override;
    std::string to_string() const override;
};
class NumLiteralExpr : public LiteralExpr{
    Token value;//the number literal token for error reporting
    public:
    NumLiteralExpr(Token value);

    Token get_value() const;

    LiteralKind get_kind() const override;
    Token get_token() const override;
    std::string to_string() const override;
};
class ArrayLiteralExpr : public LiteralExpr{
    //[elem1, elem2, ... ]
    Token tok;//the '[' token for error reporting
    std::vector<LiteralExprPtr> elements;
    public:
    ArrayLiteralExpr(Token tok, std::vector<LiteralExprPtr> elements);

    std::vector<LiteralExprPtr> get_elements() const;

    LiteralKind get_kind() const override;
    Token get_token() const override;
    std::string to_string() const override;
};
class SIMDLiteralExpr : public LiteralExpr{
    //<elem1, elem2, ... >
    Token tok;//the '<' token for error reporting
    std::vector<LiteralExprPtr> elements;
    public:
    SIMDLiteralExpr(Token tok, std::vector<LiteralExprPtr> elements);

    std::vector<LiteralExprPtr> get_elements() const;

    LiteralKind get_kind() const override;
    Token get_token() const override;
    std::string to_string() const override;
};

class StructLiteralExpr : public LiteralExpr{
    //{value1, value2, ... }
    Token tok;//the '{' token for error reporting
    std::vector<LiteralExprPtr> fields;
    public:
    StructLiteralExpr(Token tok, std::vector<LiteralExprPtr> fields);

    std::vector<LiteralExprPtr> get_fields() const;

    LiteralKind get_kind() const override;
    Token get_token() const override;
    std::string to_string() const override;
};

class NULLLiteralExpr : public LiteralExpr{
    //null
    Token tok;//the 'null' token for error reporting
    public:
    NULLLiteralExpr(Token tok);

    Token get_token() const override;
    LiteralKind get_kind() const override;
    std::string to_string() const override;
};

class ZeroInitLiteralExpr : public LiteralExpr{
    //zeroinitializer
    Token tok;//the 'zeroinitializer' token for error reporting
    public:
    ZeroInitLiteralExpr(Token tok);

    Token get_token() const override;
    LiteralKind get_kind() const override;
    std::string to_string() const override;
};

class PoisonLiteralExpr : public LiteralExpr{
    //poison
    Token tok;//the 'poison' token for error reporting
    public:
    PoisonLiteralExpr(Token tok);

    Token get_token() const override;
    LiteralKind get_kind() const override;
    std::string to_string() const override;
};

enum class ExprKind:std::uint8_t{
    LiteralExpr,
    TypeExpr,
};

class Expr{
    LiteralExprPtr literal = nullptr;//null if it is not a literal expression
    TypeExprPtr type = nullptr;//null if it is not a type expression
    public:
    Expr(LiteralExprPtr literal);
    Expr(TypeExprPtr type);

    ExprKind get_kind() const;
    LiteralExprPtr get_literal() const;
    TypeExprPtr get_type() const;
    std::string to_string() const;
};

using ExprPtr = std::shared_ptr<Expr>;

class InstructionStmt{
    public:
        class InstructionCall{
            //instruction(type:arg1,type:arg2, ... ) #[attr1] #[attr2] ! 'main.c':10:5
            Token tok;//the instruction identifier token for error reporting+For identifying the instruction being called
            std::vector<std::pair<ExprPtr,TypeExprPtr>> operands;
            /*
            If you want to do ``a=1.2`` then do ``a = .assign_value(f32:1.2)`` and done. This keeps the parser simpler and language uniform
            In case u are wondering why I cant check if the token after ``=`` is instruction. Because if I check then no need of ``.assign_value``
            I mean technically I can check but no need to overcomplicate
            */
            std::vector<AttributePtr> attributes;
            DebugInfoPtr debug_info = nullptr; //COmes after attributes
        public:
            InstructionCall(Token tok, std::vector<std::pair<ExprPtr,TypeExprPtr>> operands, std::vector<AttributePtr> attributes, DebugInfoPtr debug_info);

            Token get_token() const;
            std::vector<std::pair<ExprPtr,TypeExprPtr>> get_operands() const;
            std::vector<AttributePtr> get_attributes() const;
            DebugInfoPtr get_debug_info() const;
            std::string to_string() const;
        };
    private:
    //let type:$name #[attr1] #[attr2]= ...
    Token tok;//the 'let'/instruction token for error reporting
    std::optional<triplet<Token, std::vector<AttributePtr>, TypeExprPtr>> name;//Empty if we dont assign the InstructionCall statement to a variable

    std::optional<InstructionCall> value;//Empty if it is just a declaration without initialization. Do let type:type = .assign_value(type:<4 x i32>) if u want type def
    public:
    InstructionStmt(Token tok, std::optional<triplet<Token, std::vector<AttributePtr>, TypeExprPtr>> name, std::optional<InstructionCall> value);

    std::optional<triplet<Token, std::vector<AttributePtr>, TypeExprPtr>> get_name() const;
    std::optional<InstructionCall> get_value() const;
    Token get_token() const;
    std::string to_string() const;
};  

using InstructionStmtPtr = std::shared_ptr<InstructionStmt>;

class Label {
    /*
    @loop{
        ...
    }
    */
    Token tok;//The 'label' token for error reporting
    Token name;//The ``@name`` token for error reporting and identifying the label. Note that the value of this token includes the @ prefix (e.g. @loop)
    std::vector<triplet<Token, std::vector<AttributePtr>, TypeExprPtr>> params;
    std::vector<InstructionStmtPtr> statements;
    public:
    Label(Token tok, Token name, std::vector<InstructionStmtPtr> statements, std::vector<triplet<Token, std::vector<AttributePtr>, TypeExprPtr>> params);

    Token get_name() const;
    Token get_token() const;
    std::vector<InstructionStmtPtr> get_statements() const;
    std::vector<triplet<Token, std::vector<AttributePtr>, TypeExprPtr>> get_params() const;
    std::string to_string() const;
};

using LabelPtr = std::shared_ptr<Label>;

enum class ScopeType:std::uint8_t{
    FunctionScope,
    BlockScope,
    InlineScope
};
class Scope {
    Token tok;//The 'scope' token for error reporting

    ScopeType scope_type;
    std::optional<Token> scope_name;
    Token scope_var_name;//The variable that stores the scope.
    std::optional<Token> parent_scope_name;//Empty if it is a function scope.
    std::optional<triplet<Token,Token,Token>> scope_loc;// <'main.c', '10', '5'> for error reporting. Empty if not available
    std::optional<triplet<Token,Token,Token>> callsite_loc;// Only for InlineScope. Else std::nullopt
    public:
    Scope(Token tok, ScopeType scope_type, std::optional<Token> scope_name, Token scope_var_name, std::optional<Token> parent_scope_name, 
            std::optional<triplet<Token,Token,Token>> scope_loc, std::optional<triplet<Token,Token,Token>> callsite_loc);

    ScopeType get_scope_type() const;
    std::optional<Token> get_scope_name() const;
    Token get_scope_var_name() const;
    std::optional<Token> get_parent_scope_name() const;
    std::optional<triplet<Token,Token,Token>> get_scope_loc() const;
    std::optional<triplet<Token,Token,Token>> get_callsite_loc() const;
    Token get_token() const;
    std::string to_string() const;
};

using ScopePtr = std::shared_ptr<Scope>;
// class 
class Function {
    /*
    fn #[attr1] #[attr2] name(let type:param1,let type #[attr_of_type]:param2 #[attr_of_param2], ...) -> return_type ! 'main.c':10:5 {
        ...
    }
    */
    Token tok;//The ``fn`` token for error reporting
    Token name;//The function name token for error reporting and identifying the function
    std::vector<AttributePtr> attributes;
    std::vector<triplet<Token, std::vector<AttributePtr>, TypeExprPtr>> params;
    bool varargs;//whether the function has a ... varargs at the end.
    TypeExprPtr return_type;
    DebugInfoPtr debug_info = nullptr;
    std::vector<ScopePtr> scopes;
    std::vector<LabelPtr> body;//Empty if it is just a function declaration without a body. A function declaration with body must have atleast one label
                               //The first label is the entry point

    public:
    Function(Token tok, Token name, std::vector<AttributePtr> attributes, std::vector<triplet<Token, std::vector<AttributePtr>, TypeExprPtr>> params, 
             bool varargs, TypeExprPtr return_type, DebugInfoPtr debug_info, std::vector<ScopePtr> scopes, std::vector<LabelPtr> body);

    Token get_name() const;
    std::vector<AttributePtr> get_attributes() const;
    std::vector<triplet<Token, std::vector<AttributePtr>, TypeExprPtr>> get_params() const;
    bool has_varargs() const;
    TypeExprPtr get_return_type() const;
    DebugInfoPtr get_debug_info() const;
    std::vector<ScopePtr> get_scopes() const;
    std::vector<LabelPtr> get_body() const;
    Token get_token() const;
    std::string to_string() const;
};

using FunctionPtr = std::shared_ptr<Function>;

enum class GlobalItemKind:std::uint8_t{
    FunctionKind,
    GlobalAttributeKind,
    GlobalVarKind,
};


class GlobalItem{
    FunctionPtr function = nullptr;//null if it is not a function
    AttributePtr attribute = nullptr;//null if it is not a global attribute
    InstructionStmtPtr global_var = nullptr;//null if it is not a global variable
    public:
    GlobalItem(FunctionPtr function);
    GlobalItem(AttributePtr attribute);
    GlobalItem(InstructionStmtPtr global_var);

    FunctionPtr get_function() const;
    AttributePtr get_attribute() const;
    InstructionStmtPtr get_global_var() const;
    GlobalItemKind get_kind() const;
    std::string to_string() const;
};

using GlobalItemPtr = std::shared_ptr<GlobalItem>;
class Program{
    std::vector<GlobalItemPtr> items;
    public:
    Program(std::vector<GlobalItemPtr> items);

    std::vector<GlobalItemPtr> get_items() const;
    std::string to_string() const;
};

using ProgramPtr = std::shared_ptr<Program>;
}
}