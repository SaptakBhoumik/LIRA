error_src = [
    'error/error.cpp' 
]
lexer_src = [
    'lexer/error.cpp',
    'lexer/lexer.cpp',
    'lexer/token.cpp',
    'lexer/utils.cpp'
]

ast_src = [
    'ast/ast_literal_node.cpp',
    'ast/ast_type_node.cpp',
    'ast/ast.cpp',
]

parser_src = [
    'parser/parse_type_expr.cpp',
    'parser/parse_literal_expr.cpp',
    'parser/parser.cpp',
    'parser/utils.cpp',
]

symtable_src = [
    'symtable/symtable.cpp',
    'symtable/type_reducer.cpp'
]
include = include_directories('../include/')
error = static_library('error', sources: error_src, include_directories: include)
lexer = static_library('lexer', sources: lexer_src, include_directories: include)
ast = static_library('ast', sources: ast_src, include_directories: include)
parser = static_library('parser', sources: parser_src, include_directories: include)
symtable = static_library('symtable', sources: symtable_src, include_directories: include)