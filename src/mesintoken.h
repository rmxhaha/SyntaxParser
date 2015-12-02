#include "stdio.h"
#include "boolean.h"
#include "string.h"
#include "assert.h"

#ifndef MESINTOKEN_H
#define MESINTOKEN_H


typedef struct {
	char symbol; // for later identification
	char token[100];
	int line;
} Token;

typedef struct {
	FILE *f;
	int idx;
	int linecount;
	Token CToken; // current token
	Token NToken; // next token 
} TokenMachineState;

#define mtoken_CToken(M)\
	(M).CToken
#define mtoken_CSymbol(M)\
	(M).CToken.symbol

// memasukan symbol sesuai token yang ada
void assign_token_symbol( Token *t );

// meload table transisi NFA dari file states dan transition
void mtoken_init();

// membaca token selanjutnya cara lawas
void mtoken_adv_bare( FILE *, int *fp, int *lc,Token *t);

// menisialisasi mesin token
void mtoken_new( TokenMachineState *M, FILE* file );

// membaca token selanjutnya
void mtoken_adv( TokenMachineState *M );

// mengatakan apakah token masih berlaku
boolean mtoken_terminated( TokenMachineState M );


#endif