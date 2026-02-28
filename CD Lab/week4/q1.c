#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX_LEN 50
#define MAX_SYM 100

typedef enum {
    KEYWORD,
    IDENTIFIER,
    NUMBER,
    OPERATOR,
    DELIMITER,
    EOF_TOKEN
} TokenType;

typedef struct {
    char lexeme[MAX_LEN];
    int row;
    int col;
    TokenType type;
} Token;

typedef struct {
    char name[MAX_LEN];
    char type[MAX_LEN];
    int scope;              // 0 = global, 1 = local
    int line_declared;
} Symbol;

Symbol globalTable[MAX_SYM];
Symbol localTable[MAX_SYM];
int globalCount = 0, localCount = 0;

FILE *fp;
FILE *fout;  // output file

int row = 1, col = 0;

char *keywords[] = {
    "int", "float", "char", "double", "void",
    "if", "else", "while", "for", "return"
};
int keywordCount = 10;

int isKeyword(char *str) {
    for (int i = 0; i < keywordCount; i++)
        if (strcmp(str, keywords[i]) == 0)
            return 1;
    return 0;
}

int isDataType(char *str) {
    return (!strcmp(str, "int") ||
            !strcmp(str, "float") ||
            !strcmp(str, "char") ||
            !strcmp(str, "double") ||
            !strcmp(str, "void"));
}

int isDelimiter(char ch) {
    return (ch == ';' || ch == ',' || ch == '(' ||
            ch == ')' || ch == '{' || ch == '}');
}

int isOperator(char ch) {
    return (ch == '+' || ch == '-' || ch == '*' ||
            ch == '/' || ch == '=' || ch == '<' || ch == '>');
}

char getChar() {
    char ch = fgetc(fp);
    col++;
    return ch;
}

void retract() {
    fseek(fp, -1, SEEK_CUR);
    col--;
}

void insertGlobal(Symbol s) {
    globalTable[globalCount++] = s;
}

void insertLocal(Symbol s) {
    localTable[localCount++] = s;
}

Token getNextToken() {
    Token token;
    char ch;
    while ((ch = getChar()) != EOF) {
        if (ch == ' ' || ch == '\t') continue;
        if (ch == '\n') { row++; col = 0; continue; }

        if (ch == '#') {
            while (ch != '\n' && ch != EOF)
                ch = getChar();
            continue;
        }

        if (ch == '/') {
            char next = getChar();
            if (next == '/') {
                while (ch != '\n' && ch != EOF)
                    ch = getChar();
                continue;
            } else if (next == '*') {
                while (1) {
                    ch = getChar();
                    if (ch == '*' && getChar() == '/') break;
                }
                continue;
            } else {
                retract();
            }
        }

        if (ch == '"') {
            while ((ch = getChar()) != '"' && ch != EOF);
            continue;
        }

        if (isalpha(ch) || ch == '_') {
            int i = 0;
            token.lexeme[i++] = ch;
            while (isalnum(ch = getChar()) || ch == '_')
                token.lexeme[i++] = ch;
            token.lexeme[i] = '\0';
            retract();
            token.row = row;
            token.col = col - strlen(token.lexeme);
            token.type = isKeyword(token.lexeme) ? KEYWORD : IDENTIFIER;
            return token;
        }

        if (isdigit(ch)) {
            int i = 0;
            token.lexeme[i++] = ch;
            while (isdigit(ch = getChar()))
                token.lexeme[i++] = ch;
            token.lexeme[i] = '\0';
            retract();
            token.row = row;
            token.col = col - strlen(token.lexeme);
            token.type = NUMBER;
            return token;
        }

        if (isOperator(ch) || isDelimiter(ch)) {
            token.lexeme[0] = ch;
            token.lexeme[1] = '\0';
            token.row = row;
            token.col = col;
            token.type = OPERATOR;
            return token;
        }
    }
    token.type = EOF_TOKEN;
    return token;
}

