#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int curr = 0;
char str[100];

void S();
void T();
void Tprime();

void invalid()
{
    printf("--------- ERROR ---------\n");
    exit(0);
}

void valid()
{
    printf("-------- SUCCESS --------\n");
    exit(0);
}

/* S → a | > | ( T ) */
void S()
{
    if(str[curr] == 'a')
    {
        curr++;
    }
    else if(str[curr] == '>')
    {
        curr++;
    }
    else if(str[curr] == '(')
    {
        curr++;
        T();
        if(str[curr] == ')')
            curr++;
        else
            invalid();
    }
    else
        invalid();
}

/* T → S T' */
void T()
{
    S();
    Tprime();
}

/* T' → , S T' | ε */
void Tprime()
{
    if(str[curr] == ',')
    {
        curr++;
        S();
        Tprime();
    }
}

int main()
{
    printf("Enter string: ");
    scanf("%s", str);

    S();

    if(str[curr] == '$')
        valid();
    else
        invalid();
}