#include "symtable/symtable.hpp"
#include "ast/ast.hpp"
#include <cstddef>
#include <iostream>
#include <unordered_set>

namespace LIRA {
void TypeSymTable::error(Token tok, std::string msg,std::string submsg,std::string ecode){
    Location loc{tok.line, tok.col, this->filename, tok.source_line};
    Diagnostic err = {loc,
                   std::string(msg),
                   submsg,
                   ecode,
        };
    this->errors.push_back(err);
}
TypeSymTable::TypeSymTable(std::string filename){
    this->filename = filename;
}
void TypeSymTable::insert(Token name, TypeExprPtr type) {
    if(contains(name)) {
        error(name, "Type redefinition error", "The type '"+name.value+"' is already defined");
        this->table[name] = std::make_shared<AnyTypeExpr>(type);
        return;
    }
    this->table[name] = type;
}
TypeExprPtr TypeSymTable::lookup(TypeExprPtr name) {
    if(is_builtin(name)) {
        return name;
    }
    if(name->get_kind() == TypeExprKind::NamedTypeExpr) {
        auto named_type = std::dynamic_pointer_cast<NamedTypeExpr>(name);
        return lookup(named_type->get_name());
    }
    else{
        std::cout << "This should have never happened. We should only be looking up named type expressions in the type symtable. Report issue to the developers." << std::endl;
        exit(1);
    }
}
TypeExprPtr TypeSymTable::lookup(Token name) {
    if(is_builtin(name)) {
        return std::make_shared<NamedTypeExpr>(name, std::vector<AttributePtr>{});
    }
    auto it = this->table.find(name);
    if(it == this->table.end()) {
        error(name, "Undefined type error", "The type '"+name.value+"' is not defined");
        return std::make_shared<AnyTypeExpr>(std::make_shared<NamedTypeExpr>(name, std::vector<AttributePtr>{}));//Return an AnyTypeExpr to avoid spamming follow up errors
    }
    return it->second;
}
bool TypeSymTable::is_builtin(TypeExprPtr type) const {
    if(type->get_kind() != TypeExprKind::NamedTypeExpr) {
        return false;
    }
    auto named_type = std::dynamic_pointer_cast<NamedTypeExpr>(type);
    return is_builtin(named_type->get_name());
}
bool TypeSymTable::is_builtin(Token type) const {
    if(type.type != TokenType::builtin_identifier) {
        return false;
    }
    if(type.value[0] == 'i') {//We support iN just like llvm
        //Remove the i and see if rest is a power of 2
        std::string num_str = type.value.substr(1);
        try {
            std::size_t num = std::stoull(num_str);
            return (num & (num - 1)) == 0 && num > 0;//Check if num is a power of 2
        }
        catch(...) {
            return false;
        }
    }

    /*
    half:- f16
    bfloat16:- bf16
    float:- f32
    double:- f64
    x86_fp80:- f80
    fp128:- f128
    ppc_fp128:- ppc_f128
    */
    static std::unordered_set<std::string> builtin_types = {"f16","bf16","f32","f64", "f80","f128","ppc_f128",
                                                            "void","ptr","str","type"};
    return builtin_types.find(type.value) != builtin_types.end();
}
bool TypeSymTable::contains(Token name) const {
    return is_builtin(name) || this->table.find(name) != this->table.end();
}

std::vector<Diagnostic> TypeSymTable::get_errors() const{
    return this->errors;
}
void TypeSymTable::show_errors() const{
    for(const auto& error : this->errors) {
        display(error);
    }
}

void TypeSymTable::clear_local_type() {
    std::unordered_map<Token, TypeExprPtr, TokenValueHash, TokenValueEqual> new_table = {};
    for(const auto& pair : this->table) {
        if(pair.first.type == TokenType::global_identifier) {
            new_table[pair.first] = pair.second;
        }
    }
    this->table = new_table;
}



void VarSymTable::error(Token tok, std::string msg,std::string submsg,std::string ecode){
    Location loc{tok.line, tok.col, this->filename, tok.source_line};
    Diagnostic err = {loc,
                   std::string(msg),
                   submsg,
                   ecode,
        };
    this->errors.push_back(err);
}
VarSymTable::VarSymTable(std::string filename){
    this->filename = filename;
}
void VarSymTable::insert(Token name, TypeExprPtr type) {
    if(exists(name)) {
        error(name, "Variable redefinition error", "The variable '"+name.value+"' is already defined in this scope");
        this->table[name] = std::make_shared<AnyTypeExpr>(type);
        return;
    }
    this->table[name] = type;
}
TypeExprPtr VarSymTable::lookup(ExprPtr name){
    if(name->get_kind() == ExprKind::LiteralExpr) {
        auto named_lit = name->get_literal();
        if(named_lit->get_kind() != LiteralKind::NamedLiteralExpr) {
            std::cout << "This should have never happened. We should only be looking up named literal expressions in the variable symtable. Report issue to the developers." << std::endl;
            exit(1);
        }
        auto named_lit_casted = std::dynamic_pointer_cast<NamedLiteralExpr>(named_lit);
        return lookup(named_lit_casted->get_name());
    }
    else{
        auto named_type = name->get_type();
        if(named_type->get_kind() != TypeExprKind::NamedTypeExpr) {
            std::cout << "This should have never happened. We should only be looking up named type expressions in the variable symtable. Report issue to the developers." << std::endl;
            exit(1);
        }
        auto named_type_casted = std::dynamic_pointer_cast<NamedTypeExpr>(named_type);
        return lookup(named_type_casted->get_name());
    }
}
TypeExprPtr VarSymTable::lookup(Token name) {
    //TODO:What if builtin name? Decide later how to handle that
    if(name.type == TokenType::builtin_identifier) {
        return nullptr;
    }
    auto it = this->table.find(name);
    if(it == this->table.end()) {
        error(name, "Undefined variable error", "The variable '"+name.value+"' is not defined in this scope");
        name.value = "type of "+name.value;
        return std::make_shared<AnyTypeExpr>(std::make_shared<NamedTypeExpr>(name, std::vector<AttributePtr>{}));
    }
    return it->second;
}

bool VarSymTable::exists(ExprPtr name) const{
    if(name->get_kind() == ExprKind::LiteralExpr) {
        auto named_lit = name->get_literal();
        if(named_lit->get_kind() != LiteralKind::NamedLiteralExpr) {
            return false;
        }
        auto named_lit_casted = std::dynamic_pointer_cast<NamedLiteralExpr>(named_lit);
        return exists(named_lit_casted->get_name());
    }
    else{
        auto named_type = name->get_type();
        if(named_type->get_kind() != TypeExprKind::NamedTypeExpr) {
            return false;
        }
        auto named_type_casted = std::dynamic_pointer_cast<NamedTypeExpr>(named_type);
        return exists(named_type_casted->get_name());
    }
}
bool VarSymTable::exists(Token name) const{
    if(name.type == TokenType::builtin_identifier) {
        //TODO: Check if the built identifier exists or not. For now we assume it does exist
        return true;
    }
    return this->table.find(name) != this->table.end();
}

std::vector<Diagnostic> VarSymTable::get_errors() const{
    return this->errors;
}
void VarSymTable::show_errors() const{//Dont exit
    for(const auto& err : this->errors) {
        display(err);
    }
}
void VarSymTable::clear_local_vars() {
    std::unordered_map<Token, TypeExprPtr, TokenValueHash, TokenValueEqual> new_table = {};
    for(const auto& pair : this->table) {
        if(pair.first.type == TokenType::global_identifier) {
            new_table[pair.first] = pair.second;
        }
    }
    this->table = new_table;
}
}