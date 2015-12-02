#include "mesintoken.h"
#include "stdio.h"


int fail = 0;

void error(char s, TokenMachineState *M) {
    if (!fail) {
        puts("Error!");
        printf("Line: %d\n", (*M).CToken.line);
        if (s==(*M).CToken.line) {
            puts("Syntax error");
        }
        else if (s=='L') {
            printf("Expected '(', instead get '%s'\n", (*M).CToken.token);
        }
        else if (s=='R') {
            printf("Expected ')', instead get '%s'\n", (*M).CToken.token);
        }
        else if (s=='B') {
            printf("Expected 'begin', instead get '%s'\n", (*M).CToken.token);
        }
        else if (s=='E') {
            printf("Expected 'end', instead get '%s'\n", (*M).CToken.token);
        }
        else if (s=='C') {
            printf("Expected bool operator, instead get '%s'\n", (*M).CToken.token);
        }
        else if (s=='V'||s=='Q') {
            puts("Unexpected symbol");
        }
        else if (s=='A') {
            puts("Invalid arithmatic operator");
        }
        //printf("Because %c seharusnya %c\n", (*M).CToken.symbol, s);
        fail = 1;
    }
}

int accept(char s, TokenMachineState *M) {
    if ((*M).CToken.symbol == s) {
        if (!mtoken_terminated(*M)) {
            mtoken_adv(M);
        }
        return 1;
    }
    return 0;
}

int expect(char s, TokenMachineState *M) {

    //printf("%s %c %d\n",t.token,t.symbol,t.line);
    if (accept(s, M))
        return 1;
    error(s, M);
    return 0;
}

void operasi(TokenMachineState *M) {
    //puts("op");
    if (accept('V', M)) {
        ;
    }
    else if (accept('N', M)) {
        ;
    }
    else if (accept('L', M)) {
        operasi(M);
        expect('R', M);
    }
    else {
        error((*M).CToken.symbol, M);
    }
    if (accept('A', M)) {
        //puts("arith");
        operasi(M);
    }
}

void kondisi(TokenMachineState *M) {
    //puts("kondisi");
    if (accept('V', M)) {
        ;
    }
    else if (accept('N', M)) {
        ;
    }
    else if (accept('L', M)) {
        operasi(M);
        expect('R', M);
    }
    else {
        error((*M).CToken.symbol, M);
    }
    expect('C', M);
    if (accept('V', M)) {
        ;
    }
    else if (accept('N', M)) {
        ;
    }
    else if (accept('L', M)) {
        operasi(M);
        expect('R', M);
    }
    else {
        error((*M).CToken.symbol, M);
    }
}

void isi(TokenMachineState *M);

void block(TokenMachineState *M) {
    expect('B', M);
    //puts("begin");
    //printf("f %d\n", fail);
    while (!accept('E', M) && !fail) {
        //puts("masuk");
        isi(M);
    }
    //puts("end");
}

void isi(TokenMachineState *M) {
    if (accept('I', M)) {
        //puts("input");
        expect('L', M);
        //puts("(");
        expect('V', M);
        //puts("var");
        expect('R', M);
        //puts(")");
    }
    else if (accept('O', M)) {
        //puts("output");
        expect('L', M);
        operasi(M);
        expect('R', M);
    }
    else if (accept('J', M)) {
        //puts("if");
        expect('L', M);
        kondisi(M);
        expect('R', M);
        expect('H', M);
        //puts("then");
        block(M);
        if (accept('S', M)) {
            //puts("else");
            block(M);
        }
    }
    else if (accept('F', M)) {
        //puts("for");
        expect('L', M);
        expect('V', M);
        expect('Q', M);
        expect('N', M);
        expect('T', M);
        expect('N', M);
        expect('R', M);
        expect('D', M);
        block(M);
    }
    else if (accept('D', M)) {
        //puts("do");
        while (!accept('W', M) && !fail) {
            isi(M);
        }
        //puts("while");
        expect('L', M);
        kondisi(M);
        expect('R', M);
    }
    else if (accept('V', M)) {
        //puts("assignment");
        expect('Q', M);
        //puts("=");
        operasi(M);
    }
    else {
        error((*M).CToken.symbol, M);
    }
}

void mainparser(TokenMachineState *M) {
    mtoken_adv(M);
    expect('V', M);
    //puts("Begin");
    while (!accept('E', M) && !fail) {
        isi(M);
    }
    //puts("end.");
    //printf("Sukses\n");
}

int main( int argc, char *argv[] )
{
	if( argc == 1 ){
		printf("please add filename into parameter\n");
		printf("e.g. %s input.txt\n", argv[0]);
		return 0;
	}

	
	mtoken_init();
	FILE *f = fopen(argv[1],"r");
	
	if( f == NULL ){
		printf("File cannot be opened\n");
		return 0;
	}

	TokenMachineState M;
	mtoken_new( &M, f );
/*
	while( !mtoken_terminated(M) ){
		mtoken_adv(&M);
		printf("%s %c %d\n",M.CToken.token,M.CToken.symbol,M.CToken.line);
		if( M.CToken.symbol == 'P' )
			printf("Error %d\n", M.CToken.line);
	}
	return 0;
	*/
    mainparser(&M);

    if (!fail) {
        printf("Syntax valid!!\n");
    }

	return 0;
}
