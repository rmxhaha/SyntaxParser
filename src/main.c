#include "mesintoken.h"
#include "stdio.h"


int main()
{
	mtoken_init();
	FILE *f = fopen("s.txt","r");
	int i = 0;
	int linec = 1;
	Token t;
	
	
	while( i != -1 )
	{
		mtoken_adv(f,&i,&linec,&t);
		printf("%s %d\n",t.token,t.line);
		if( strlen(t.token)  == 0 ) 
			printf("Error %d\n", t.line);
		//printf("Token : %s\n", t.token);
		//printf("idx : %d\n",i);
	}
	
	return 0;
}
