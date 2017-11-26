#pragma once

#define IS_DIGIT(c) (c >= '0' && c <= '9')
#define IS_WHITESPACE(c) (c == ' ')
#define IS_DOT(c) (c == '.')
#define IS_NEG(c) (c == '-')
// For operators TODO: Move elsewhere eventually?
#define IS_OP(c) (std::string("+-*/()").find(c) != std::string::npos)
#define IS_ADD(c) (std::string("+").find(c) != std::string::npos)
#define IS_SUB(c) (std::string("-").find(c) != std::string::npos)
#define IS_MULT(c) (std::string("*").find(c) != std::string::npos)
#define IS_DIV(c) (std::string("/").find(c) != std::string::npos)
#define IS_OPEN_PAR(c) (std::string("(").find(c) != std::string::npos)
#define IS_CLOSING_PAR(c) (std::string(")").find(c) != std::string::npos)


#define TO_INT(c) (c - '0')
