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
static int indentSize;

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
	indentSize=TAB;
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
	indents(indentSize);
	printf("integer %s;\n",di2->id);
}

void printDeclRecord(struct nodeDeclRecord *dr2){
	indents(indentSize);
	printf("record %s;\n",dr2->id);
}

void printStmtSeq(struct nodeStmtSeq *ss2){
	printStmt(ss2->s);

	if(ss2->ss != NULL){
		printStmtSeq(ss2->ss);
	}
}

void printStmt(struct nodeStmt *s2){
	if(s2->ass != NULL){
		printAssign(s2->ass);
	}
	if(s2->i != NULL){
		printIf(s2->i);
	}
	if(s2->lp != NULL){
		printLoop(s2->lp);
	}
	if(s2->out != NULL){
		printOut(s2->out);
	}
}

void printAssign(struct nodeAssign *ass2){
	indents(indentSize);
	printf("%s", ass2->id);
	if(ass2->idx != NULL){
		printIndex(ass2->idx);
		printf(":=");
		printExpr(ass2->exp);
	}else if(ass2->exp != NULL){
		printf(":=new record[");
		printExpr(ass2->exp);
		printf("]");
	}else if(ass2->id2 != NULL){
		printf(":=record %s", ass2->id2);
	}	
	printf(";\n");

}

void printIndex(struct nodeIndex *idx2){
	if(idx2->exp != NULL){
		printf("[");
		printExpr(idx2->exp);
		printf("]");
	}
}

void printIf(struct nodeIf *i2){

}

void printLoop(struct nodeLoop *lp2){

}

void printOut(struct nodeOut *out2){

}

void printExpr(struct nodeExpr *exp2){
	printTerm(exp2->tm);

	if(exp2->math != NULL){
		if(!strcmp(exp2->math, "+")){
			printf("+");
		}else if(!strcmp(exp2->math, "-")){
			printf("-");
		}
		printExpr(exp2->exp);
	}

}

void printTerm(struct nodeTerm *tm2){
	printFactor(tm2->fac);

	if(tm2->math != NULL){
		if(!strcmp(tm2->math, "*")){
			printf("*");
		}else if(!strcmp(tm2->math, "/")){
			printf("/");
		}
		printTerm(tm2->tm);
	}
	
}

void printFactor(struct nodeFactor *fac2){
	if(fac2->id != NULL){
		printf("%s", fac2->id);
		if(fac2->exp != NULL){
			printf("[");
			printExpr(fac2->exp);
			printf("]");
		}
	}else if(fac2->cnt != -1){
		printf("%d", fac2->cnt);
	}else if(fac2->exp != NULL){
		printf("(");
		printExpr(fac2->exp);
		printf(")");
	}else{
		printf("in()");
	}
}
