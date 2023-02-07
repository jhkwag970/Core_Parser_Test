#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "core.h"
#include "tree.h"
#include "printer.h"
#include "parser.h"

#define TAB 4

void printProcedure();
void printDeclSeq();
void printStmtSeq();
void printDecl();
void printDeclInteger();
void printDeclRecord();
void printStmt();
void printAssign();
void printIf();
void printLoop();
void printOut();
void printIndex();
void printExpr();
void printTerm();
void printFactor();
void printCond();
void printCmpr();

extern struct nodeProcedure *p;

/*
*
* Helper functions
*
*/

static void indents(int indent) {
	for (int i=0; i<indent; i++) {
		printf("  ");
	}
}

/*
*
* Print functions go here
*
*/

void printTree(){
	//printf("printer %d\n", p);
	printProcedure();
}

void printProcedure(){
	printf("procedure ");
	printf("%s ", p->id);
	printf("is\n");

	printDeclSeq(p->ds);
	printf("begin\n");

	printStmtSeq(p->ss);

	printf("end");
}


void printDeclSeq(struct nodeDeclSeq *ds2){
	printDecl(ds2->d);
	if(ds2->ds != NULL){
		printDeclSeq(ds2->ds);
	}
}

void printDecl(struct nodeDecl *d2){
	if(d2->di != NULL){
		printDeclInteger(d2->di);
	}
	if(d2->dr != NULL){
		printDeclRecord(d2->dr);
	}
}

void printDeclInteger(struct nodeDeclInteger *di2){
	indents(TAB);
	printf("integer %s;\n",di2->id);
}

void printDeclRecord(struct nodeDeclRecord *dr2){
	indents(TAB);
	printf("record %s;\n",dr2->id);
}

void printStmtSeq(){

}
