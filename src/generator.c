#include "stdio.h"
#include "string.h"
#include "ctype.h"

#define FOR_ALL_TYPEABLE(c)\
	for( c = '!'; c <= '~'; ++ c )\

int main(){
	// state generator
	char c;

	int i;
	for( i = 0; i <=255; ++ i){
		c = (char)i;
		printf("%c\n", c);
	}

	return 0;

	for( c = 'a'; c <= 'z'; ++ c ) printf("p%cq\n", c);
	for( c = 'A'; c <= 'Z'; ++ c ) printf("p%cq\n", c);


	for( c = '0'; c <= '9'; ++ c ) printf("q%cq\n", c);
	for( c = 'a'; c <= 'z'; ++ c ) printf("q%cq\n", c);
	for( c = 'A'; c <= 'Z'; ++ c ) printf("q%cq\n", c);

	char one_char_state[] = "=+-*()";


	for( i = 0; i < strlen(one_char_state); ++ i ) printf("p%cr\n", one_char_state[i] );


	/*
		<
		<=
		<>
	*/
	printf("p<s\n");
	printf("s=t\n");
	printf("s>t\n");

	/*
		>
		>=
	*/
	printf("p>u\n");
	printf("u=v\n");

	/*
		{<ee>}
	*/

	printf("p{w\n");
	// all char except }
	for( c = '!'; c <= 'z'; ++ c ){
		if( c != '}')
		{
			printf("w%cw\n", c);
		}
	}

	printf("w}x\n");

	// final states
	printf("qstuvx\n");




	return 0;
}
