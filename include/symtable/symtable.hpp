#pragma once
#include "ast/ast.hpp"
#include <unordered_map>

namespace LIRA {
namespace Utils{
// TODO: TypeSymTable and VarSymTable will be called really often along with ::clear_local_type. Right now I have one map to store all the table. It works but
// ::clear_local_type become O(N) cuz has to go throught the entire table. We can optimize it by having a separate map to store only the local types and variables 
// and then just clear that map when we need to clear local types and variables. But not the current priority
class TypeSymTable {
    std::string filename;
    //Note:-We only check the equality of the token value. Not the location and stuff
    std::unordered_map<IR::Token, IR::TypeExprPtr, IR::TokenValueHash, IR::TokenValueEqual> table = {};//TypeExprPtr is the reduced type expression after resolving typedefs. We reduce cuz we only want to concern about the final type structure and not the name
    [[noreturn]] void error(IR::Token tok, std::string msg,std::string submsg="",std::string ecode="") const;
    public:
    TypeSymTable(std::string filename);
    void insert(IR::Token name, IR::TypeExprPtr type);//Expects u to run reduce_type_expr on the type before inserting it into the table. 
    IR::TypeExprPtr lookup(IR::TypeExprPtr name) const;//If it is a built in type then return it. If not found then error. 
    IR::TypeExprPtr lookup(IR::Token name) const;//If it is a built in type then return it. If not found then error. 
    bool contains(IR::Token name) const;//Check if the type is in the table (either built in or user defined)

    void clear_local_type();
};

using TypeSymTablePtr = std::shared_ptr<TypeSymTable>;

class VarSymTable {
    std::string filename;
    //Note:-We only check the equality of the token value. Not the location and stuff
    std::unordered_map<IR::Token, IR::TypeExprPtr, IR::TokenValueHash, IR::TokenValueEqual> table = {};//Reduced type expr
    [[noreturn]] void error(IR::Token tok, std::string msg,std::string submsg="",std::string ecode="") const;
    public:
    VarSymTable(std::string filename);
    void insert(IR::Token name, IR::TypeExprPtr type);//Expects u to run reduce_type_expr on the type before inserting it into the table.TODO: Make sure to add the ``labels``
    void update(IR::Token name, IR::TypeExprPtr type);//Updates the type of the variable in the table. Expects u to run reduce_type_expr on the type before inserting it into the table. If not found then error. 
    //lookup returns nulptr if the variable is builtin and doenst create error.TODO: Up to caler to determine how to handle it?
    IR::TypeExprPtr lookup(IR::ExprPtr name) const;//If not found then error. 
    IR::TypeExprPtr lookup(IR::Token name) const;//If not found then error. 
    bool exists(IR::ExprPtr name) const;//Check if the variable is in the table.
    bool exists(IR::Token name) const;//Check if the variable is in the table

    void clear_local_vars();//Clear all the variables that are not defined in global scope. Useful when we go from one function to another because variables defined in one function should not be visible in another. 
};

using VarSymTablePtr = std::shared_ptr<VarSymTable>;
}
}