int main() {
    fp = fopen("input2.c", "r");
    if (!fp) {
        printf("Error opening input file\n");
        return 1;
    }

    fout = fopen("output2.txt", "w");
    if (!fout) {
        printf("Error opening output file\n");
        return 1;
    }

    Token t;
    int insideFunction = 0;

    while ((t = getNextToken()).type != EOF_TOKEN) {
        if (t.type == KEYWORD && isDataType(t.lexeme)) {
            Token id = getNextToken();
            Symbol s;
            strcpy(s.name, id.lexeme);
            strcpy(s.type, t.lexeme);
            s.line_declared = id.row;
            if (insideFunction) {
                s.scope = 1;
                insertLocal(s);
            } else {
                s.scope = 0;
                insertGlobal(s);
            }
        }
        if (strcmp(t.lexeme, "{") == 0) insideFunction = 1;
        if (strcmp(t.lexeme, "}") == 0) insideFunction = 0;
    }

    // Write Global Table
    fprintf(fout, "GLOBAL SYMBOL TABLE\n");
    fprintf(fout, "Name\tType\tLine\n");
    for (int i = 0; i < globalCount; i++) {
        fprintf(fout, "%s\t%s\t%d\n",
                globalTable[i].name,
                globalTable[i].type,
                globalTable[i].line_declared);
    }

    // Write Local Table
    fprintf(fout, "\nLOCAL SYMBOL TABLE\n");
    fprintf(fout, "Name\tType\tLine\n");
    for (int i = 0; i < localCount; i++) {
        fprintf(fout, "%s\t%s\t%d\n",
                localTable[i].name,
                localTable[i].type,
                localTable[i].line_declared);
    }

    fclose(fp);
    fclose(fout);
    printf("Symbol table generation complete. Output written to 'symbol_table_output.txt'\n");
    return 0;
}


// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <ctype.h>
// #define MAX_LEN 50
// #define MAX_SYM 100
// typedef enum {
//     KEYWORD,
//     IDENTIFIER,
//     NUMBER,
//     OPERATOR,
//     DELIMITER,
//     EOF_TOKEN
// } TokenType;
// typedef struct {
//     char lexeme[MAX_LEN];
//     int row;
//     int col;
//     TokenType type;
// } Token;
// typedef struct {
//     char name[MAX_LEN];
//     char type[MAX_LEN];
//     int scope;              // 0 = global, 1 = local
//     int line_declared;
// } Symbol;
// Symbol globalTable[MAX_SYM];
// Symbol localTable[MAX_SYM];
// int globalCount = 0, localCount = 0;
// FILE *fp;
// int row = 1, col = 0;
// char *keywords[] = {
//     "int", "float", "char", "double", "void",
//     "if", "else", "while", "for", "return"
// };
// int keywordCount = 10;
// int isKeyword(char *str) {
//     for (int i = 0; i < keywordCount; i++) {
//         if (strcmp(str, keywords[i]) == 0)
//             return 1;
//     }
//     return 0;
// }
// int isDataType(char *str) {
//     return (!strcmp(str, "int") ||
//             !strcmp(str, "float") ||
//             !strcmp(str, "char") ||
//             !strcmp(str, "double") ||
//             !strcmp(str, "void"));
// }
// int isDelimiter(char ch) {
//     return (ch == ';' || ch == ',' || ch == '(' ||
//             ch == ')' || ch == '{' || ch == '}');
// }
// int isOperator(char ch) {
//     return (ch == '+' || ch == '-' || ch == '*' ||
//             ch == '/' || ch == '=' || ch == '<' || ch == '>');
// }
// char getChar() {
//     char ch = fgetc(fp);
//     col++;
//     return ch;
// }
// void retract() {
//     fseek(fp, -1, SEEK_CUR);
//     col--;
// }
// void insertGlobal(Symbol s) {
//     globalTable[globalCount++] = s;
// }
// void insertLocal(Symbol s) {
//     localTable[localCount++] = s;
// }
// Token getNextToken() {
//     Token token;
//     char ch;
//     while ((ch = getChar()) != EOF) {
//         if (ch == ' ' || ch == '\t')
//             continue;
//         if (ch == '\n') {
//             row++;
//             col = 0;
//             continue;
//         }
//         if (ch == '#') {
//             while (ch != '\n' && ch != EOF)
//                 ch = getChar();
//             continue;
//         }
//         if (ch == '/') {
//             char next = getChar();
//             if (next == '/') {   
//                 while (ch != '\n' && ch != EOF)
//                     ch = getChar();
//                 continue;
//             } else if (next == '*') { 
//                 while (1) {
//                     ch = getChar();
//                     if (ch == '*' && getChar() == '/')
//                         break;
//                 }
//                 continue;
//             } else {
//                 retract();
//             }
//         }
//         if (ch == '"') {
//             while ((ch = getChar()) != '"' && ch != EOF);
//             continue;
//         }
//         if (isalpha(ch) || ch == '_') {
//             int i = 0;
//             token.lexeme[i++] = ch;
//             while (isalnum(ch = getChar()) || ch == '_')
//                 token.lexeme[i++] = ch;

