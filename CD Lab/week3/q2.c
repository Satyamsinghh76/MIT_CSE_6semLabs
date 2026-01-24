#include <stdio.h>
#include <ctype.h>
#include <string.h>
#define MAX 100
typedef struct {
    int row;
    int col;
    char type[30];
    char lexeme[50];
} Token;
FILE *fp;
int row = 1, col = 0;
char *keywords[] = {
    "int", "float", "char", "double", "if", "else",
    "while", "for", "return", "void", "break", "continue"
};
int keywordCount = sizeof(keywords) / sizeof(keywords[0]);
int isKeyword(char *);
Token getNextToken();
int isKeyword(char *str) {
    for (int i = 0; i < keywordCount; i++) {
        if (strcmp(str, keywords[i]) == 0)
            return 1;
    }
    return 0;
}
Token getNextToken() {
    Token token;
    char ch;
    int i;
    strcpy(token.type, "EOF");
    token.lexeme[0] = '\0';
    token.row = row;
    token.col = col;
    while ((ch = fgetc(fp)) != EOF) {
        col++;
        if (ch == '\n') {
            row++;
            col = 0;
            continue;
        }
        if (isspace(ch))
            continue;
        if (ch == '#') {
            while ((ch = fgetc(fp)) != '\n' && ch != EOF);
            row++;
            col = 0;
            continue;
        }
        if (ch == '/') {
            char next = fgetc(fp);
            col++;
            if (next == '/') {
                while ((ch = fgetc(fp)) != '\n' && ch != EOF);
                row++;
                col = 0;
                continue;
            }
            else if (next == '*') {
                while ((ch = fgetc(fp)) != EOF) {
                    if (ch == '\n') {
                        row++;
                        col = 0;
                    }
                    if (ch == '*') {
                        char temp = fgetc(fp);
                        if (temp == '/')
                            break;
                        else
                            ungetc(temp, fp);
                    }
                }
                continue;
            }
            else {
                ungetc(next, fp);
                col--;
            }
        }
        if (ch == '"') {
            while ((ch = fgetc(fp)) != '"' && ch != EOF) {
                if (ch == '\n') {
                    row++;
                    col = 0;
                }
            }
            continue;
        }
        if (isalpha(ch) || ch == '_') {
            i = 0;
            token.lexeme[i++] = ch;
            token.row = row;
            token.col = col;

            while ((ch = fgetc(fp)) != EOF && (isalnum(ch) || ch == '_')) {
                token.lexeme[i++] = ch;
                col++;
            }
            token.lexeme[i] = '\0';
            if (ch != EOF)
                ungetc(ch, fp);

            if (isKeyword(token.lexeme))
                strcpy(token.type, "KEYWORD");
            else
                strcpy(token.type, "IDENTIFIER");

            return token;
        }
        if (isdigit(ch)) {
            i = 0;
            token.lexeme[i++] = ch;
            token.row = row;
            token.col = col;
            while ((ch = fgetc(fp)) != EOF && isdigit(ch)) {
                token.lexeme[i++] = ch;
                col++;
            }
            token.lexeme[i] = '\0';
            if (ch != EOF)
                ungetc(ch, fp);
            strcpy(token.type, "NUMBER");
            return token;
        }
        if (strchr("+-*/%=<>!", ch)) {
            token.lexeme[0] = ch;
            token.lexeme[1] = '\0';
            token.row = row;
            token.col = col;
            strcpy(token.type, "OPERATOR");
            return token;
        }
        if (strchr(";(),{}[]", ch)) {
            token.lexeme[0] = ch;
            token.lexeme[1] = '\0';
            token.row = row;
            token.col = col;
            strcpy(token.type, "SPECIAL_SYMBOL");
            return token;
        }
    }
    return token;
}
int main() {
    Token t;
    fp = fopen("q1.c", "r");
    if (!fp) {
        printf("Error opening file\n");
        return 1;
    }
    printf("Row\tCol\tType\t\tLexeme\n");
    printf("--------------------------------------\n");
    while (1) {
        t = getNextToken();
        if (strcmp(t.type, "EOF") == 0)
            break;

        printf("%d\t%d\t%-15s %s\n", t.row, t.col, t.type, t.lexeme);
    }
    fclose(fp);
    return 0;
}