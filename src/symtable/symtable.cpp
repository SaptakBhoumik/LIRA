#include "symtable/symtable.hpp"
#include "ast/ast.hpp"
#include <cstddef>
#include <iostream>
#include <unordered_set>

namespace LIRA {
namespace Utils {
[[noreturn]] void TypeSymTable::error(IR::Token tok, std::string msg,std::string submsg,std::string ecode) const{
    Location loc{tok.line, tok.col, this->filename, tok.source_line};
    Diagnostic err = {loc,
                   std::string(msg),
                   submsg,
                   ecode,
        };
    display(err);
    exit(1);
}
TypeSymTable::TypeSymTable(std::string filename){
    this->filename = filename;
}
void TypeSymTable::insert(IR::Token name, IR::TypeExprPtr type) {
    if(contains(name)) {
        error(name, "Type redefinition error", "The type '"+name.value+"' is already defined");
        // this->table[name] = std::make_shared<IR::AnyTypeExpr>(type);
        // return;
    }
    this->table[name] = type;
}
IR::TypeExprPtr TypeSymTable::lookup(IR::TypeExprPtr name) const{
    if(name->get_kind() == IR::TypeExprKind::NamedTypeExpr) {
        auto named_type = std::dynamic_pointer_cast<IR::NamedTypeExpr>(name);
        return lookup(named_type->get_name());
    }
    else{
        std::cout << "This should have never happened. We should only be looking up named type expressions in the type symtable. Report issue to the developers." << std::endl;
        exit(1);
    }
}
IR::TypeExprPtr TypeSymTable::lookup(IR::Token name) const{
    auto it = this->table.find(name);
    if(it == this->table.end()) {
        error(name, "Undefined type error", "The type '"+name.value+"' is not defined");
        // return std::make_shared<IR::AnyTypeExpr>(std::make_shared<IR::NamedTypeExpr>(name, std::vector<IR::AttributePtr>{}));//Return an AnyTypeExpr to avoid spamming follow up errors
    }
    return it->second;
}
bool TypeSymTable::contains(IR::Token name) const{
    return this->table.find(name) != this->table.end();
}

void TypeSymTable::clear_local_type() {
    std::unordered_map<IR::Token, IR::TypeExprPtr, IR::TokenValueHash, IR::TokenValueEqual> new_table = {};
    for(const auto& pair : this->table) {
        if(pair.first.type == IR::TokenType::global_identifier) {
            new_table[pair.first] = pair.second;
        }
    }
    this->table = new_table;
}


void VarSymTable::error(IR::Token tok, std::string msg,std::string submsg,std::string ecode) const{
    Location loc{tok.line, tok.col, this->filename, tok.source_line};
    Diagnostic err = {loc,
                   std::string(msg),
                   submsg,
                   ecode,
        };
    display(err);
    exit(1);
}
VarSymTable::VarSymTable(std::string filename){
    this->filename = filename;
}
void VarSymTable::insert(IR::Token name, IR::TypeExprPtr type) {
    if(exists(name)) {
        error(name, "Variable redefinition error", "The variable '"+name.value+"' is already defined in this scope");
        // this->table[name] = std::make_shared<IR::AnyTypeExpr>(type);
        // return;
    }
    this->table[name] = type;
}
IR::TypeExprPtr VarSymTable::lookup(IR::ExprPtr name) const{
    if(name->get_kind() == IR::ExprKind::LiteralExpr) {
        auto named_lit = name->get_literal();
        if(named_lit->get_kind() != IR::LiteralKind::NamedLiteralExpr) {
            std::cout << "This should have never happened. We should only be looking up named literal expressions in the variable symtable. Report issue to the developers." << std::endl;
            exit(1);
        }
        auto named_lit_casted = std::dynamic_pointer_cast<IR::NamedLiteralExpr>(named_lit);
        return lookup(named_lit_casted->get_name());
    }
    else{
        auto named_type = name->get_type();
        if(named_type->get_kind() != IR::TypeExprKind::NamedTypeExpr) {
            std::cout << "This should have never happened. We should only be looking up named type expressions in the variable symtable. Report issue to the developers." << std::endl;
            exit(1);
        }
        auto named_type_casted = std::dynamic_pointer_cast<IR::NamedTypeExpr>(named_type);
        return lookup(named_type_casted->get_name());
    }
}
IR::TypeExprPtr VarSymTable::lookup(IR::Token name) const{
    //TODO:What if builtin name? Decide later how to handle that
    if(name.type == IR::TokenType::builtin_identifier) {
        return nullptr;
    }
    auto it = this->table.find(name);
    if(it == this->table.end()) {
        error(name, "Undefined variable error", "The variable '"+name.value+"' is not defined in this scope");
        // name.value = "type of "+name.value;
        // return std::make_shared<IR::AnyTypeExpr>(std::make_shared<IR::NamedTypeExpr>(name, std::vector<IR::AttributePtr>{}));
    }
    return it->second;
}

bool VarSymTable::exists(IR::ExprPtr name) const{
    if(name->get_kind() == IR::ExprKind::LiteralExpr) {
        auto named_lit = name->get_literal();
        if(named_lit->get_kind() != IR::LiteralKind::NamedLiteralExpr) {
            return false;
        }
        auto named_lit_casted = std::dynamic_pointer_cast<IR::NamedLiteralExpr>(named_lit);
        return exists(named_lit_casted->get_name());
    }
    else{
        auto named_type = name->get_type();
        if(named_type->get_kind() != IR::TypeExprKind::NamedTypeExpr) {
            return false;
        }
        auto named_type_casted = std::dynamic_pointer_cast<IR::NamedTypeExpr>(named_type);
        return exists(named_type_casted->get_name());
    }
}
bool VarSymTable::exists(IR::Token name) const{
    if(name.type == IR::TokenType::builtin_identifier) {
        //TODO: Check if the built identifier exists or not. For now we assume it does exist
        return true;
    }
    return this->table.find(name) != this->table.end();
}

void VarSymTable::clear_local_vars() {
    std::unordered_map<IR::Token, IR::TypeExprPtr, IR::TokenValueHash, IR::TokenValueEqual> new_table = {};
    for(const auto& pair : this->table) {
        if(pair.first.type == IR::TokenType::global_identifier) {
            new_table[pair.first] = pair.second;
        }
    }
    this->table = new_table;
}
}
}