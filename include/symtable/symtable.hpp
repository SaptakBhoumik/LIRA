#include "ast/ast.hpp"
#include <unordered_map>

namespace LIRA {
namespace Utils{
// TODO: TypeSymTable and VarSymTable will be called really often along with ::clear_local_type. Right now I have one map to store all the table. It works but
// ::clear_local_type become O(N) cuz has to go throught the entire table. We can optimize it by having a separate map to store only the local types and variables 
// and then just clear that map when we need to clear local types and variables. But not the current priority
class TypeSymTable {
    std::string filename;
    std::unordered_map<IR::Token, IR::TypeExprPtr, IR::TokenValueHash, IR::TokenValueEqual> table = {};//TypeExprPtr is the reduced type expression after resolving typedefs. We reduce cuz we only want to concern about the final type structure and not the name
    std::vector<Diagnostic> errors = {};
    void error(IR::Token tok, std::string msg,std::string submsg="",std::string ecode="");
    public:
    TypeSymTable(std::string filename);
    void insert(IR::Token name, IR::TypeExprPtr type);//Expects u to run reduce_type_expr on the type before inserting it into the table. 
    IR::TypeExprPtr lookup(IR::TypeExprPtr name);//If it is a built in type then return it. If not found then error. Dont exit if error. Just add to errors. Return an AnyTypeExpr in case of error to avoid spamming follow up errors.
    IR::TypeExprPtr lookup(IR::Token name);//If it is a built in type then return it. If not found then error. Dont exit if error. Just add to errors. Return an AnyTypeExpr in case of error to avoid spamming follow up errors.
    bool contains(IR::Token name) const;//Check if the type is in the table (either built in or user defined)

    std::vector<Diagnostic> get_errors() const;
    void show_errors() const;//Dont exit
    void clear_local_type();//Clear all the types that are not defined in global scope. Useful when we go from one function to another because types defined in one function should not be visible in another. 
};

using TypeSymTablePtr = std::shared_ptr<TypeSymTable>;

class VarSymTable {
    std::string filename;
    std::unordered_map<IR::Token, IR::TypeExprPtr, IR::TokenValueHash, IR::TokenValueEqual> table = {};//Reduced type expr
    std::vector<Diagnostic> errors = {};
    void error(IR::Token tok, std::string msg,std::string submsg="",std::string ecode="");
    public:
    VarSymTable(std::string filename);
    void insert(IR::Token name, IR::TypeExprPtr type);//Expects u to run reduce_type_expr on the type before inserting it into the table.TODO: Make sure to add the ``labels``
    //lookup returns nulptr if the variable is builtin and doenst create error.TODO: Up to caler to determine how to handle it?
    IR::TypeExprPtr lookup(IR::ExprPtr name);//If not found then error. Dont exit if error. Just add to errors. Return an AnyTypeExpr in case of error to avoid spamming follow up errors.
    IR::TypeExprPtr lookup(IR::Token name);//If not found then error. Dont exit if error. Just add to errors. Return an AnyTypeExpr in case of error to avoid spamming follow up errors.
    bool exists(IR::ExprPtr name) const;//Check if the variable is in the table.
    bool exists(IR::Token name) const;//Check if the variable is in the table

    std::vector<Diagnostic> get_errors() const;
    void show_errors() const;//Dont exit
    void clear_local_vars();//Clear all the variables that are not defined in global scope. Useful when we go from one function to another because variables defined in one function should not be visible in another. 
};

using VarSymTablePtr = std::shared_ptr<VarSymTable>;

//TODO:Finish it
IR::TypeExprPtr reduce_type_expr(IR::TypeExprPtr type, TypeSymTablePtr symtable);//Recursively reduce a type expression by resolving typedefs until we get a non-typedef type expression. If we encounter a non-typedef type that is not built in then we error out.
}
}