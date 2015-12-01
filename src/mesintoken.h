#include "stdio.h"
#include "boolean.h"
#include "string.h"

#ifndef MESINTOKEN_H
#define MESINTOKEN_H


typedef struct {
	char symbol; // for later identification
	char token[100];
	int line;
} Token;

void assign_token_symbol( Token *t );

void mtoken_init();

void mtoken_adv( FILE *, int *fp, int *lc,Token *t);

#endif