#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MAX 100
const char *keywords[] = {
    "auto","break","case","char","const","continue","default","do",
    "double","else","enum","extern","float","for","goto","if","int",
    "long","register","return","short","signed","sizeof","static",
    "struct","switch","typedef","union","unsigned","void","volatile","while"
};
int isKeyword(char *word)
{
    int i;
    int count = sizeof(keywords) / sizeof(keywords[0]);

    for (i = 0; i < count; i++)
    {
        if (strcmp(word, keywords[i]) == 0)
            return 1;
    }
    return 0;
}
void printUpper(char *word)
{
    int i;
    for (i = 0; word[i]; i++)
        putchar(toupper(word[i]));
}
int main(int argc, char *argv[])
{
    FILE *fp;
    char word[MAX];
    int c, i = 0;

    if (argc != 2)
    {
        printf("Usage: %s <input_c_file>\n", argv[0]);
        return 1;
    }

    fp = fopen(argv[1], "r");
    if (fp == NULL)
    {
        printf("Error: Cannot open file.\n");
        return 1;
    }

    while ((c = fgetc(fp)) != EOF)
    {
        if (isalpha(c) || c == '_')
        {
            word[i++] = c;

            while ((c = fgetc(fp)) != EOF && (isalnum(c) || c == '_'))
            {
                word[i++] = c;
            }

            word[i] = '\0';
            i = 0;
            if (isKeyword(word))
                printUpper(word);
            else
                printf("%s", word);

            if (c != EOF)
                putchar(c);
        }
        else
        {
            putchar(c);
        }
    }
    fclose(fp);
    return 0;
}
