#include "lexer.h"

int main(int argc, char *argv[]) {
    initializeLexer(argv[1]);
    fileptr fptr;
    fptr.ptr = fopen(argv[1], "r");
    char outputs[7][20] = {"KEYWORD", "OPERATOR", "SPECIAL_CHARACTER", "CONSTANT", "IDENTIFIER", "HEADER", "UNKNOWN"};
    if (!fptr.ptr) {
        perror("Error: Unable to open file");
        return 1;
    }
    Token token;
    while ((token = getNextToken(fptr)).type != UNKNOWN) {
        printf("%-20s-> Type: %s\n", token.lexeme, outputs[token.type]);
    }
    return 0;
}
