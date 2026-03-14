#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char token[50];
FILE *fp;
void Program();
void identifier_list();
void statement_list();
void statement();
void assign_stat();
void expn();
void eprime();
void simple_expn();
void seprime();
void term();
void tprime();
void factor();
void relop();
void addop();
void mulop();

void match(char *expected);
void error(char *msg);
int getToken();

/* Read next token */

int getToken()
{
    return fscanf(fp,"%s",token);
}

/* Error handler */

void error(char *msg)
{
    printf("Syntax Error: %s near token '%s'\n",msg,token);
    exit(1);
}

/* Match expected token */

void match(char *expected)
{
    if(strcmp(token,expected)==0)
    {
        if(getToken()<1)
            strcpy(token,"EOF");
    }
    else
    {
        printf("Syntax Error: expected '%s' but found '%s'\n",expected,token);
        exit(1);
    }
}

/* Program → main ( ) { identifier_list statement_list } */

void Program()
{
    match("main");
    match("(");
    match(")");
    match("{");

    identifier_list();
    statement_list();

    match("}");
}

/* identifier_list → id | id , identifier_list | id[num] | id[num] , identifier_list */

void identifier_list()
{
    match("id");

    if(strcmp(token,"[")==0)
    {
        match("[");
        match("num");
        match("]");
    }

    if(strcmp(token,",")==0)
    {
        match(",");
        identifier_list();
    }
}

/* statement_list → statement statement_list | ε */

void statement_list()
{
    while(strcmp(token,"id")==0)
    {
        statement();
    }
}

/* statement → assign_stat ; */

void statement()
{
    assign_stat();
    match(";");
}

/* assign_stat → id = expn */

void assign_stat()
{
    match("id");
    match("=");
    expn();
}

/* expn → simple_expn eprime */

void expn()
{
    simple_expn();
    eprime();
}

/* eprime → relop simple_expn | ε */

void eprime()
{
    if(strcmp(token,"==")==0 || strcmp(token,"!=")==0 ||
       strcmp(token,"<")==0 || strcmp(token,">")==0 ||
       strcmp(token,"<=")==0 || strcmp(token,">=")==0)
    {
        relop();
        simple_expn();
    }
}

/* simple_expn → term seprime */

void simple_expn()
{
    term();
    seprime();
}

/* seprime → addop term seprime | ε */

void seprime()
{
    if(strcmp(token,"+")==0 || strcmp(token,"-")==0)
    {
        addop();
        term();
        seprime();
    }
}

/* term → factor tprime */

void term()
{
    factor();
    tprime();
}

/* tprime → mulop factor tprime | ε */

void tprime()
{
    if(strcmp(token,"*")==0 || strcmp(token,"/")==0 || strcmp(token,"%")==0)
    {
        mulop();
        factor();
        tprime();
    }
}

/* factor → id | num */

void factor()
{
    if(strcmp(token,"id")==0)
        match("id");

    else if(strcmp(token,"num")==0)
        match("num");

    else
        error("Invalid factor");
}

/* relop → == | != | < | > | <= | >= */

void relop()
{
    if(strcmp(token,"==")==0) match("==");
    else if(strcmp(token,"!=")==0) match("!=");
    else if(strcmp(token,"<")==0) match("<");
    else if(strcmp(token,">")==0) match(">");
    else if(strcmp(token,"<=")==0) match("<=");
    else if(strcmp(token,">=")==0) match(">=");
    else error("Invalid relational operator");
}

/* addop → + | - */

void addop()
{
    if(strcmp(token,"+")==0) match("+");
    else if(strcmp(token,"-")==0) match("-");
    else error("Invalid addition operator");
}

/* mulop → * | / | % */

void mulop()
{
    if(strcmp(token,"*")==0) match("*");
    else if(strcmp(token,"/")==0) match("/");
    else if(strcmp(token,"%")==0) match("%");
    else error("Invalid multiplication operator");
}

/* Main Function */

int main()
{
    fp = fopen("input.txt","r");

    if(fp==NULL)
    {
        printf("Input file not found\n");
        exit(1);
    }

    if(getToken()<1)
    {
        printf("Empty input file\n");
        exit(1);
    }

    Program();

    if(strcmp(token,"EOF")!=0)
        error("Unexpected tokens after program");

    fclose(fp);

    printf("Parsing Successful\n");

    return 0;
}