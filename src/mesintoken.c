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
void mtoken_adv_bare( FILE *f, int *idx, int* linecount, Token *t ){
	char c = '\0';
	int r = 0, i;
	int lf = -1;
	boolean current_state[NSTATE];
	boolean sp = false;
	
	memcpy( current_state, start_state, sizeof( current_state ));
	fseek( f, *idx, SEEK_SET );
	
	while( !IsDeadState(current_state) ){
		c = fgetc(f);
		if( c == EOF )
			break;
		// NFA simulation
		t->token[r] = c;
		ConvertState( current_state, c );
		if( IsFinalState(current_state) ){
			//printf("Final !\n");
			lf = r;
		}

		
		// special case comment 
		if( current_state['w'] && c == '\n' ){ (*linecount) ++; ++r; }
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

	t->line = (*linecount);
	
	
	if( c == EOF ){
		(*idx) = -1;

		
		if( lf == -1 ) {
			t->token[0] = '\0';
		}
		else if( t->token[0] != ' ' && t->token[0] != '\t' && t->token[0] != '\n' ){
			// not a special case
			t->token[lf+1] = '\0';
		}
		else {
			t->token[0] = '\0';
		}
	}
	else if( lf == -1 ){
		t->token[0] = '\0';
	}
	else{
		(*idx) += lf+1;
		
		// ignore white spaces and comments
		if( t->token[0] == ' ' || t->token[0] == '\t' || t->token[0] == '\n' || t->token[0] == '{' ){
			// special case
			if( t->token[0] == '\n' ){ (*linecount) ++; (*idx) ++; }	

			mtoken_adv_bare(f,idx,linecount,t);
			return; // don't assign_token_symbol
		}
		else {
			t->token[lf+1] = '\0';
		}
	}
		
	assign_token_symbol(t);
}

void assign_token_symbol( Token *t ){
	char f,c;
	
	if( t->token[0] == '\0' )
		t->symbol = 'P';
	else if( strcmp(t->token,"begin") == 0 ){
		t->symbol = 'B';
	}
	else if( strcmp(t->token,"end") == 0 ){
		t->symbol = 'E';
	}
	else if( strcmp(t->token,"input") == 0 ){
		t->symbol = 'I';
	}
	else if( strcmp(t->token,"output") == 0 ){
		t->symbol = 'O';
	}
	else if( strcmp(t->token,"do") == 0 ){
		t->symbol = 'D';
	}
	else if( strcmp(t->token,"while") == 0 ){
		t->symbol = 'W';
	}
	else if( strcmp(t->token,"if") == 0 ){
		t->symbol = 'J';
	}
	else if( strcmp(t->token,"then") == 0 ){
		t->symbol = 'H';
	}
	else if( strcmp(t->token,"for") == 0 ){
		t->symbol = 'F';		
	}
	else if( strcmp(t->token,"to") == 0 ){
		t->symbol = 'T';
	}
	else if( strcmp(t->token,"else") == 0 ){
		t->symbol = 'S';
	}
	else if( strcmp("<=",t->token) == 0 || strcmp("<>",t->token) == 0 || strcmp(">=",t->token) == 0 ){
		t->symbol = 'C';
	}
	else if( '0' <= t->token[0] && t->token[0] <= '9' ){
		t->symbol = 'N';
	}
	else if( t->token[0] == '{' ){
		t->symbol = 'M';
	}
	else if( strlen(t->token) == 1 ){
		c = t->token[0];

		if( c == '=' )
			t->symbol = 'Q';
		else if( c == '+' || c == '-' || c == '*' )
			t->symbol = 'A';
		else if( c == '<' || c == '>')
			t->symbol = 'C';
		else if( c == '(' )
			t->symbol = 'L';
		else if( c == ')' )
			t->symbol = 'R';
		else 
			t->symbol = 'V';
	}
	else {
		t->symbol = 'V';
	}
	
}


void mtoken_new( TokenMachineState *M, FILE* f ){
	assert( f != 0 );
	M->f = f;
	M->idx = 0;
	M->linecount = 1;

	mtoken_adv_bare(M->f,&M->idx,&M->linecount,&M->NToken);
}

void mtoken_adv( TokenMachineState *M ){
	assert( !mtoken_terminated(*M) );
	// CToken is NToken
	memcpy(&M->CToken,&M->NToken, sizeof(Token));

	if( M->idx != -1 ){
		mtoken_adv_bare(M->f,&M->idx,&M->linecount,&M->NToken);
	}
	else {
		M->NToken.symbol = 'P';
	}
}

boolean mtoken_terminated( TokenMachineState M ){
	if( M.idx == -1 && M.NToken.symbol == 'P' )
		return true;
	else
		return false;
}
