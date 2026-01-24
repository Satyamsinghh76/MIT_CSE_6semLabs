#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    FILE *fin, *fout;
    int ch;
    int in_space = 0;
    if (argc != 3)
    {
        printf("Usage: %s <input_file> <output_file>\n", argv[0]);
        return 1;
    }
    fin = fopen(argv[1], "r");
    if (fin == NULL)
    {
        printf("Error: Cannot open input file.\n");
        return 1;
    }
    fout = fopen(argv[2], "w");
    if (fout == NULL)
    {
        printf("Error: Cannot open output file.\n");
        fclose(fin);
        return 1;
    }
    while ((ch = fgetc(fin)) != EOF)
    {
        if (ch == ' ' || ch == '\t')
        {
            if (!in_space)
            {
                fputc(' ', fout);
                in_space = 1;
            }
        }
        else
        {
            fputc(ch, fout);
            in_space = 0;
            if (ch == '\n')
                in_space = 0;
        }
    }
    fclose(fin);
    fclose(fout);
    printf("File processed successfully.\n");
    return 0;
}
