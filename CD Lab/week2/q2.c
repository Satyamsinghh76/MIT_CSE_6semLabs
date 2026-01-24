#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    FILE *fin, *fout;
    char line[1024];
    if (argc != 3)
    {
        printf("Usage: %s <input_c_file> <output_file>\n", argv[0]);
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
    while (fgets(line, sizeof(line), fin) != NULL)
    {
        if (line[0] != '#')
        {
            fputs(line, fout);
        }
    }
    fclose(fin);
    fclose(fout);

    printf("Preprocessor directives removed successfully.\n");
    return 0;
}
