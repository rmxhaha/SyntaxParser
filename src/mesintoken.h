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

/*
P Error
B Begin
E End
I input
O output
D do
W while
H if
J then
S else
F for
T to
C conditional < > <= >=
N Number
M Comment
Q khusus =
A arthimatic
L khusus (
R khusus )
V variable
*/

void assign_token_symbol( Token *t );

void mtoken_init();

void mtoken_adv_bare( FILE *, int *fp, int *lc,Token *t);

void mtoken_new( TokenMachineState *M, FILE* file );

void mtoken_adv( TokenMachineState *M );

boolean mtoken_terminated( TokenMachineState M );


#endif