#include "stdio.h"
#include "boolean.h"
#include "string.h"

#ifndef MESINTOKEN_H
#define MESINTOKEN_H


typedef struct {
	char id; // for later identification
	char token[100];
	int line;
} Token;

void mtoken_init();

void mtoken_adv( FILE *, int *fp, int *lc,Token *t);

#endif