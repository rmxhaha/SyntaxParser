#include "stdio.h"
#include "string.h"

int main(){
	// state generator
	char c;
	
	
	for( c = 'a'; c <= 'z'; ++ c ) printf("p%cq\n", c);
	for( c = 'A'; c <= 'Z'; ++ c ) printf("p%cq\n", c);

	
	for( c = '0'; c <= '9'; ++ c ) printf("q%cq\n", c);
	for( c = 'a'; c <= 'z'; ++ c ) printf("q%cq\n", c);
	for( c = 'A'; c <= 'Z'; ++ c ) printf("q%cq\n", c);
	
	char one_char_state[] = "=+-*()";
	
	int i;
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