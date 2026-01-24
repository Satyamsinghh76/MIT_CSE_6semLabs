#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *fp1, *fp2;
    long size = 0;
    int ch;
    fp1 = fopen("dummy.txt", "r");
    if (fp1 == NULL) {
        printf("Couldn't open input file\n");
        exit(1);
    }
    fp2 = fopen("reversed.txt", "w");
    if (fp2 == NULL) {
        printf("Couldn't open output file\n");
        fclose(fp1);
        exit(1);
    }
    while ((ch = fgetc(fp1)) != EOF) {
        size++;
    }
    printf("Number of characters: %ld\n", size);
    printf("Size of file: %ld bytes\n", size);
    int i = size - 1;
    while (i >= 0) {
        fseek(fp1, i, SEEK_SET);
        ch = fgetc(fp1);
        fputc(ch, fp2);
        i--;
    }
    fclose(fp1);
    fclose(fp2);
    return 0;
}

