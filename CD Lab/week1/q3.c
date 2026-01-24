#include <stdio.h>
#include <string.h>
#define MAX 1000
int main(){
    FILE *f1=fopen("dummy.txt","r");
    FILE *f2=fopen("reversed.txt","r");
    FILE *fm=fopen("merged.txt","w");
    char l1[MAX],l2[MAX];
    if(!f1||!f2||!fm) return 1;
    while(1){
        if(fgets(l1,MAX,f1)){
            fputs(l1,fm);
            if(l1[strlen(l1)-1]!='\n') fputc('\n',fm);
        }
        if(fgets(l2,MAX,f2)){
            fputs(l2,fm);
            if(l2[strlen(l2)-1]!='\n') fputc('\n',fm);
        }
        if(feof(f1)&&feof(f2)) break;
    }
    fclose(f1);
    fclose(f2);
    fclose(fm);
    return 0;
}
