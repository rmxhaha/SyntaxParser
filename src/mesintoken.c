#include "mesintoken.h"

#define NSTATE 256
#define NINPUT 256

// state input = target
boolean trans_table[NSTATE][NINPUT][NSTATE]; // state, input, { target states }
boolean start_state[NSTATE];
boolean final_state[NSTATE];

#define epsilon '#'
#define mark '\n'

#define push_back_str(str,c)\
	str[strlen(str)+1] = '\0';\
	str[strlen(str)] = c;


	
void mtoken_init(){
	char c;
	char s,ts;
	int i,k;
	
	memset( trans_table, 0, sizeof(trans_table));
	
	FILE *f = fopen("states","r");
	// read all states and throw it all away b/c it's unnencesarry
	do {
		fscanf(f,"%c",&c);
	} while ( c != mark );
	
	memset( start_state, 0, sizeof(start_state));

	do {
		fscanf(f,"%c",&c);
		start_state[c] = true;
	} while( c != mark );
	
	
	memset( final_state, 0, sizeof(final_state));
	do {
		fscanf(f,"%c",&c);
		final_state[c] = true;
	} while( c != mark );
	
	fclose(f);
	

	f = fopen("transition","r");
	do {
		fscanf(f,"%c%c%c\n",&s,&c,&ts);
		trans_table[s][c][ts] = true;
	} while( s != '#' || c != '#' || ts != '#' );
	
	fclose(f);
}





boolean IsDeadState( boolean *state ){
	int i;
	for( i = 0; i < NSTATE; ++ i ){
		if( state[i] ) return false;
	}

	return true;
}

boolean IsFinalState( boolean *state ){
	int i;
	for( i = 0; i < NSTATE; ++ i ){
		if( state[i] && final_state[i] ) return true;
	}
	
	return false;
}

void ConvertState( boolean *state, char input ){
	boolean tstate[NSTATE];
	memset( tstate,0,sizeof(tstate) );
	int i,k;
	for( i = 0; i < NSTATE; ++ i ){
		// if not at i state
		if( !state[i] ) continue;
		
		// conversion
		for( k = 0; k < NSTATE; ++ k ){
			tstate[k] |= trans_table[i][input][k];
		}
	}
	
	// copy back
	for( i = 0; i < NSTATE; ++ i ){
		state[i] = tstate[i];
	}
}

// f:FILE*
// idx:int*

// I.S. idx awal pembacaan, f sudah di inisialisasi, t sembarangan
// F.S. idx akhir pembacaan, t terdef
void mtoken_adv( FILE *f, int *idx, Token *t ){
	char c;
	int r = 0, i;
	int lf = -1;
	boolean current_state[NSTATE];
	
	memcpy( current_state, start_state, sizeof( current_state ));
	fseek( f, *idx, SEEK_SET );
	
	
	while( !IsDeadState(current_state) ){
		c = fgetc(f);
		if( c == EOF )
			break;
		

		t->token[r] = c;
		ConvertState( current_state, c );
		if( IsFinalState(current_state) ){
			//printf("Final !\n");
			lf = r;
		}
		/*
		printf("%d %c\n", r, c);
		for( i = 0; i < NSTATE; ++ i )
			if( current_state[i] )
				printf("%c", (char)i );
		printf("\n");
		printf("\n");
		*/
		++r;
		
	}
	if( c == EOF ){
		//printf("R1\n");
		(*idx) = -1;

		if( lf == -1 ) 
			t->token[0] = '\0';
		else
			t->token[lf+1] = '\0';
	}
	else if( lf == -1 ) {
		//printf("R2\n");
		(*idx) ++;
		mtoken_adv(f,idx,t);
	}
	else{
		//printf("R3\n");
		(*idx) += lf+1;
		t->token[lf+1] = '\0';
	}
}

