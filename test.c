#include <stdio.h>
#include <stdlib.h>

void bin_rec(int length,int i, char *numbers){
    if(length==i){
        numbers[i]='\0';
        printf("%s\n",numbers);
        return;
    }

    numbers[i]='0';
    bin_rec(length,i+1,numbers);
    numbers[i]='1';
    bin_rec(length,i+1,numbers);
}

void print_binary_numbers ( int length ) {
	char *buffer = (char*)malloc((1+length)*sizeof(char));
    bin_rec(length,0,buffer);
    free(buffer);

}


int main ( void ) {
	//print_binary_numbers( 1 );
	//print_binary_numbers( 2 );
	print_binary_numbers( 3 );
	//print_binary_numbers( 5 );

	return 0;
}

