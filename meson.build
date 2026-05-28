project('LIRA', 'cpp', version: '0.1')

cpp_src = [
    'src/LIRA.cpp',
]

include = include_directories('include/')

add_project_arguments('-std=c++2a', language: 'cpp')


subdir('src/')

executable(
    'LIRA.elf',
    sources: cpp_src, 
    include_directories: include,
    link_with: [error, lexer, ast, parser]
)