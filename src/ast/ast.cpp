#include "ast/ast.hpp"

namespace LIRA {
namespace IR {
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


Attribute::Attribute(Token tok, Token name, std::vector<std::pair<ExprPtr,TypeExprPtr>> args, std::vector<triplet<Token,ExprPtr,TypeExprPtr>> kwargs){
    this->tok = tok;
    this->name = name;
    this->args = args;
    this->kwargs = kwargs;
}

Token Attribute::get_name() const{
    return this->name;
}
std::vector<std::pair<ExprPtr,TypeExprPtr>> Attribute::get_args() const{
    return this->args;
}
std::vector<triplet<Token,ExprPtr,TypeExprPtr>> Attribute::get_kwargs() const{
    return this->kwargs;
}

Token Attribute::get_token() const{
    return this->tok;
}
std::string Attribute::to_string() const{
    std::string res = "#["+this->name.value;
    res += "(";
    for(size_t i=0;i<this->args.size();i++){
        res += this->args[i].second->to_string()+":"+this->args[i].first->to_string();
        if(i!=this->args.size()-1 || this->kwargs.size()>0){ 
            res += ", ";
        }
    }
    for(size_t i=0;i<this->kwargs.size();i++){
        res += this->kwargs[i].first.value+"="+this->kwargs[i].third->to_string()+":"+this->kwargs[i].second->to_string();
        if(i!=this->kwargs.size()-1){
            res += ", ";
        }
    }
    res += ")]";
    return res;
}


Expr::Expr(LiteralExprPtr literal){
    if(literal == nullptr){
        throw std::invalid_argument("LiteralExprPtr cannot be null");
    }
    this->literal = literal;
    this->type = nullptr;
}
Expr::Expr(TypeExprPtr type){
    if(type == nullptr){
        throw std::invalid_argument("TypeExprPtr cannot be null");
    }
    this->type = type;
    this->literal = nullptr;
}

ExprKind Expr::get_kind() const{
    if(this->literal!=nullptr){
        return ExprKind::LiteralExpr;
    } 
    else {
        return ExprKind::TypeExpr;
    }
}
Token Expr::get_token() const{
    if(this->literal!=nullptr){
        return this->literal->get_token();
    } 
    else {
        return this->type->get_token();
    }
}
LiteralExprPtr Expr::get_literal() const{
    return this->literal;
}
TypeExprPtr Expr::get_type() const{
    return this->type;
}
std::string Expr::to_string() const{
    if(this->literal!=nullptr){
        return this->literal->to_string();
    } 
    else {
        return this->type->to_string();
    }
}


InstructionStmt::InstructionCall::InstructionCall(Token tok, std::vector<std::pair<ExprPtr,TypeExprPtr>> operands, std::vector<AttributePtr> attributes, DebugInfoPtr debug_info){
    this->tok = tok;
    this->operands = operands;
    this->attributes = attributes;
    this->debug_info = debug_info;
}

Token InstructionStmt::InstructionCall::get_token() const{
    return this->tok;
}
std::vector<std::pair<ExprPtr,TypeExprPtr>> InstructionStmt::InstructionCall::get_operands() const{
    return this->operands;
}
std::vector<AttributePtr> InstructionStmt::InstructionCall::get_attributes() const{
    return this->attributes;
}
DebugInfoPtr InstructionStmt::InstructionCall::get_debug_info() const{
    return this->debug_info;
}
std::string InstructionStmt::InstructionCall::to_string() const{
    std::string res = this->tok.value+"(";
    for(size_t i=0;i<this->operands.size();i++){
        res += this->operands[i].second->to_string()+":"+this->operands[i].first->to_string();
        if(i!=this->operands.size()-1){
            res += ", ";
        }
    }
    res += ")";
    for(const auto& attr: this->attributes){
        res += " "+attr->to_string();
    }
    if(this->debug_info!=nullptr){
        res += " ! "+this->debug_info->to_string();
    }
    return res;
}



InstructionStmt::InstructionStmt(Token tok, std::optional<triplet<Token, std::vector<AttributePtr>, TypeExprPtr>> name,std::optional<InstructionCall> value){
    this->tok = tok;
    this->name = name;
    this->value = value;
}

std::optional<triplet<Token, std::vector<AttributePtr>, TypeExprPtr>> InstructionStmt::get_name() const{
    return this->name;
}
std::optional<InstructionStmt::InstructionCall> InstructionStmt::get_value() const{
    return this->value;
}
Token InstructionStmt::get_token() const{
    return this->tok;
}
std::string InstructionStmt::to_string() const{
    std::string res;
    if(this->name.has_value()){
        res = "let " + this->name.value().third->to_string() + ":" + this->name.value().first.value;
        for(const auto& attr: this->name.value().second){
            res += " "+attr->to_string();
        }
        if(this->value.has_value()){
            res += " = ";
        }
    }
    if(value.has_value()){
        res += this->value->to_string();
    }
    return res;
}



Label::Label(Token tok, Token name, std::vector<InstructionStmtPtr> statements, std::vector<triplet<Token, std::vector<AttributePtr>, TypeExprPtr>> params){
    this->tok = tok;
    this->name = name;
    this->statements = statements;
    this->params = params;
}

Token Label::get_name() const{
    return this->name;
}
Token Label::get_token() const{
    return this->tok;
}
std::vector<InstructionStmtPtr> Label::get_statements() const{
    return this->statements;
}
std::vector<triplet<Token, std::vector<AttributePtr>, TypeExprPtr>> Label::get_params() const{
    return this->params;
}

std::string Label::to_string() const{
    std::string res = "\tlabel " + this->name.value + "(";
    for(size_t i=0;i<this->params.size();i++){
        res += "let " + this->params[i].third->to_string()+":"+this->params[i].first.value;
        for(const auto& attr: this->params[i].second){
            res += " "+attr->to_string();
        }
        if(i!=this->params.size()-1){
            res += ", ";
        }
    }
    res += "){\n";
    for(const auto& stmt: this->statements){
        res += "\t\t" + stmt->to_string() + ";\n";
    }
    res += "\t}";
    return res;
}


Scope::Scope(Token tok, ScopeType scope_type, std::optional<Token> scope_name, Token scope_var_name, std::optional<Token> parent_scope_name, 
            std::optional<triplet<Token,Token,Token>> scope_loc, std::optional<triplet<Token,Token,Token>> callsite_loc){
    this->tok = tok;
    this->scope_type = scope_type;
    this->scope_name = scope_name;
    this->scope_var_name = scope_var_name;
    this->parent_scope_name = parent_scope_name;
    this->scope_loc = scope_loc;
    this->callsite_loc = callsite_loc;
}

ScopeType Scope::get_scope_type() const{
    return this->scope_type;
}
std::optional<Token> Scope::get_scope_name() const{
    return this->scope_name;
}
Token Scope::get_scope_var_name() const{
    return this->scope_var_name;
}
std::optional<Token> Scope::get_parent_scope_name() const{
    return this->parent_scope_name;
}
std::optional<triplet<Token,Token,Token>> Scope::get_scope_loc() const{
    return this->scope_loc;
}
std::optional<triplet<Token,Token,Token>> Scope::get_callsite_loc() const{
    return this->callsite_loc;
}
Token Scope::get_token() const{
    return this->tok;
}
std::string Scope::to_string() const{
    std::string res = "\tscope ";
    res += this->scope_var_name.value + " = ";
    if(this->scope_type == ScopeType::FunctionScope){
        res += "function(";
    } 
    else if(this->scope_type == ScopeType::BlockScope){
        res += "block(";
    }
    else if(this->scope_type == ScopeType::InlineScope){
        res += "inline(";
    }
    if(this->scope_name.has_value()){
        res += "scope_name = \"" + this->scope_name.value().value + "\", ";
    }
    if(this->parent_scope_name.has_value()){
        res += "parent_scope = " + this->parent_scope_name.value().value + ", ";
    }
    if(this->scope_loc.has_value()){
        res += "scope_loc = \"" + this->scope_loc.value().first.value + "\":" + this->scope_loc.value().second.value + ":" + this->scope_loc.value().third.value  + ", ";
    }
    if(this->callsite_loc.has_value()){
        res += "callsite_loc = \"" + this->callsite_loc.value().first.value + "\":" + this->callsite_loc.value().second.value + ":" + this->callsite_loc.value().third.value  + ", ";
    }
    //Remove the last ", " if it exists
    if(res.size() >= 2 && res.substr(res.size() - 2) == ", "){
        res = res.substr(0, res.size() - 2);
    }
    res += ");";
    return res;
}


Function::Function(Token tok, Token name, std::vector<AttributePtr> attributes, std::vector<triplet<Token, std::vector<AttributePtr>, TypeExprPtr>> params, 
                   bool varargs, TypeExprPtr return_type, DebugInfoPtr debug_info, std::vector<ScopePtr> scopes, std::vector<LabelPtr> body){
    this->tok = tok;
    this->name = name;
    this->attributes = attributes;
    this->params = params;
    this->varargs = varargs;
    this->return_type = return_type;
    this->debug_info = debug_info;
    this->scopes = scopes;  
    this->body = body;
}

Token Function::get_name() const{
    return this->name;
}
std::vector<AttributePtr> Function::get_attributes() const{
    return this->attributes;
}
std::vector<triplet<Token, std::vector<AttributePtr>, TypeExprPtr>> Function::get_params() const{
    return this->params;
}
TypeExprPtr Function::get_return_type() const{
    return this->return_type;
}
DebugInfoPtr Function::get_debug_info() const{
    return this->debug_info;
}
std::vector<ScopePtr> Function::get_scopes() const{
    return this->scopes;
}
std::vector<LabelPtr> Function::get_body() const{
    return this->body;
}
Token Function::get_token() const{
    return this->tok;
}
std::string Function::to_string() const{
    std::string res = "fn";

    for(const auto& attr: this->attributes){
        res += " "+attr->to_string();
    }
    res += " "+this->name.value+"(";
    for(size_t i=0;i<this->params.size();i++){
        res += "let " + this->params[i].third->to_string() + ":" + this->params[i].first.value;
        for(const auto& attr: this->params[i].second){
            res += " "+attr->to_string();
        }
        if(i!=this->params.size()-1){
            res += ", ";
        }
    }
    if(this->varargs){
        if(!this->params.empty()){
            res += ", ";
        }
        res += "...";
    }
    res += ")";
    res += " -> "+this->return_type->to_string();
    if(this->debug_info!=nullptr){
        res += " ! "+this->debug_info->to_string();
    }
    if(this->body.size() > 0){
        res += " {\n";
        for(const auto& scope: this->scopes){
            res += scope->to_string() + "\n";
        }
        for(const auto& label: this->body){
            res += label->to_string()+"\n";
        }
        res += "}";
    }
    return res;
}


GlobalItem::GlobalItem(FunctionPtr function){
    if (function == nullptr){
        throw std::invalid_argument("FunctionPtr cannot be null");
    }
    this->function = function;
    this->attribute = nullptr;
    this->global_var = nullptr;
}
GlobalItem::GlobalItem(AttributePtr attribute){
    if(attribute == nullptr){
        throw std::invalid_argument("AttributePtr cannot be null");
    }
    this->function = nullptr;
    this->attribute = attribute;
    this->global_var = nullptr;
}
GlobalItem::GlobalItem(InstructionStmtPtr global_var){
    if(global_var == nullptr){
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
    if(this->function != nullptr){
        return GlobalItemKind::FunctionKind;
    }
    if(this->attribute != nullptr){
        return GlobalItemKind::GlobalAttributeKind;
    }
    return GlobalItemKind::GlobalVarKind;
}
std::string GlobalItem::to_string() const{
    switch(get_kind()){
        case GlobalItemKind::FunctionKind:
            return this->function->to_string();
        case GlobalItemKind::GlobalAttributeKind:
            return this->attribute->to_string() + ";";
        case GlobalItemKind::GlobalVarKind:
            return this->global_var->to_string() + ";";
    }
}

Program::Program(std::vector<GlobalItemPtr> items){
    this->items = items;
}

std::vector<GlobalItemPtr> Program::get_items() const{
    return this->items;
}
std::string Program::to_string() const{
    std::string res;
    for(const auto& item: this->items){
        res += item->to_string() + "\n";
    }
    return res;
}
}
}