//             token.lexeme[i] = '\0';
//             retract();
//             token.row = row;
//             token.col = col - strlen(token.lexeme);
//             token.type = isKeyword(token.lexeme) ? KEYWORD : IDENTIFIER;
//             return token;
//         }
//         if (isdigit(ch)) {
//             int i = 0;
//             token.lexeme[i++] = ch;
//             while (isdigit(ch = getChar()))
//                 token.lexeme[i++] = ch;
//             token.lexeme[i] = '\0';
//             retract();
//             token.row = row;
//             token.col = col - strlen(token.lexeme);
//             token.type = NUMBER;
//             return token;
//         }
//         if (isOperator(ch) || isDelimiter(ch)) {
//             token.lexeme[0] = ch;
//             token.lexeme[1] = '\0';
//             token.row = row;
//             token.col = col;
//             token.type = OPERATOR;
//             return token;
//         }
//     }
//     token.type = EOF_TOKEN;
//     return token;
// }
// int main() {
//     fp = fopen("input2.c", "r");
//     if (!fp) {
//         printf("Error opening file\n");
//         return 1;
//     }
//     Token t;
//     int insideFunction = 0;
//     while ((t = getNextToken()).type != EOF_TOKEN) {
//         if (t.type == KEYWORD && isDataType(t.lexeme)) {
//             Token id = getNextToken();
//             Symbol s;
//             strcpy(s.name, id.lexeme);
//             strcpy(s.type, t.lexeme);
//             s.line_declared = id.row;
//             if (insideFunction) {
//                 s.scope = 1;
//                 insertLocal(s);
//             } else {
//                 s.scope = 0;
//                 insertGlobal(s);
//             }
//         }
//         if (strcmp(t.lexeme, "{") == 0)
//             insideFunction = 1;
//         if (strcmp(t.lexeme, "}") == 0)
//             insideFunction = 0;
//     }
//     fclose(fp);
//     printf("\nGLOBAL SYMBOL TABLE\n");
//     printf("Name\tType\tLine\n");
//     for (int i = 0; i < globalCount; i++) {
//         printf("%s\t%s\t%d\n",
//                globalTable[i].name,
//                globalTable[i].type,
//                globalTable[i].line_declared);
//     }
//     printf("\nLOCAL SYMBOL TABLE\n");
//     printf("Name\tType\tLine\n");
//     for (int i = 0; i < localCount; i++) {
//         printf("%s\t%s\t%d\n",
//                localTable[i].name,
//                localTable[i].type,
//                localTable[i].line_declared);
//     }
//     return 0;
// }
