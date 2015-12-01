#include "mesintoken.h"
#include "stdio.h"


int main()
{
	mtoken_init();
	FILE *f = fopen("s.txt","r");
	int i = 0;
	Token t;
	
	
	while( i != -1 )
	{
		mtoken_adv(f,&i,&t);
		printf("%s\n",t.token);
		//printf("Token : %s\n", t.token);
		//printf("idx : %d\n",i);
	}
	
	return 0;
}
