#include<stdio.h>
int main (void){

	int number,total,exists=0;

	printf("Zadejte pocet cisel: \n");
	scanf("%d",&total);

	for(int i=0 ; i<total;i++){
		printf("Zadejte cislo\n");
		scanf("%d",&number);
		if(number%2==0){
			
			exists++;
		}

	
	}

	printf("Celkem je %d sudych cisel z celkove %d zadanych.\n",exists,total);
	
	return 0;
}
