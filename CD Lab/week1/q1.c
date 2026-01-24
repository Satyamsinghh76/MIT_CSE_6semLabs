#include<stdio.h>
#include<stdlib.h>
int main()
{
	FILE *fptr1;
	int lcount=0,c_count=0;
	fptr1 = fopen("dummy.txt","r");
	if(fptr1 == NULL){
		printf("Coudn't Open the file\n");
		exit(0);
	}
	char c = fgetc(fptr1);
	while(c != EOF){
		if(c == '\n'){
			lcount++;
		}
		else{
			c_count++;
		}
		c = fgetc(fptr1);
	}
	printf("No. of Lines:%d\n",lcount);
	printf("No. of Characaters:%d\n",c_count);
	fclose(fptr1);
	return 0;
}