#include "parser/parser.hpp"

namespace LIRA {
LiteralExprPtr Parser::parse_literal_expr(){
    switch (this->curr_tok.type){
        case TokenType::global_identifier:
        case TokenType::local_identifier:
        case TokenType::label_identifier:
        case TokenType::instruction_identifier:
        case TokenType::builtin_identifier:{
            return parse_named_literal_expr();
        }
        case TokenType::raw_string:
        case TokenType::string:{
            return parse_string_literal_expr();
        }
        case TokenType::number:{
            return parse_num_literal_expr();
        }
        case TokenType::lbracket:{
            return parse_array_literal_expr();
        }
        case TokenType::langel:{
            return parse_simd_literal_expr();
        }
        case TokenType::lbrace:{
            return parse_struct_literal_expr();
        }
        default:{
            error(curr_tok, "Expected a literal expression");
        }
    }
}
LiteralExprPtr Parser::parse_named_literal_expr(){
    return std::make_shared<NamedLiteralExpr>(this->curr_tok);
}
LiteralExprPtr Parser::parse_string_literal_expr(){
    return std::make_shared<StringLiteralExpr>(this->curr_tok);
}
LiteralExprPtr Parser::parse_num_literal_expr(){
    return std::make_shared<NumLiteralExpr>(this->curr_tok);
}
LiteralExprPtr Parser::parse_array_literal_expr(){
    Token tok = this->curr_tok;//the [ token
    std::vector<LiteralExprPtr> elements;
    while(peek().type != TokenType::rbracket){
        advance();//After the [ token or the , token
        elements.push_back(parse_literal_expr());
        if(peek().type == TokenType::comma){
            advance();//On the , token
        }
        else if(peek().type != TokenType::rbracket){
            error(peek(), "Expected ',' or ']' after array literal element in array literal expression");
        }
    }
    expect(TokenType::rbracket, "Expected ']' after array literal elements in array literal expression");
    return std::make_shared<ArrayLiteralExpr>(tok, elements);
}
LiteralExprPtr Parser::parse_simd_literal_expr(){
    Token tok = this->curr_tok;//the < token
    std::vector<LiteralExprPtr> elements;
    while(peek().type != TokenType::rangel){
        advance();//After the < token or the , token
        elements.push_back(parse_literal_expr());
        if(peek().type == TokenType::comma){
            advance();//On the , token
        }
        else if(peek().type != TokenType::rangel){
            error(peek(), "Expected ',' or '>' after SIMD literal element in SIMD literal expression");
        }
    }
    expect(TokenType::rangel, "Expected '>' after SIMD literal elements in SIMD literal expression");
    return std::make_shared<SIMDLiteralExpr>(tok, elements);
}
LiteralExprPtr Parser::parse_struct_literal_expr(){
    Token tok = this->curr_tok;//the { token
    std::vector<LiteralExprPtr> elements;
    while(peek().type != TokenType::rbrace){
        advance();//After the { token or the , token
        elements.push_back(parse_literal_expr());
        if(peek().type == TokenType::comma){
            advance();//On the , token
        }
        else if(peek().type != TokenType::rbrace){
            error(peek(), "Expected ',' or '}' after struct literal element in struct literal expression");
        }
    }
    expect(TokenType::rbrace, "Expected '}' after struct literal elements in struct literal expression");
    return std::make_shared<StructLiteralExpr>(tok, elements);
}
}