#include "ast/ast.hpp"
#include "lexer/token.hpp"
#include <map>

namespace LIRA {
class Parser {
    std::size_t curr_index = 0;
    Token curr_tok;
    std::vector<Token> toks;
    std::string filename;

    // Utils
    void advance();
    void advance_on_semicolon();
    Token peek(std::size_t i=1) const;// peek the token at curr_index + i without advancing
    void expect(TokenType expected_type, std::string msg="",std::string submsg="",std::string ecode="");
    [[noreturn]] void error(Token tok, std::string msg,std::string submsg="",std::string ecode="");

    // Parse type expressions
    TypeExprPtr parse_type_expr(bool has_attribute);
    TypeExprPtr parse_named_type_expr(bool has_attribute);
    TypeExprPtr parse_array_type_expr(bool has_attribute);
    TypeExprPtr parse_simd_type_expr(bool has_attribute);
    TypeExprPtr parse_struct_type_expr(bool has_attribute);
    TypeExprPtr parse_func_type_expr(bool has_attribute);

    // Parse literal expressions
    LiteralExprPtr parse_literal_expr();
    LiteralExprPtr parse_named_literal_expr();
    LiteralExprPtr parse_string_literal_expr();
    LiteralExprPtr parse_num_literal_expr();
    LiteralExprPtr parse_array_literal_expr();
    LiteralExprPtr parse_simd_literal_expr();
    LiteralExprPtr parse_struct_literal_expr();

    // Parse attributes
    DebugInfoPtr parse_debug_info();//On ! token. 
    std::pair<ExprPtr,TypeExprPtr> parse_type_expr_pair();//type:expr pair for args
    AttributePtr parse_attribute();//On #
    std::vector<AttributePtr> parse_attributes();//On # token. Multiple attributes can follow afterwards. We keep parsing until we dont see a # token anymore
    InstructionStmtPtr parse_instruction_stmt(bool is_global);//On 'let' token or instruction token
    LabelPtr parse_label();//On label identifier token
    std::vector<LabelPtr> parse_labels();
    FunctionPtr parse_function();//On 'fn' token
    GlobalItemPtr parse_global_item();

    public:
    Parser(const std::vector<Token>& toks, const std::string& filename);
    ProgramPtr parse();
};
}