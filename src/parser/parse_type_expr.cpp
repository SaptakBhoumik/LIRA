#include "parser/parser.hpp"
#include <iostream>

namespace LIRA{
TypeExprPtr Parser::parse_type_expr(bool has_attribute){
    switch (this->curr_tok.type){
        case TokenType::global_identifier:
        case TokenType::local_identifier:
        case TokenType::buildin_identifier:{
            return parse_named_type_expr(has_attribute);
        }
        case TokenType::lparen:{
            advance();//After '(' 
            TypeExprPtr stmt = parse_type_expr(true);
            expect(TokenType::rparen, "Expected ')' after type expression");
            return stmt;
        }
        case TokenType::lbracket:{
            return parse_array_type_expr(has_attribute);
        }
        case TokenType::langel:{    
            return parse_simd_type_expr(has_attribute);
        }
        case TokenType::star:{
            return parse_ptr_type_expr(has_attribute);
        }
        case TokenType::lbrace:{
            return parse_struct_type_expr(has_attribute);
        }
        case TokenType::kw_fn:{
            return parse_func_type_expr(has_attribute);
        }
        default:{
            std::cout << "Unexpected token type: " << this->curr_tok << std::endl;
            error(this->curr_tok, "Expected a type expression");
        }
    }
}
TypeExprPtr Parser::parse_named_type_expr(bool has_attribute){
    Token name = this->curr_tok;
    std::vector<AttributePtr> attributes;
    if(has_attribute && peek().type == TokenType::hash){
        advance();//On the # token
        attributes = parse_attributes();
    }
    return std::make_shared<NamedTypeExpr>(name, attributes);
}
TypeExprPtr Parser::parse_array_type_expr(bool has_attribute){
    Token tok = this->curr_tok;//the [ token
    advance();//After the [ token
    TypeExprPtr base_type = parse_type_expr(true);
    expect(TokenType::comma, "Expected ',' after base type in array type expression");
    expect(TokenType::number, "Expected array size after '[' in array type expression");
    Token size = this->curr_tok;
    expect(TokenType::rbracket, "Expected ']' after array size in array type expression");
    std::vector<AttributePtr> attributes;
    if(has_attribute && peek().type == TokenType::hash){
        advance();//On the # token
        attributes = parse_attributes();
    }
    return std::make_shared<ArrayTypeExpr>(tok, base_type, size, attributes);
}
TypeExprPtr Parser::parse_simd_type_expr(bool has_attribute){
    Token tok = this->curr_tok;//the < token
    advance();//After the < token
    TypeExprPtr base_type = parse_type_expr(true);
    expect(TokenType::comma, "Expected ',' after base type in SIMD type expression");
    expect(TokenType::number, "Expected SIMD size after '<' in SIMD type expression");
    Token size = this->curr_tok;
    expect(TokenType::rangel, "Expected '>' after SIMD size in SIMD type expression");
    std::vector<AttributePtr> attributes;
    if(has_attribute && peek().type == TokenType::hash){
        advance();//On the # token
        attributes = parse_attributes();
    }
    return std::make_shared<SIMDTypeExpr>(tok, base_type, size, attributes);
}
TypeExprPtr Parser::parse_ptr_type_expr(bool has_attribute){
    Token tok = this->curr_tok;//the * token
    advance();//After the * token
    TypeExprPtr base_type = parse_type_expr(true);
    std::vector<AttributePtr> attributes;
    if(has_attribute && peek().type == TokenType::hash){
        advance();//On the # token
        attributes = parse_attributes();
    }
    return std::make_shared<PtrTypeExpr>(tok, base_type, attributes);
}
TypeExprPtr Parser::parse_struct_type_expr(bool has_attribute){
    // {type1, type2, ...} #[attributes]
    Token tok = this->curr_tok;//the { token
    std::vector<TypeExprPtr> fields;
    while(peek().type != TokenType::rbrace){
        advance();//After the { token or the , token
        fields.push_back(parse_type_expr(true));
        if(peek().type == TokenType::comma){
            advance();//On the , token
        }
        else if(peek().type != TokenType::rbrace){
            error(peek(), "Expected ',' or '}' after struct type field in struct type expression");
        }
    }
    expect(TokenType::rbrace, "Expected '}' after struct type fields in struct type expression");
    std::vector<AttributePtr> attributes;
    if(has_attribute && peek().type == TokenType::hash){
        advance();//On the # token
        attributes = parse_attributes();
    }
    return std::make_shared<StructTypeExpr>(tok, fields, false, attributes);
}
TypeExprPtr Parser::parse_func_type_expr(bool has_attribute){
    // fn(type1, type2, ... ) -> return_type #[attributes]
    Token tok = this->curr_tok;//the fn token
    expect(TokenType::lparen, "Expected '(' after 'fn' in function type expression");
    std::vector<TypeExprPtr> param_types;
    bool varargs = false;
    while(peek().type != TokenType::rparen){
        advance();//After the ( token or the , token
        if(this->curr_tok.type == TokenType::ellipsis){
            varargs = true;
            break;
        }
        param_types.push_back(parse_type_expr(true));
        if(peek().type == TokenType::comma){
            advance();//On the , token
        }
        else if(peek().type != TokenType::rparen){
            error(peek(), "Expected ',' or ')' after function type parameter in function type expression");
        }
    }
    expect(TokenType::rparen, "Expected ')' after function type parameters in function type expression");
    expect(TokenType::arrow, "Expected '->' after function type parameters in function type expression");
    advance();//after the '->' token
    TypeExprPtr return_type = parse_type_expr(false);//Put expr within bracket to only allow attributes on the return type
    std::vector<AttributePtr> attributes;
    if(has_attribute && peek().type == TokenType::hash){
        advance();//On the # token
        attributes = parse_attributes();
    }
    return std::make_shared<FuncTypeExpr>(tok, param_types, varargs, return_type, attributes);
}
}