#include "lexer/token.hpp"

namespace LIRA {
namespace IR {
std::string to_string(TokenType type) {
    //Dont use map. Use switch case because in case u forget to add a case the compiler will warn u even before u run the code, 
    //whereas with a map it will just return an empty string/throw error and u might not notice the bug until runtime
    switch (type) {
        case TokenType::eof: return "<EOF>";

        case TokenType::number: return "<number>";
        case TokenType::string: return "<string>";
        case TokenType::raw: return "<r>";
        case TokenType::raw_string: return "<raw string>";

        case TokenType::global_identifier: return "<global identifier>";
        case TokenType::local_identifier: return "<local identifier>";
        case TokenType::label_identifier: return "<label identifier>";
        case TokenType::instruction_identifier: return "<instruction identifier>";
        case TokenType::scope_identifier: return "<scope identifier>";
        case TokenType::builtin_identifier: return "<buildin identifier>";

        case TokenType::lparen: return "(";
        case TokenType::rparen: return ")";
        case TokenType::lbracket: return "[";
        case TokenType::rbracket: return "]";
        case TokenType::lbrace: return "{";
        case TokenType::rbrace: return "}";
        case TokenType::langel: return "<";
        case TokenType::rangel: return ">";

        case TokenType::bang: return "!";
        case TokenType::assign: return "=";
        case TokenType::hash: return "#";
        case TokenType::arrow: return "->";
        case TokenType::comma: return ",";
        case TokenType::ellipsis: return "...";
        case TokenType::colon: return ":";

        case TokenType::kw_fn: return "fn";
        case TokenType::kw_let: return "let";
        case TokenType::kw_label: return "label";
        case TokenType::kw_scope: return "scope";
        case TokenType::kw_null: return "null";
        case TokenType::kw_zeroinitializer: return "zeroinitializer";
        case TokenType::kw_poison: return "poison";

        case TokenType::semicolon: return ";";
    }
    return "<unknown token>";
}
std::string to_string(const Token& tok){
    return "Token(col : " + std::to_string(tok.col) + ", line: " + std::to_string(tok.line) + ", value: " + tok.value + ", type: " + to_string(tok.type) + ")";
}

std::ostream& operator<<(std::ostream& os, const Token& tok){
    os << to_string(tok);
    return os;
}

bool is_identifier(TokenType type){
    return type == TokenType::global_identifier || 
           type == TokenType::local_identifier || 
           type == TokenType::label_identifier || 
           type == TokenType::instruction_identifier || 
           type == TokenType::scope_identifier || 
           type == TokenType::builtin_identifier;
}
}
}