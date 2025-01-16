#include "lexer.h"

static const char* keywords[MAX_KEYWORDS] = {
    "int", "float", "return", "if", "else", "while", "for", "do", "break", "continue",
    "char", "double", "void", "switch", "case", "default", "const", "static", "sizeof", "struct", "main"
};
static const char* operators = "+-*/%=!<>|&";
static const char* specialCharacters = ",;{}()[]\"#<>";
char str[MAX_TOKEN_SIZE];

void initializeLexer(const char* filename) {
    char* validFile = strrchr(filename, '.');
    if (validFile && strcasecmp(validFile, ".c") == 0) {
        printf("File is valid\n");
    } else {
        printf("File should be \".c\" format\n");
    }
}

Token getNextToken(fileptr fptr) {
    Token token = {{0}, UNKNOWN};
    char ch;
    int i = 0;

    while ((ch = getc(fptr.ptr)) != EOF) {
        // Skip whitespace and new line
        if (isspace(ch) || ch == '\n' || ch == '\t') continue;
        
        // Operators
        for (int j = 0; operators[j] != '\0'; j++) {
            if (ch == operators[j]) {
                token.lexeme[0] = ch;
                token.lexeme[1] = '\0';
                token.type = OPERATOR;
                return token;
            }
        }

        // Special Characters
        for (int j = 0; specialCharacters[j] != '\0'; j++) {
            if (ch == specialCharacters[j]) {
                //Header
                if (ch == '#') {
                    str[i++] = ch;
                    while ((ch = getc(fptr.ptr)) != EOF && (ch != '>')) {
                        str[i++] = ch;
                    }
                    str[i++] = ch;
                    str[i++] = '\0';
                    i = 0;
                    strcpy(token.lexeme, str);
                    token.type = HEADER;
                    return token;
                }
                //Constants
                else if (ch == '"') {
                    str[i++] = ch;
                    while ((ch = getc(fptr.ptr)) != EOF && ch != '"') {
                        str[i++] = ch;
                    }
                    str[i++] = ch;
                    str[i++] = '\0';
                    i = 0;
                    //fseek(fptr.ptr, -1, SEEK_CUR);
                    strcpy(token.lexeme, str);
                    token.type = CONSTANT;
                    return token;
                //Special character
                }else {
                    token.lexeme[0] = ch;
                    token.lexeme[1] = '\0';
                    token.type = SPECIAL_CHARACTER;
                    return token;
                }
            }
        }

        //Digits
        if (isdigit(ch)) {
            str[i++] = ch;
            while ((ch = getc(fptr.ptr)) != EOF && isdigit(ch)) {
                str[i++] = ch;
            }
            str[i] = '\0';
            i = 0;
            fseek(fptr.ptr, -1, SEEK_CUR);
            strcpy(token.lexeme, str);
            token.type = CONSTANT;
            return token;
        }

        //Keywords
        if (isalpha(ch)) {
            str[i++] = ch;
            while ((ch = getc(fptr.ptr)) != EOF && isalpha(ch)) {
                str[i++] = ch;
            }
            str[i] = '\0';
            i = 0;
            fseek(fptr.ptr, -1, SEEK_CUR);
            for (int j = 0; j < MAX_KEYWORDS; j++) {
                if (strcasecmp(str, keywords[j]) == 0) {
                    strcpy(token.lexeme, str);
                    token.type = KEYWORD;
                    return token;
                }
            }
            //identifier
            strcpy(token.lexeme, str);
            token.type = IDENTIFIER;
            return token;
        }
    }

    //Unknown
    token.type = UNKNOWN;
    return token;
}
