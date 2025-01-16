#include <stdio.h>
#include <string.h>
#include <ctype.h>

#ifndef LEXER_H
#define LEXER_H

#define MAX_KEYWORDS 21
#define MAX_TOKEN_SIZE 100

typedef enum {
    KEYWORD, //0
    OPERATOR, //1
    SPECIAL_CHARACTER, //2
    CONSTANT, //3
    IDENTIFIER, //4
    HEADER, //5
    UNKNOWN //6
} TokenType;

typedef struct {
    char lexeme[MAX_TOKEN_SIZE];
    TokenType type;
} Token;

typedef struct {
    FILE* ptr;
}fileptr;

void initializeLexer(const char* filename);
Token getNextToken(fileptr fptr);

#endif
