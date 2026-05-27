#include "ast/ast.hpp"

namespace LIRA {
DebugInfo::DebugInfo(Token tok, Token file_name, Token line, Token column){
    this->tok = tok;
    this->file_name = file_name;
    this->line = line;
    this->column = column;
}

Token DebugInfo::get_file_name() const{
    return this->file_name;
}

Token DebugInfo::get_line() const{
    return this->line;
}

Token DebugInfo::get_column() const{
    return this->column;
}

Token DebugInfo::get_token() const{
    return this->tok;
}
std::string DebugInfo::to_string() const{
    return "\""+this->file_name.value+"\":"+this->line.value+":"+this->column.value;
}


Attribute::Attribute(Token tok, Token name, std::vector<Token> args, std::vector<std::pair<Token,Token>> kwargs){
    this->tok = tok;
    this->name = name;
    this->args = args;
    this->kwargs = kwargs;
}

Token Attribute::get_name() const{
    return this->name;
}
std::vector<Token> Attribute::get_args() const{
    return this->args;
}
std::vector<std::pair<Token,Token>> Attribute::get_kwargs() const{
    return this->kwargs;
}

Token Attribute::get_token() const{
    return this->tok;
}
std::string Attribute::to_string() const{
    std::string res = "#["+this->name.value;
    res += "(";
    for(size_t i=0;i<this->args.size();i++){
        res += this->args[i].value;
        if(i!=this->args.size()-1) { 
            res += ", ";
        }
    }
    for(size_t i=0;i<this->kwargs.size();i++){
        res += this->kwargs[i].first.value+"="+this->kwargs[i].second.value;
        if(i!=this->kwargs.size()-1) {
            res += ", ";
        }
    }
    res += ")]";
    return res;
}


Expr::Expr(LiteralExprPtr literal){
    if(literal == nullptr) {
        throw std::invalid_argument("LiteralExprPtr cannot be null");
    }
    this->literal = literal;
    this->type = nullptr;
}
Expr::Expr(TypeExprPtr type){
    if(type == nullptr) {
        throw std::invalid_argument("TypeExprPtr cannot be null");
    }
    this->type = type;
    this->literal = nullptr;
}

ExprKind Expr::get_kind() const{
    if(literal!=nullptr) {
        return ExprKind::LiteralExpr;
    } 
    else {
        return ExprKind::TypeExpr;
    }
}
LiteralExprPtr Expr::get_literal() const{
    return literal;
}
TypeExprPtr Expr::get_type() const{
    return type;
}
std::string Expr::to_string() const{
    if(literal!=nullptr) {
        return literal->to_string();
    } 
    else {
        return type->to_string();
    }
}


InstructionStmt::InstructionCall::InstructionCall(Token tok, std::vector<std::pair<ExprPtr,TypeExprPtr>> operands, std::vector<AttributePtr> attributes, DebugInfoPtr debug_info){
    this->tok = tok;
    this->operands = operands;
    this->attributes = attributes;
    this->debug_info = debug_info;
}

Token InstructionStmt::InstructionCall::get_token() const{
    return tok;
}
std::vector<std::pair<ExprPtr,TypeExprPtr>> InstructionStmt::InstructionCall::get_operands() const{
    return operands;
}
std::vector<AttributePtr> InstructionStmt::InstructionCall::get_attributes() const{
    return attributes;
}
DebugInfoPtr InstructionStmt::InstructionCall::get_debug_info() const{
    return debug_info;
}
std::string InstructionStmt::InstructionCall::to_string() const{
    std::string res = tok.value+"(";
    for(size_t i=0;i<operands.size();i++){
        res += operands[i].first->to_string()+":"+operands[i].second->to_string();
        if(i!=operands.size()-1) {
            res += ", ";
        }
    }
    res += ")";
    for(const auto& attr: attributes){
        res += " "+attr->to_string();
    }
    if(debug_info!=nullptr) {
        res += " ! "+debug_info->to_string();
    }
    return res;
}



InstructionStmt::InstructionStmt(Token tok, std::optional<triplet<Token, std::vector<AttributePtr>, TypeExprPtr>> name,std::optional<InstructionCall> value){
    this->tok = tok;
    this->name = name;
    this->value = value;
}

std::optional<triplet<Token, std::vector<AttributePtr>, TypeExprPtr>> InstructionStmt::get_name() const{
    return name;
}
std::optional<InstructionStmt::InstructionCall> InstructionStmt::get_value() const{
    return value;
}
Token InstructionStmt::get_token() const{
    return tok;
}
std::string InstructionStmt::to_string() const{
    std::string res;
    if(name.has_value()) {
        res = "let " + name->third->to_string() + ":" + name->first.value;
        for(const auto& attr: name->second){
            res += " "+attr->to_string();
        }
        if(value.has_value()) {
            res += " = ";
        }
    }
    if(value.has_value()) {
        res += value->to_string();
    }
    return res;
}



Label::Label(Token name, std::vector<InstructionStmtPtr> statements){
    this->name = name;
    this->statements = statements;
}

Token Label::get_name() const{
    return name;
}
std::vector<InstructionStmtPtr> Label::get_statements() const{
    return statements;
}

std::string Label::to_string() const{
    std::string res = "\t" + name.value + "{\n";
    for(const auto& stmt: statements){
        res += "\t\t" + stmt->to_string() + ";\n";
    }
    res += "\t}";
    return res;
}


Function::Function(Token tok, Token name, std::vector<AttributePtr> attributes, std::vector<triplet<Token, std::vector<AttributePtr>, TypeExprPtr>> params, 
                   bool varargs, TypeExprPtr return_type, DebugInfoPtr debug_info, std::optional<std::vector<LabelPtr>> body){
    this->tok = tok;
    this->name = name;
    this->attributes = attributes;
    this->params = params;
    this->varargs = varargs;
    this->return_type = return_type;
    this->debug_info = debug_info;
    this->body = body;
}

Token Function::get_name() const{
    return name;
}
std::vector<AttributePtr> Function::get_attributes() const{
    return attributes;
}
std::vector<triplet<Token, std::vector<AttributePtr>, TypeExprPtr>> Function::get_params() const{
    return params;
}
TypeExprPtr Function::get_return_type() const{
    return return_type;
}
DebugInfoPtr Function::get_debug_info() const{
    return debug_info;
}
std::optional<std::vector<LabelPtr>> Function::get_body() const{
    return body;
}
Token Function::get_token() const{
    return tok;
}
std::string Function::to_string() const{
    std::string res = "fn";

    for(const auto& attr: attributes){
        res += " "+attr->to_string();
    }
    res += " "+name.value+"(";
    for(size_t i=0;i<params.size();i++){
        res += params[i].third->to_string() + ":" + params[i].first.value;
        for(const auto& attr: params[i].second){
            res += " "+attr->to_string();
        }
        if(i!=params.size()-1) {
            res += ", ";
        }
    }
    res += ")";
    res += " -> "+return_type->to_string();
    if(debug_info!=nullptr) {
        res += " ! "+debug_info->to_string();
    }
    if(body.has_value()) {
        res += " {\n";
        for(const auto& label: body.value()){
            res += label->to_string()+"\n";
        }
        res += "}";
    }
    return res;
}


GlobalItem::GlobalItem(FunctionPtr function){
    if (function == nullptr) {
        throw std::invalid_argument("FunctionPtr cannot be null");
    }
    this->function = function;
    this->attribute = nullptr;
    this->global_var = nullptr;
}
GlobalItem::GlobalItem(AttributePtr attribute){
    if(attribute == nullptr) {
        throw std::invalid_argument("AttributePtr cannot be null");
    }
    this->function = nullptr;
    this->attribute = attribute;
    this->global_var = nullptr;
}
GlobalItem::GlobalItem(InstructionStmtPtr global_var){
    if(global_var == nullptr) {
        throw std::invalid_argument("InstructionStmtPtr cannot be null");
    }
    this->function = nullptr;
    this->attribute = nullptr;
    this->global_var = global_var;
}

FunctionPtr GlobalItem::get_function() const{
    return this->function;
}
AttributePtr GlobalItem::get_attribute() const{
    return this->attribute;
}
InstructionStmtPtr GlobalItem::get_global_var() const{
    return this->global_var;
}

GlobalItemKind GlobalItem::get_kind() const{
    if(function != nullptr){
        return GlobalItemKind::FunctionKind;
    }
    if(attribute != nullptr){
        return GlobalItemKind::GlobalAttributeKind;
    }
    return GlobalItemKind::GlobalVarKind;
}
std::string GlobalItem::to_string() const{
    switch(get_kind()){
        case GlobalItemKind::FunctionKind:
            return function->to_string();
        case GlobalItemKind::GlobalAttributeKind:
            return attribute->to_string();
        case GlobalItemKind::GlobalVarKind:
            return global_var->to_string();
    }
}

Program::Program(std::vector<GlobalItem> items){
    this->items = items;
}

std::vector<GlobalItem> Program::get_items() const{
    return items;
}
std::string Program::to_string() const{
    std::string res;
    for(const auto& item: items){
        res += item.to_string() + "\n";
    }
    return res;
}
}