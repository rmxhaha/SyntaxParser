#include "stdio.h"

#ifndef MESINTOKEN_H
#define MESINTOKEN_H


typedef struct {
	char id; // for later identification
	char token[100];
	int line;
} Token;


void mtoken_init();

Token mtoken_adv();


#endif