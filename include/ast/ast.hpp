#pragma once
#include "lexer/token.hpp"
#include "lexer/lexer.hpp"
#include "error/error.hpp"
#include <cstdint>
#include <memory>
#include <optional>
namespace LIRA {
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

class Attribute{
    //#[name(arg1, arg2, ... )] or #[name(kwarg1=value1, kwarg2=value2, ...)] 
    Token tok;//The # token for error reporting
    Token name;
    //The args are supposed to be const literal anyways
    std::vector<Token> args;
    std::vector<std::pair<Token,Token>> kwargs;//Expects constant literal tokens as values and constant identtifier token as keys
    public:
    Attribute(Token tok, Token name, std::vector<Token> args, std::vector<std::pair<Token,Token>> kwargs);

    Token get_name() const;
    std::vector<Token> get_args() const;
    std::vector<std::pair<Token,Token>> get_kwargs() const;

    Token get_token() const;
    std::string to_string() const;
};

using AttributePtr = std::shared_ptr<Attribute>;

enum class TypeExprKind:std::uint8_t{
    NamedTypeExpr, // Stuff like i8,i32,%name,$name
    ArrayTypeExpr,
    SIMDTypeExpr,
    PtrTypeExpr,
    StructTypeExpr,
    FuncTypeExpr,
};
class TypeExpr{
    public:
    virtual TypeExprKind get_kind() const = 0;
    virtual Token get_token() const = 0;
    virtual std::vector<AttributePtr> get_attributes() const = 0;
    virtual std::string to_string() const = 0;

    virtual ~TypeExpr() = default;
};

using TypeExprPtr = std::shared_ptr<TypeExpr>;
//TODO:Make sure to support ``(`` and ``)`` for grouping in type expressions. Although thing to be noted is that these parentheses are just for grouping 
// and dont actually become part of the type expression tree. So for example ``(i32)`` is just a NamedTypeExpr with name i32 and not some new ParenTypeExpr or 
// something. This is similar to how in arithmetic expressions ``(1 + 2)`` is just a BinaryExpr with operator + and left operand 1 and right operand 2 and not
// some new ParenExpr or something. This makes the parser simpler and also makes the AST simpler without unnecessary nodes while allowing you to represent complex stuff
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

class ArrayTypeExpr : public TypeExpr{
    //[size x type] #[attributes]
    Token tok;//the '[' token for error reporting
    std::vector<AttributePtr> attributes;
    
    TypeExprPtr base_type;
    Token size;
    public:
    ArrayTypeExpr(Token tok, TypeExprPtr base_type, Token size, std::vector<AttributePtr> attributes);

    TypeExprPtr get_base_type() const;
    Token get_size() const;
    
    TypeExprKind get_kind() const override;
    Token get_token() const override;
    std::vector<AttributePtr> get_attributes() const override;
    std::string to_string() const override;
};

class SIMDTypeExpr : public TypeExpr{
    // <size x type> #[attributes]
    Token tok;//the '[' token for error reporting
    std::vector<AttributePtr> attributes;
    
    TypeExprPtr base_type;
    Token size;
    public:
    SIMDTypeExpr(Token tok, TypeExprPtr base_type, Token size, std::vector<AttributePtr> attributes);

    TypeExprPtr get_base_type() const;
    Token get_size() const;

    TypeExprKind get_kind() const override;
    Token get_token() const override;
    std::vector<AttributePtr> get_attributes() const override;
    std::string to_string() const override;
};

class PtrTypeExpr : public TypeExpr{
    //*type #[attributes]
    //While parsing makse sure it dont become *(type #[attributes])
    Token tok;//the '*' token for error reporting
    std::vector<AttributePtr> attributes;
    
    TypeExprPtr base_type;
    public:
    PtrTypeExpr(Token tok, TypeExprPtr base_type, std::vector<AttributePtr> attributes);

    TypeExprPtr get_base_type() const;

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


enum class LiteralKind:std::uint8_t{
    NamedLiteralExpr, // Stuff like name,%name,$name
    StringLiteralExpr,
    NumLiteralExpr,
    ArrayLiteralExpr,
    SIMDLiteralExpr,
    StructLiteralExpr,
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
    //name #[attributes]
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
            If you want to do ``a=1.2`` then do ``a = .copy(f32:1.2)`` and done. This keeps the parser simpler and language uniform
            In case u are wondering why I cant check if the token after ``=`` is instruction. Because if I check then no need of ``.copy``
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

    std::optional<InstructionCall> value;//Empty if it is just a declaration without initialization. Do let type:type = .copy(type:<4 x i32>) if u want type def
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
    Token name;//The ``@name`` token for error reporting and identifying the label. Note that the value of this token includes the @ prefix (e.g. @loop)
    std::vector<InstructionStmtPtr> statements;
    public:
    Label(Token name, std::vector<InstructionStmtPtr> statements);

    Token get_name() const;
    std::vector<InstructionStmtPtr> get_statements() const;
    std::string to_string() const;
};

using LabelPtr = std::shared_ptr<Label>;

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
    std::optional<std::vector<LabelPtr>> body;//Empty if it is just a function declaration without a body

    public:
    Function(Token tok, Token name, std::vector<AttributePtr> attributes, std::vector<triplet<Token, std::vector<AttributePtr>, TypeExprPtr>> params, 
             bool varargs, TypeExprPtr return_type, DebugInfoPtr debug_info, std::optional<std::vector<LabelPtr>> body);

    Token get_name() const;
    std::vector<AttributePtr> get_attributes() const;
    std::vector<triplet<Token, std::vector<AttributePtr>, TypeExprPtr>> get_params() const;
    bool has_varargs() const;
    TypeExprPtr get_return_type() const;
    DebugInfoPtr get_debug_info() const;
    std::optional<std::vector<LabelPtr>> get_body() const;
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

class Program{
    std::vector<GlobalItem> items;
    public:
    Program(std::vector<GlobalItem> items);

    std::vector<GlobalItem> get_items() const;
    std::string to_string() const;
};
}