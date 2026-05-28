#include "ast/ast.hpp"

namespace LIRA {
NamedTypeExpr::NamedTypeExpr(Token name, std::vector<AttributePtr> attributes){
    this->name = name;
    this->attributes = attributes;
}

Token NamedTypeExpr::get_name() const{
    return this->name;
}

TypeExprKind NamedTypeExpr::get_kind() const{
    return TypeExprKind::NamedTypeExpr;
}
Token NamedTypeExpr::get_token() const{
    return this->name;
}
std::vector<AttributePtr> NamedTypeExpr::get_attributes() const{
    return this->attributes;
}
std::string NamedTypeExpr::to_string() const{
    std::string res = "(" + this->name.value;
    for(const auto& attr: this->attributes){
        res += " "+attr->to_string();
    }
    return res + ")";
}


ArrayTypeExpr::ArrayTypeExpr(Token tok, TypeExprPtr base_type, Token size, std::vector<AttributePtr> attributes){
    this->tok = tok;
    this->base_type = base_type;
    this->size = size;
    this->attributes = attributes;
}

TypeExprPtr ArrayTypeExpr::get_base_type() const{
    return this->base_type;
}
Token ArrayTypeExpr::get_size() const{
    return this->size;
}

TypeExprKind ArrayTypeExpr::get_kind() const{
    return TypeExprKind::ArrayTypeExpr;
}
Token ArrayTypeExpr::get_token() const{
    return this->tok;
}
std::vector<AttributePtr> ArrayTypeExpr::get_attributes() const{
    return this->attributes;
}
std::string ArrayTypeExpr::to_string() const{
    std::string res = "([" + this->base_type->to_string() + "," + this->size.value + "]";
    for(const auto& attr: this->attributes){
        res += " "+attr->to_string();
    }
    return res+")";
}


SIMDTypeExpr::SIMDTypeExpr(Token tok, TypeExprPtr base_type, Token size, std::vector<AttributePtr> attributes){
    this->tok = tok;
    this->base_type = base_type;
    this->size = size;
    this->attributes = attributes;
}

TypeExprPtr SIMDTypeExpr::get_base_type() const{
    return this->base_type;
}
Token SIMDTypeExpr::get_size() const{
    return this->size;
}

TypeExprKind SIMDTypeExpr::get_kind() const{
    return TypeExprKind::SIMDTypeExpr;
}
Token SIMDTypeExpr::get_token() const{
    return this->tok;
}
std::vector<AttributePtr> SIMDTypeExpr::get_attributes() const{
    return this->attributes;
}
std::string SIMDTypeExpr::to_string() const{
    std::string res = "(<" + this->size.value + " x " + this->base_type->to_string() + ">";
    for(const auto& attr: this->attributes){
        res += " "+attr->to_string();
    }
    return res+")";
}


PtrTypeExpr::PtrTypeExpr(Token tok, TypeExprPtr base_type, std::vector<AttributePtr> attributes){
    this->tok = tok;
    this->base_type = base_type;
    this->attributes = attributes;
}

TypeExprPtr PtrTypeExpr::get_base_type() const{
    return this->base_type;
}

TypeExprKind PtrTypeExpr::get_kind() const{
    return TypeExprKind::PtrTypeExpr;
}
Token PtrTypeExpr::get_token() const{
    return this->tok;
}
std::vector<AttributePtr> PtrTypeExpr::get_attributes() const{
    return this->attributes;
}
std::string PtrTypeExpr::to_string() const{
    std::string res = "(*" + this->base_type->to_string();
    for(const auto& attr: this->attributes){
        res += " "+attr->to_string();
    }
    return res+")";
}


StructTypeExpr::StructTypeExpr(Token tok, std::vector<TypeExprPtr> fields, bool packed, std::vector<AttributePtr> attributes){
    this->tok = tok;
    this->fields = fields;
    this->packed = packed;
    this->attributes = attributes;
}

std::vector<TypeExprPtr> StructTypeExpr::get_fields() const{
    return this->fields;
}

bool StructTypeExpr::is_packed() const{
    return this->packed;
}

TypeExprKind StructTypeExpr::get_kind() const{
    return TypeExprKind::StructTypeExpr;
}
Token StructTypeExpr::get_token() const{
    return this->tok;
}
std::vector<AttributePtr> StructTypeExpr::get_attributes() const{
    return this->attributes;
}
std::string StructTypeExpr::to_string() const{
    std::string res;
    if(this->packed) {
        res = "(<{";
    } 
    else {
        res = "({"; 
    }
    for(size_t i=0;i<this->fields.size();i++){
        res += this->fields[i]->to_string();
        if(i!=this->fields.size()-1) {
            res += ", ";
        }
    }
    if(this->packed) {
        res += "}>"; 
    } 
    else {
        res += "}"; 
    }
    for(const auto& attr: this->attributes){
        res += " "+attr->to_string();
    }
    return res+")";
}


FuncTypeExpr::FuncTypeExpr(Token tok, std::vector<TypeExprPtr> param_types, bool varargs, TypeExprPtr return_type, std::vector<AttributePtr> attributes){
    this->tok = tok;
    this->param_types = param_types;
    this->varargs = varargs;
    this->return_type = return_type;
    this->attributes = attributes;
}

std::vector<TypeExprPtr> FuncTypeExpr::get_param_types() const{
    return this->param_types;
}
bool FuncTypeExpr::has_varargs() const{
    return this->varargs;
}
TypeExprPtr FuncTypeExpr::get_return_type() const{
    return this->return_type;
}

TypeExprKind FuncTypeExpr::get_kind() const{
    return TypeExprKind::FuncTypeExpr;
}
Token FuncTypeExpr::get_token() const{
    return this->tok;
}
std::vector<AttributePtr> FuncTypeExpr::get_attributes() const{
    return this->attributes;
}
std::string FuncTypeExpr::to_string() const{
    std::string res = "(fn(";
    for(size_t i=0;i<this->param_types.size();i++){
        res += this->param_types[i]->to_string();
        if(i!=this->param_types.size()-1) {
            res += ", ";
        }
    }
    if(this->varargs) {
        if(!this->param_types.empty()) {
            res += ", ";
        }
        res += "...";
    }
    res += ") -> " + this->return_type->to_string();
    for(const auto& attr: this->attributes){
        res += " "+attr->to_string();
    }
    return res+")";
}
}