#include "ast/ast.hpp"

namespace LIRA {
namespace IR {
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
    std::string res = this->name.value;
    for(const auto& attr: this->attributes){
        res += " "+attr->to_string();
    }
    if(!this->attributes.empty()) {
        res = "("+res+")";
    }
    return res;
}


IntTypeExpr::IntTypeExpr(Token tok,std::size_t bits, std::vector<AttributePtr> attributes){
    this->tok = tok;
    this->bits = bits;
    this->attributes = attributes;
}

std::size_t IntTypeExpr::get_bits() const{
    return this->bits;
}

TypeExprKind IntTypeExpr::get_kind() const{
    return TypeExprKind::IntTypeExpr;
}
Token IntTypeExpr::get_token() const{
    return this->tok;
}
std::vector<AttributePtr> IntTypeExpr::get_attributes() const{
    return this->attributes;
}
std::string IntTypeExpr::to_string() const{
    std::string res = this->tok.value;
    for(const auto& attr: this->attributes){
        res += " "+attr->to_string();
    }
    if(!this->attributes.empty()) {
        res = "("+res+")";
    }
    return res;
}


FloatTypeExpr::FloatTypeExpr(Token tok,std::size_t bits,bool brain_float, std::vector<AttributePtr> attributes){
    this->tok = tok;
    this->bits = bits;
    this->brain_float = brain_float;
    this->attributes = attributes;
}
std::size_t FloatTypeExpr::get_bits() const{
    return this->bits;
}
bool FloatTypeExpr::is_brain_float() const{
    return this->brain_float;
}
TypeExprKind FloatTypeExpr::get_kind() const{
    return TypeExprKind::FloatTypeExpr;
}
Token FloatTypeExpr::get_token() const{
    return this->tok;
}
std::vector<AttributePtr> FloatTypeExpr::get_attributes() const{
    return this->attributes;
}
std::string FloatTypeExpr::to_string() const{
    std::string res = this->tok.value;
    for(const auto& attr: this->attributes){
        res += " "+attr->to_string();
    }
    if(!this->attributes.empty()) {
        res = "("+res+")";
    }
    return res;
}


VoidTypeExpr::VoidTypeExpr(Token tok, std::vector<AttributePtr> attributes){
    this->tok = tok;
    this->attributes = attributes;
}

TypeExprKind VoidTypeExpr::get_kind() const{
    return TypeExprKind::VoidTypeExpr;
}
Token VoidTypeExpr::get_token() const{
    return this->tok;
}
std::vector<AttributePtr> VoidTypeExpr::get_attributes() const{
    return this->attributes;
}
std::string VoidTypeExpr::to_string() const{
    std::string res = "void";
    for(const auto& attr: this->attributes){
        res += " "+attr->to_string();
    }
    if(!this->attributes.empty()) {
        res = "("+res+")";
    }
    return res;
}


PtrTypeExpr::PtrTypeExpr(Token tok, std::vector<AttributePtr> attributes){
    this->tok = tok;
    this->attributes = attributes;
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
    std::string res = "ptr";
    for(const auto& attr: this->attributes){
        res += " "+attr->to_string();
    }
    if(!this->attributes.empty()) {
        res = "("+res+")";
    }
    return res;
}


MetaTypeExpr::MetaTypeExpr(Token tok, std::vector<AttributePtr> attributes){
    this->tok = tok;
    this->attributes = attributes;
}

TypeExprKind MetaTypeExpr::get_kind() const{
    return TypeExprKind::MetaTypeExpr;
}
Token MetaTypeExpr::get_token() const{
    return this->tok;
}
std::vector<AttributePtr> MetaTypeExpr::get_attributes() const{
    return this->attributes;
}
std::string MetaTypeExpr::to_string() const{
    std::string res = "type";
    for(const auto& attr: this->attributes){
        res += " "+attr->to_string();
    }
    if(!this->attributes.empty()) {
        res = "("+res+")";
    }
    return res;
}


ArrayTypeExpr::ArrayTypeExpr(Token tok, TypeExprPtr base_type, Token size, std::vector<AttributePtr> attributes){
    this->tok = tok;
    this->base_type = base_type;
    this->size = size;
    this->attributes = attributes;
}

TypeExprPtr ArrayTypeExpr::get_basetype() const{
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
    std::string res = "[" + this->base_type->to_string() + "," + this->size.value + "]";
    for(const auto& attr: this->attributes){
        res += " "+attr->to_string();
    }
    if(!this->attributes.empty()) {
        res = "("+res+")";
    }
    return res;
}


SIMDTypeExpr::SIMDTypeExpr(Token tok, TypeExprPtr base_type, Token size, std::vector<AttributePtr> attributes){
    this->tok = tok;
    this->base_type = base_type;
    this->size = size;
    this->attributes = attributes;
}

TypeExprPtr SIMDTypeExpr::get_basetype() const{
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
    std::string res = "<" + this->size.value + " x " + this->base_type->to_string() + ">";
    for(const auto& attr: this->attributes){
        res += " "+attr->to_string();
    }
    if(!this->attributes.empty()) {
        res = "("+res+")";
    }
    return res;
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
        res = "<{";
    } 
    else {
        res = "{"; 
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
    if(!this->attributes.empty()) {
        res = "("+res+")";
    }
    return res;
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
    std::string res = "fn(";
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
    if(!this->attributes.empty()) {
        res = "("+res+")";
    }
    return res;
}


LabelTypeExpr::LabelTypeExpr(Token tok, std::vector<TypeExprPtr> params, std::vector<AttributePtr> attributes){
    this->tok = tok;
    this->params = params;
    this->attributes = attributes;
}

std::vector<TypeExprPtr> LabelTypeExpr::get_params() const{
    return this->params;
}

std::vector<AttributePtr> LabelTypeExpr::get_attributes() const{
    return this->attributes;
}

TypeExprKind LabelTypeExpr::get_kind() const{
    return TypeExprKind::LabelTypeExpr;
}
Token LabelTypeExpr::get_token() const{
    return this->tok;
}
std::string LabelTypeExpr::to_string() const{
    std::string res = "label(";
    for(size_t i=0;i<this->params.size();i++){
        res += this->params[i]->to_string();
        if(i!=this->params.size()-1) {
            res += ", ";
        }
    }
    res += ")";
    for(const auto& attr: this->attributes){
        res += " "+attr->to_string();
    }
    if(!this->attributes.empty()) {
        res = "("+res+")";
    }
    return res;
}


ScopeTypeExpr::ScopeTypeExpr(Token tok){
    this->tok = tok;
}

TypeExprKind ScopeTypeExpr::get_kind() const{
    return TypeExprKind::ScopeTypeExpr;
}
Token ScopeTypeExpr::get_token() const{
    return this->tok;
}
std::vector<AttributePtr> ScopeTypeExpr::get_attributes() const{
    return {};
}
std::string ScopeTypeExpr::to_string() const{
    return "scope";
}
}
}