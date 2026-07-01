#include "lexer/lexer.hpp"
#include <algorithm>
#include <cctype>
namespace LIRA {
namespace IR {
bool Lexer::advance(){
    if(this->curr_index < this->input.size() - 1){
        this->curr_index++;
        this->col++;
        this->curr_char = this->input[this->curr_index];
        return true;
    }
    return false;
}

char Lexer::peek(std::size_t i) const{
    if((this->curr_index + i) < this->input.size()){
        return this->input[this->curr_index + i];
    }
    return '\0';
}

std::vector<std::string> Lexer::split_lines(const std::string& code){
    std::vector<std::string> lines;
    std::string line;
    char prev = '\0';

    for (char c : code){
        if(c == '\n' || c == '\r'){
            if(prev == '\r' && c == '\n'){
                // \r\n counts as a single line ending; already pushed on '\r'
            } 
            else{
                lines.push_back(line);
                line.clear();
            }
        } 
        else if(c == '"'){
            line += "\\\"";   // escape embedded quotes for diagnostic display
        }
        else{
            line += c;
        }
        prev = c;
    }
    lines.push_back(line);
    return lines;
}


bool Lexer::is_num(const std::string& s){
    //Yes we expect u to convert stuff like hex,binary etc to correct form before hand
    if(s.empty()) return false;
    size_t start = 0;
    if(s[0] == '-' || s[0] == '+'){
        if(s.size() == 1) return false; // just a sign is not a number
        start = 1;
    }
    bool has_decimal_point = false;
    for (size_t i = start; i < s.size(); i++){
        if(s[i] == '.'){
            if(has_decimal_point){
                return false; // multiple decimal points
            }
            has_decimal_point = true;
        } 
        else if(!std::isdigit(s[i])){
            return false; // non-digit character
        }
    }
    return true;
}

TokenType Lexer::get_identifier_type(const std::string& s){
    if(s[0] == '$'){
        return TokenType::global_identifier;
    } 
    else if(s[0] == '%'){
        return TokenType::local_identifier;
    } 
    else if(s[0] == '@'){
        return TokenType::label_identifier;
    } 
    else if(s[0] == '.'){
        return TokenType::instruction_identifier;
    }
    else if(s[0] == '^'){
        return TokenType::scope_identifier;
    }
    else{
        return TokenType::builtin_identifier;
    }
}
}
} // namespace LIRA