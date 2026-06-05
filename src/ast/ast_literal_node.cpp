#include "ast/ast.hpp"
#include "lexer/token.hpp"

namespace LIRA {
namespace IR {
NamedLiteralExpr::NamedLiteralExpr(Token name){
    this->name = name;
}

Token NamedLiteralExpr::get_name() const{
    return this->name;
}

LiteralKind NamedLiteralExpr::get_kind() const{
    return LiteralKind::NamedLiteralExpr;
}
Token NamedLiteralExpr::get_token() const{
    return this->name;
}
std::string NamedLiteralExpr::to_string() const{
    return this->name.value;
}


StringLiteralExpr::StringLiteralExpr(Token value){
    this->value = value;
}

Token StringLiteralExpr::get_value() const{
    return this->value;
}

LiteralKind StringLiteralExpr::get_kind() const{
    return LiteralKind::StringLiteralExpr;
}
Token StringLiteralExpr::get_token() const{
    return this->value;
}
std::string StringLiteralExpr::to_string() const{
    return (this->value.type == TokenType::raw_string ? "r\"":"\"") + this->value.value + "\"";
}


NumLiteralExpr::NumLiteralExpr(Token value){
    this->value = value;
}

Token NumLiteralExpr::get_value() const{
    return this->value;
}

LiteralKind NumLiteralExpr::get_kind() const{
    return LiteralKind::NumLiteralExpr;
}
Token NumLiteralExpr::get_token() const{
    return this->value;
}
std::string NumLiteralExpr::to_string() const{
    return this->value.value;
}


ArrayLiteralExpr::ArrayLiteralExpr(Token tok, std::vector<LiteralExprPtr> elements){
    this->tok = tok;
    this->elements = elements;
}

std::vector<LiteralExprPtr> ArrayLiteralExpr::get_elements() const{
    return this->elements;
}

LiteralKind ArrayLiteralExpr::get_kind() const{
    return LiteralKind::ArrayLiteralExpr;
}
Token ArrayLiteralExpr::get_token() const{
    return this->tok;
}
std::string ArrayLiteralExpr::to_string() const{
    std::string res = "[";
    for(size_t i=0;i<this->elements.size();i++){
        res += this->elements[i]->to_string();
        if(i!=this->elements.size()-1) {
            res += ", ";
        }
    }
    return res+"]";
}


SIMDLiteralExpr::SIMDLiteralExpr(Token tok, std::vector<LiteralExprPtr> elements){
    this->tok = tok;
    this->elements = elements;
}

std::vector<LiteralExprPtr> SIMDLiteralExpr::get_elements() const{
    return this->elements;
}

LiteralKind SIMDLiteralExpr::get_kind() const{
    return LiteralKind::SIMDLiteralExpr;
}
Token SIMDLiteralExpr::get_token() const{
    return this->tok;
}
std::string SIMDLiteralExpr::to_string() const{
    std::string res = "<";
    for(size_t i=0;i<this->elements.size();i++){
        res += this->elements[i]->to_string();
        if(i!=this->elements.size()-1) {
            res += ", ";
        }
    }
    return res+">";
}


StructLiteralExpr::StructLiteralExpr(Token tok, std::vector<LiteralExprPtr> fields){
    this->tok = tok;
    this->fields = fields;
}

std::vector<LiteralExprPtr> StructLiteralExpr::get_fields() const{
    return this->fields;
}

LiteralKind StructLiteralExpr::get_kind() const{
    return LiteralKind::StructLiteralExpr;
}
Token StructLiteralExpr::get_token() const{
    return this->tok;
}
std::string StructLiteralExpr::to_string() const{
    std::string res = "{";
    for(size_t i=0;i<this->fields.size();i++){
        res += this->fields[i]->to_string();
        if(i!=this->fields.size()-1) {
            res += ", ";
        }
    }
    return res+"}";
}


NULLLiteralExpr::NULLLiteralExpr(Token tok){
    this->tok = tok;
}

Token NULLLiteralExpr::get_token() const{
    return this->tok;
}
LiteralKind NULLLiteralExpr::get_kind() const{
    return LiteralKind::NULLLiteralExpr;
}
std::string NULLLiteralExpr::to_string() const{
    return "null";
}


ZeroInitLiteralExpr::ZeroInitLiteralExpr(Token tok){
    this->tok = tok;
}

Token ZeroInitLiteralExpr::get_token() const{
    return this->tok;
}
LiteralKind ZeroInitLiteralExpr::get_kind() const{
    return LiteralKind::ZeroInitLiteralExpr;
}
std::string ZeroInitLiteralExpr::to_string() const{
    return "zeroinitializer";
}


PoisonLiteralExpr::PoisonLiteralExpr(Token tok){
    this->tok = tok;
}

Token PoisonLiteralExpr::get_token() const{
    return this->tok;
}
LiteralKind PoisonLiteralExpr::get_kind() const{
    return LiteralKind::PoisonLiteralExpr;
}
std::string PoisonLiteralExpr::to_string() const{
    return "poison";
}
}
}