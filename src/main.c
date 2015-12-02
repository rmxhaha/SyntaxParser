#include "mesintoken.h"
#include "stdio.h"


int main()
{
	mtoken_init();
	FILE *f = fopen("s.txt","r");
	int i = 0;
	int linec = 1;
	Token t;
	TokenMachineState M;
	
	/*
	while( i != -1 )
	{
		mtoken_adv_bare(f,&i,&linec,&t);
		printf("%s %c %d\n",t.token,t.symbol,t.line);
		if( strlen(t.token)  == 0 ) 
			printf("Error %d\n", t.line);
		//printf("Token : %s\n", t.token);
		//printf("idx : %d\n",i);
	}
	*/
	
	mtoken_new( &M, f );
		
	while( !mtoken_terminated(M) ){
		mtoken_adv(&M);
		printf("%s %c %d\n",M.CToken.token,M.CToken.symbol,M.CToken.line);
		if( mtoken_CSymbol(M) == 'R' ) 
			printf("Error %d\n", M.CToken.line);
	}
	
	
	return 0;
}
