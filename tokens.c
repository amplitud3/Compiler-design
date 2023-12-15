#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX_TOKEN_LENGTH 100

// Token types
enum TokenType {
    KEYWORD,
    IDENTIFIER,
    NUMBER,
    OPERATOR,
    DELIMITER,
};

// Structure to represent a token
struct Token {
    enum TokenType type;
    char lexeme[MAX_TOKEN_LENGTH];
};

// Function to check if a string is a keyword
int isKeyword(char* str) {
    char* keywords[] = {"int", "float", "if", "else", "while", "for", "return"};
    int numKeywords = 7;
    for (int i = 0; i < numKeywords; i++) {
        if (strcmp(keywords[i], str) == 0) {
            return 1;  // It's a keyword
        }
    }
    return 0;  // It's not a keyword
}

// Function to recognize and tokenize the input program
void tokenize(char* program) {
struct Token token;
    int i = 0;
    int programLength = strlen(program);
    while (i < programLength) {
        // Skip whitespace
        while (isspace(program[i])) {
            i++;
        }

        // Check for keywords, identifiers, and numbers
        if (isalpha(program[i])) {
            int j = 0;
            while (isalnum(program[i]) || program[i] == '_') {
                if (j < MAX_TOKEN_LENGTH - 1) {
                    token.lexeme[j] = program[i];
                    j++;
                }
                i++;
            }
            token.lexeme[j] = '\0';
            if (isKeyword(token.lexeme)) {
                token.type = KEYWORD;
            } else {
                token.type = IDENTIFIER;
            }
        } else if (isdigit(program[i])) {
            int j = 0;
            while (isdigit(program[i]) || program[i] == '.') {
                if (j < MAX_TOKEN_LENGTH - 1) {
                    token.lexeme[j] = program[i];
                    j++;
                }
                i++;
            }
            token.lexeme[j] = '\0';
            token.type = NUMBER;
        }

        // Check for operators and delimiters
        else if (strchr("+-*/=<>", program[i]) != NULL) {
            token.lexeme[0] = program[i];
            token.lexeme[1] = '\0';
            token.type = OPERATOR;
            i++;
        } else if (strchr("();{},[]", program[i]) != NULL) {
            token.lexeme[0] = program[i];
            token.lexeme[1] = '\0';
            token.type = DELIMITER;
            i++;
        } else {
            // Handle unsupported characters or tokens
            printf("Error: Invalid character: %c\n", program[i]);
            i++;
        }

        // Print the recognized token
        printf("Lexeme: %s\t Type: %d \n",  token.lexeme, token.type);
    }
}

int main() {
    char program[] = "int main() {\n    int x = 5;\n    return x;\n}";

    struct Token token;
    
    printf("\nType 0 = KEYWORD\nType 1 = IDENTIFIER\nType 2 = NUMBER\nType 3 = OPERATOR\nType 4 = DELIMITER\n\n\n\n");

    tokenize(program);

    return 0;
}

