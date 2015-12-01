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

/*
R Error
B Begin
E End
I Input
O Output
D do
W while
F if
T then
L else
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

void mtoken_adv( FILE *, int *fp, int *lc,Token *t);

#endif