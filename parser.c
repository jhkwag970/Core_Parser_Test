#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "scanner.h"
#include "core.h"
#include "tree.h"
#include "parser.h"

void parseProcedure();
void parseDeclSeq();
void parseStmtSeq();
void parseDecl();
void parseDeclInteger();
void parseDeclRecord();
void parseStmt();
void parseAssign();
void parseIf();
void parseLoop();
void parseOut();
void parseIndex();
void parseExpr();
void parseTerm();
void parseFactor();
void parseCond();
void parseCmpr();




static struct nodeProcedure *p;
static int expected;

/*
*
* Helper functions
*
*/
// Converts token value to a string
static void tokenString(char* str, int current) {
	switch (current) {
	  case AND : strcpy(str, "AND"); break;
	  case BEGIN : strcpy(str, "BEGIN"); break;
	  case DO : strcpy(str, "DO"); break;
	  case ELSE : strcpy(str, "ELSE"); break;
	  case END : strcpy(str, "END"); break;
	  case IF : strcpy(str, "IF"); break;
	  case IN : strcpy(str, "IN"); break;
	  case INTEGER : strcpy(str, "INTEGER"); break;
	  case IS : strcpy(str, "IS"); break;
	  case NEW : strcpy(str, "NEW"); break;
	  case NOT : strcpy(str, "NOT"); break;
	  case OR : strcpy(str, "OR"); break;
	  case OUT : strcpy(str, "OUT"); break;
	  case PROCEDURE : strcpy(str, "PROCEDURE"); break;
	  case RECORD : strcpy(str, "RECORD"); break;
	  case THEN : strcpy(str, "THEN"); break;
	  case WHILE : strcpy(str, "WHILE"); break;
	  case ADD : strcpy(str, "ADD"); break;
	  case SUBTRACT : strcpy(str, "SUBTRACT"); break;
	  case MULTIPLY : strcpy(str, "MULTIPLY"); break;
	  case DIVIDE : strcpy(str, "DIVIDE"); break;
	  case ASSIGN : strcpy(str, "ASSIGN"); break;
	  case EQUAL : strcpy(str, "EQUAL"); break;
	  case LESS : strcpy(str, "LESS"); break;
	  case COLON : strcpy(str, "COLON"); break;
	  case SEMICOLON : strcpy(str, "SEMICOLON"); break;
	  case PERIOD : strcpy(str, "PERIOD"); break;
	  case COMMA : strcpy(str, "COMMA"); break;
	  case LPAREN : strcpy(str, "LPAREN"); break;
	  case RPAREN : strcpy(str, "RPAREN"); break;
	  case LBRACE : strcpy(str, "LBRACE"); break;
	  case RBRACE : strcpy(str, "RBRACE"); break;
	  case CONST : strcpy(str, "CONST"); break;
	  case ID : strcpy(str, "ID"); break;
	  case EOS : strcpy(str, "EOS"); break;
	}
}

void scanner(char* filename){
		// Initialize the scanner
  scanner_open(filename);
  //scanner_open("Correct/1.code");

  while (currentToken() != EOS && currentToken() != ERROR) {
	
	int current = currentToken();

	char str[20];
	tokenString(str, current);

	printf("%s", str);

	if (currentToken() == ID) {
		char value[20];
		getId(value);
		printf("[%s]", value);
	} else if (currentToken() == CONST) {
		int value = getConst();
		printf("[%d]", value);
	}

	printf("\n");

    // Advance to the next token
    nextToken();
  }
	// Scanning is done, release memory
  scanner_close();
}

void Test_scanner(char* filename){
		// Initialize the scanner
  //scanner_open(filename);

//x:=10;
//   scanner_open("Correct/0_test.code");
//   while (currentToken() != EOS && currentToken() != ERROR) {
// 	parseProcedure();
//     nextToken();
//   }
//   printf("\n-----------------------------------\n");
//   printf("procedure Id is %s\n", p->id);
//   printf("Dec Id is: %s\n", p->ds->d->di->id);
//   printf("Assign Id is: %s\n",p->ss->s->ass->id);
//   printf("expr1 is: %d\n",p->ss->s->ass->exp->tm->fac->cnt);
//   scanner_close();
// 		//   PROCEDURE
// 		// procedure Id is test1
// 		// Dec Id is: x
// 		// Assign Id is: x
// 		// expr1 is: 10

// //x:=0-10;
//   scanner_open("Correct/0_test copy 2.code");
//   while (currentToken() != EOS && currentToken() != ERROR) {
// 	parseProcedure();
//     nextToken();
//   }
//   printf("\n-----------------------------------\n");
//   printf("procedure Id is %s\n", p->id);
//   printf("Dec Id is: %s\n", p->ds->d->di->id);
//   printf("Assign Id is: %s\n",p->ss->s->ass->id);
//   printf("expr1 is: %d\n",p->ss->s->ass->exp->tm->fac->cnt);
//   printf("math1 is: %s\n",p->ss->s->ass->exp->math);
//   printf("expr2 is: %d\n",(p->ss->s->ass->exp->exp->tm->fac->cnt));
//   scanner_close();
// 		// PROCEDURE
// 		// procedure Id is test1
// 		// Dec Id is: x
// 		// Assign Id is: x
// 		// expr1 is: 0
// 		// math1 is: -
// 		// expr2 is: 10

// //x:=3-2+1;
//   scanner_open("Correct/0_test copy 3.code");
//   while (currentToken() != EOS && currentToken() != ERROR) {
// 	parseProcedure();
//     nextToken();
//   }
//   printf("\n-----------------------------------\n");
// printf("procedure Id is %s\n", p->id);
// printf("Dec Id is: %s\n", p->ds->d->di->id);
// printf("Assign Id is: %s\n",p->ss->s->ass->id);
// printf("expr1 is: %d\n",p->ss->s->ass->exp->tm->fac->cnt);
// printf("math1 is: %s\n",p->ss->s->ass->exp->math);
// printf("expr2 is: %d\n",(p->ss->s->ass->exp->exp->tm->fac->cnt));
// printf("math2 is: %s\n",(p->ss->s->ass->exp->exp->math));
// printf("expr3 is: %d\n",(p->ss->s->ass->exp->exp->exp->tm->fac->cnt));
//   scanner_close();
// 		// PROCEDURE
// 		// procedure Id is test1
// 		// Dec Id is: x
// 		// Assign Id is: x
// 		// expr1 is: 3
// 		// math1 is: -
// 		// expr2 is: 2
// 		// math2 is: +
// 		// expr3 is: 1

// //out(4);
//   scanner_open("Correct/0_test copy 4.code");
//   while (currentToken() != EOS && currentToken() != ERROR) {
// 	parseProcedure();
//     nextToken();
//   }
//   printf("\n-----------------------------------\n");
//   printf("procedure Id is %s\n", p->id);
//   printf("Dec Id is: %s\n", p->ds->d->di->id);
//   printf("out expr is: %d\n",p->ss->s->out->exp->tm->fac->cnt);
//   scanner_close();
// 		// PROCEDURE
// 		// procedure Id is test1
// 		// Dec Id is: x
// 		// out expr is: 4

// //x[2]:=3;
//   scanner_open("Correct/0_test copy 5.code");
//   while (currentToken() != EOS && currentToken() != ERROR) {
// 	parseProcedure();
//     nextToken();
//   }
//   printf("\n-----------------------------------\n");
// printf("procedure Id is %s\n", p->id);
// printf("Dec Id is: %s\n", p->ds->d->di->id);
// printf("Assign Id is: %s\n",p->ss->s->ass->id);
// printf("idx1 is: %d\n",p->ss->s->ass->idx->exp->tm->fac->cnt);
// printf("expr1 is: %d\n",p->ss->s->ass->exp->tm->fac->cnt);
//   scanner_close();
// 		// PROCEDURE
// 		// procedure Id is test1
// 		// Dec Id is: x
// 		// Assign Id is: x
// 		// idx1 is: 2
// 		// expr1 is: 3  

// //x:=new record[3];  
//   scanner_open("Correct/0_test copy 6.code");
//   while (currentToken() != EOS && currentToken() != ERROR) {
// 	parseProcedure();
//     nextToken();
//   }
//   printf("\n-----------------------------------\n");
//   printf("procedure Id is %s\n", p->id);
//   printf("Dec Id is: %s\n", p->ds->d->di->id);
//   printf("Assign Id is: %s\n",p->ss->s->ass->id);
//   printf("expr1 is: %d\n",p->ss->s->ass->exp->tm->fac->cnt);
//   scanner_close();
// 		// PROCEDURE
// 		// procedure Id is test1
// 		// Dec Id is: x
// 		// Assign Id is: x
// 		// expr1 is: 3

// //x[2]:=x[1];
//   scanner_open("Correct/0_test copy 7.code");
//   while (currentToken() != EOS && currentToken() != ERROR) {
// 	parseProcedure();
//     nextToken();
//   }
//   printf("\n-----------------------------------\n");
// printf("procedure Id is %s\n", p->id);
// printf("Dec Id is: %s\n", p->ds->d->di->id);
// printf("Assign Id is: %s\n",p->ss->s->ass->id);
// printf("idx1 is: %d\n",p->ss->s->ass->idx->exp->tm->fac->cnt);
// printf("assign expr is: %s\n",p->ss->s->ass->exp->tm->fac->id);
// printf("assign idx is: %d\n",p->ss->s->ass->exp->tm->fac->exp->tm->fac->cnt);
//   scanner_close();
// 		// PROCEDURE
// 		// procedure Id is test1
// 		// Dec Id is: x
// 		// Assign Id is: x
// 		// idx1 is: 2
// 		// assign expr is: x
// 		// assign idx is: 1

// //x := in();
//   scanner_open("Correct/0_test copy 8.code");
//   while (currentToken() != EOS && currentToken() != ERROR) {
// 	parseProcedure();
//     nextToken();
//   }
//   printf("\n-----------------------------------\n");
//   printf("procedure Id is %s\n", p->id);
//   printf("Dec Id is: %s\n", p->ds->d->di->id);
//   printf("Assign Id is: %s\n",p->ss->s->ass->id);
//   printf("expr1 is: %s\n",p->ss->s->ass->exp->tm->fac->id);
//   scanner_close();
// 		//   PROCEDURE
// 		// procedure Id is test1
// 		// Dec Id is: x
// 		// Assign Id is: x
// 		// expr1 is: in
// 	// Scanning is done, release memory

// //x := (3+2);
//   scanner_open("Correct/0_test copy 9.code");
//   while (currentToken() != EOS && currentToken() != ERROR) {
// 	parseProcedure();
//     nextToken();
//   }
//   printf("\n-----------------------------------\n");
//   printf("procedure Id is %s\n", p->id);
//   printf("Dec Id is: %s\n", p->ds->d->di->id);
//   printf("Assign Id is: %s\n",p->ss->s->ass->id);
//   printf("expr1 is: %d\n",p->ss->s->ass->exp->tm->fac->exp->tm->fac->cnt);
//   printf("math1 is: %s\n",p->ss->s->ass->exp->tm->fac->exp->math);
//   printf("expr1 is: %d\n",p->ss->s->ass->exp->tm->fac->exp->exp->tm->fac->cnt);
//   scanner_close();
// 		// PROCEDURE
// 		// procedure Id is test1
// 		// Dec Id is: x
// 		// Assign Id is: x
// 		// expr1 is: 3
// 		// math1 is: +
// 		// expr1 is: 2

// //x:=y; (x)
//   scanner_open("Correct/0_test copy 10.code");
//   while (currentToken() != EOS && currentToken() != ERROR) {
// 	parseProcedure();
//     nextToken();
//   }
//   printf("\n-----------------------------------\n");
//   printf("procedure Id is %s\n", p->id);
//   printf("Dec Id is: %s\n", p->ds->d->di->id);
//   printf("Assign Id is: %s\n",p->ss->s->ass->id);
//   printf("expr1 is: %s\n",p->ss->s->ass->exp->tm->fac->id);
//   scanner_close();
// 		// PROCEDURE
// 		// procedure Id is test1
// 		// Dec Id is: x
// 		// Assign Id is: x
// 		// expr1 is: x

// //x:=record y;
//   scanner_open("Correct/0_test copy 11.code");
//   while (currentToken() != EOS && currentToken() != ERROR) {
// 	parseProcedure();
//     nextToken();
//   } 
//   printf("\n-----------------------------------\n");
//   printf("procedure Id is %s\n", p->id);
//   printf("Dec Id is: %s\n", p->ds->d->di->id);
//   printf("Assign Id is: %s\n",p->ss->s->ass->id);
//   printf("Assign Id is: %s\n",p->ss->s->ass->id2);
//   scanner_close();
// 		// procedure Id is test1
// 		// Dec Id is: x
// 		// Assign Id is: x
// 		// Assign Id is: y

// // x :=3*2;
//   scanner_open("Correct/0_test copy 12.code");
//   while (currentToken() != EOS && currentToken() != ERROR) {
// 	parseProcedure();
//     nextToken();
//   }
//   printf("\n-----------------------------------\n");
//   printf("procedure Id is %s\n", p->id);
//   printf("Dec Id is: %s\n", p->ds->d->di->id);
//   printf("Assign Id is: %s\n",p->ss->s->ass->id);
//   printf("expr1 is: %d\n",p->ss->s->ass->exp->tm->fac->cnt);
//   printf("math1 is: %s\n",p->ss->s->ass->exp->tm->math);
//   printf("expr1 is: %d\n",p->ss->s->ass->exp->tm->tm->fac->cnt);
//   scanner_close();
// 		//   procedure Id is test1
// 		// Dec Id is: x
// 		// Assign Id is: x
// 		// expr1 is: 3
// 		// math1 is: *
// 		// expr1 is: 2

// //x :=3/2;
//   scanner_open("Correct/0_test copy 13.code");
//   while (currentToken() != EOS && currentToken() != ERROR) {
// 	parseProcedure();
//     nextToken();
//   }
//   printf("\n-----------------------------------\n");
//   printf("procedure Id is %s\n", p->id);
//   printf("Dec Id is: %s\n", p->ds->d->di->id);
//   printf("Assign Id is: %s\n",p->ss->s->ass->id);
//   printf("expr1 is: %d\n",p->ss->s->ass->exp->tm->fac->cnt);
//   printf("math1 is: %s\n",p->ss->s->ass->exp->tm->math);
//   printf("expr1 is: %d\n",p->ss->s->ass->exp->tm->tm->fac->cnt);
//   scanner_close();
// 		//   procedure Id is test1
// 		// Dec Id is: x
// 		// Assign Id is: x
// 		// expr1 is: 3
// 		// math1 is: /
// 		// expr1 is: 2

// //x :=3*2/1;
//   scanner_open("Correct/0_test copy 14.code");
//   while (currentToken() != EOS && currentToken() != ERROR) {
// 	parseProcedure();
//     nextToken();
//   }
//   printf("\n-----------------------------------\n");
//   printf("procedure Id is %s\n", p->id);
//   printf("Dec Id is: %s\n", p->ds->d->di->id);
//   printf("Assign Id is: %s\n",p->ss->s->ass->id);
//   printf("expr1 is: %d\n",p->ss->s->ass->exp->tm->fac->cnt);
//   printf("math1 is: %s\n",p->ss->s->ass->exp->tm->math);
//   printf("expr2 is: %d\n",p->ss->s->ass->exp->tm->tm->fac->cnt);
//   printf("math2 is: %s\n",p->ss->s->ass->exp->tm->tm->math);
//   printf("exp3 is: %d\n",p->ss->s->ass->exp->tm->tm->tm->fac->cnt);
//   scanner_close();
// 		//   procedure Id is test1
// 		// Dec Id is: x
// 		// Assign Id is: x
// 		// expr1 is: 3
// 		// math1 is: *
// 		// expr2 is: 2
// 		// math2 is: /
// 		// exp3 is: 1

// //x :=3*2+1;
//   scanner_open("Correct/0_test copy 15.code");
//   while (currentToken() != EOS && currentToken() != ERROR) {
// 	parseProcedure();
//     nextToken();
//   }
//   printf("\n-----------------------------------\n");
//   printf("procedure Id is %s\n", p->id);
//   printf("Dec Id is: %s\n", p->ds->d->di->id);
//   printf("Assign Id is: %s\n",p->ss->s->ass->id);
//   printf("expr1 is: %d\n",p->ss->s->ass->exp->tm->fac->cnt);
//   printf("math1 is: %s\n",p->ss->s->ass->exp->tm->math);
//   printf("expr1 is: %d\n",p->ss->s->ass->exp->tm->tm->fac->cnt);
//   printf("expr1 is: %s\n",p->ss->s->ass->exp->math);
//   printf("expr1 is: %d\n",p->ss->s->ass->exp->exp->tm->fac->cnt);
//   scanner_close();
// 		//   PROCEDURE
// 		// procedure Id is test1
// 		// Dec Id is: x
// 		// Assign Id is: x
// 		// expr1 is: 3
// 		// math1 is: *
// 		// expr1 is: 2
// 		// expr1 is: +
// 		// expr1 is: 1

// //integer x and record y
// //x :=3*2+1;
// //y:=0-10; 
//   scanner_open("Correct/0_test copy 16.code");
//   while (currentToken() != EOS && currentToken() != ERROR) {
// 	parseProcedure();
//     nextToken();
//   }
//   printf("\n-----------------------------------\n");
//   printf("procedure Id is %s\n", p->id);
//   printf("Dec int Id is: %s\n", p->ds->d->di->id);
//   printf("Dec rec Id is: %s\n", p->ds->ds->d->dr->id);

//   printf("Assign Id is: %s\n",p->ss->s->ass->id);
//   printf("expr1 is: %d\n",p->ss->s->ass->exp->tm->fac->cnt);
//   printf("math1 is: %s\n",p->ss->s->ass->exp->tm->math);
//   printf("expr1 is: %d\n",p->ss->s->ass->exp->tm->tm->fac->cnt);
//   printf("math1 is: %s\n",p->ss->s->ass->exp->math);
//   printf("expr1 is: %d\n",p->ss->s->ass->exp->exp->tm->fac->cnt);

//   printf("Assign Id2 is: %s\n",p->ss->ss->s->ass->id);
//   printf("expr is2: %d\n",p->ss->ss->s->ass->exp->tm->fac->cnt);
//   printf("math is2: %s\n",p->ss->ss->s->ass->exp->math);
//   printf("expr is2: %d\n",p->ss->ss->s->ass->exp->exp->tm->fac->cnt);
//   scanner_close();
// 		//   Dec int Id is: x
// 		// Dec rec Id is: y
// 		// Assign Id is: x
// 		// expr1 is: 3
// 		// math1 is: *
// 		// expr1 is: 2
// 		// math1 is: +
// 		// expr1 is: 1
// 		// Assign Id2 is: y
// 		// expr is2: 0
// 		// math is2: -
// 		// expr is2: 10

// //int x rec y (x)
// //	x:=record z; 
// //	y:=0-10; 
//   scanner_open("Correct/0_test copy 17.code");
//   while (currentToken() != EOS && currentToken() != ERROR) {
// 	parseProcedure();
//     nextToken();
//   }
//   printf("\n-----------------------------------\n");
//   printf("procedure Id is %s\n", p->id);
//   printf("Dec int Id is: %s\n", p->ds->d->di->id);
//   printf("Dec rec Id is: %s\n", p->ds->ds->d->dr->id);

//   printf("Assign Id is: %s\n",p->ss->s->ass->id);
//   printf("Assign Id is: %s\n",p->ss->s->ass->id2);

//   printf("Assign Id2 is: %s\n",p->ss->ss->s->ass->id);
//   printf("expr is2: %d\n",p->ss->ss->s->ass->exp->tm->fac->cnt);
//   printf("math is2: %s\n",p->ss->ss->s->ass->exp->math);
//   printf("expr is2: %d\n",p->ss->ss->s->ass->exp->exp->tm->fac->cnt);
//   scanner_close();

// // int x
// // 	if then end (x)
//   scanner_open("Correct/0_test copy 18.code");
//   while (currentToken() != EOS && currentToken() != ERROR) {
// 	parseProcedure();
//     nextToken();
//   }
//   printf("\n-----------------------------------\n");
//   printf("procedure Id is %s\n", p->id);
//   printf("Dec int Id is: %s\n", p->ds->d->di->id);

//   printf("Cond1 %d\n", p->ss->s->i->c->cmp->exp->tm->fac->cnt);
//   printf("Cond sign %s\n", p->ss->s->i->c->cmp->sign);
//   printf("Cond2 %d\n", p->ss->s->i->c->cmp->exp2->tm->fac->cnt);

//   printf("then stmt id %s\n", p->ss->s->i->ss->s->ass->id);
//   printf("then stmt exp %d\n", p->ss->s->i->ss->s->ass->exp->tm->fac->cnt);
//   scanner_close();

// // if else then
//    scanner_open("Correct/0_test copy 19.code");
//   while (currentToken() != EOS && currentToken() != ERROR) {
      
// 	  parseProcedure();
//     nextToken();
//   }
//   printf("\n-----------------------------------\n");
//   printf("procedure Id is %s\n", p->id);
//   printf("Dec int Id is: %s\n", p->ds->d->di->id);

//   printf("Cond1 %d\n", p->ss->s->i->c->cmp->exp->tm->fac->cnt);
//   printf("Cond sign %s\n", p->ss->s->i->c->cmp->sign);
//   printf("Cond2 %d\n", p->ss->s->i->c->cmp->exp2->tm->fac->cnt);

//   printf("then stmt id %s\n", p->ss->s->i->ss->s->ass->id);
//   printf("then stmt exp %d\n", p->ss->s->i->ss->s->ass->exp->tm->fac->cnt);
//     printf("then stmt id %s\n", p->ss->s->i->ss->ss->s->ass->id);
//   printf("then stmt exp %d\n", p->ss->s->i->ss->ss->s->ass->exp->tm->fac->cnt);

//   printf("else stmt id %s\n", p->ss->s->i->ss2->s->ass->id);
//   printf("else stmt exp %d\n", p->ss->s->i->ss2->s->ass->exp->tm->fac->cnt);
//     printf("else stmt id %s\n", p->ss->s->i->ss2->ss->s->ass->id);
//   printf("else stmt exp %d\n", p->ss->s->i->ss2->ss->s->ass->exp->tm->fac->cnt);
//   scanner_close();

//  //if < else
//   scanner_open("Correct/0_test copy 20.code");
//   while (currentToken() != EOS && currentToken() != ERROR) {
// 	parseProcedure();
//     nextToken();
//   }
//   printf("\n-----------------------------------\n");
//   printf("procedure Id is %s\n", p->id);
//   printf("Dec int Id is: %s\n", p->ds->d->di->id);

//   printf("Cond1 %d\n", p->ss->s->i->c->cmp->exp->tm->fac->cnt);
//   printf("Cond sign %s\n", p->ss->s->i->c->cmp->sign);
//   printf("Cond2 %d\n", p->ss->s->i->c->cmp->exp2->tm->fac->cnt);

//   printf("then stmt id %s\n", p->ss->s->i->ss->s->ass->id);
//   printf("then stmt exp %d\n", p->ss->s->i->ss->s->ass->exp->tm->fac->cnt);
//   scanner_close();

// //if and else 
//    scanner_open("Correct/0_test copy 21.code");
//   while (currentToken() != EOS && currentToken() != ERROR) {
// 	parseProcedure();
//     nextToken();
//   }
//   printf("\n-----------------------------------\n");
//   printf("procedure Id is %s\n", p->id);
//   printf("Dec int Id is: %s\n", p->ds->d->di->id);

//   printf("Cond1 %d\n", p->ss->s->i->c->cmp->exp->tm->fac->cnt);
//   printf("Cond sign %s\n", p->ss->s->i->c->cmp->sign);
//   printf("Cond1 %d\n", p->ss->s->i->c->cmp->exp2->tm->fac->cnt);

// 	printf("Cond1 btw sign %s\n", p->ss->s->i->c->sign);

//    printf("Cond2 %d\n", p->ss->s->i->c->c->cmp->exp->tm->fac->cnt);
//   printf("Cond sign %s\n", p->ss->s->i->c->c->cmp->sign);
//   printf("Cond2 %d\n", p->ss->s->i->c->c->cmp->exp2->tm->fac->cnt);

//   printf("then stmt id %s\n", p->ss->s->i->ss->s->ass->id);
//   printf("then stmt exp %d\n", p->ss->s->i->ss->s->ass->exp->tm->fac->cnt);
//   scanner_close();

// // if not 
//    scanner_open("Correct/0_test copy 22.code");
//   while (currentToken() != EOS && currentToken() != ERROR) {
// 	parseProcedure();
//     nextToken();
//   }
//     printf("\n-----------------------------------\n");
//   printf("procedure Id is %s\n", p->id);
//   printf("Dec int Id is: %s\n", p->ds->d->di->id);

//   printf("Cond1 %d\n", p->ss->s->i->c->c->cmp->exp->tm->fac->cnt);
//   printf("Cond sign %s\n", p->ss->s->i->c->c->cmp->sign);
//   printf("Cond1 %d\n", p->ss->s->i->c->c->cmp->exp2->tm->fac->cnt);

//   printf("then stmt id %s\n", p->ss->s->i->ss->s->ass->id);
//   printf("then stmt exp %d\n", p->ss->s->i->ss->s->ass->exp->tm->fac->cnt);

//   printf("then stmt id %s\n", p->ss->s->i->ss->ss->s->ass->id);
//   printf("then stmt exp %d\n", p->ss->s->i->ss->ss->s->ass->exp->tm->fac->cnt);

//   printf("else stmt id %s\n", p->ss->s->i->ss2->s->ass->id);
//   printf("else stmt exp %d\n", p->ss->s->i->ss2->s->ass->exp->tm->fac->cnt);
//     printf("else stmt id %s\n", p->ss->s->i->ss2->ss->s->ass->id);
//   printf("else stmt exp %d\n", p->ss->s->i->ss2->ss->s->ass->exp->tm->fac->cnt);

// 	printf("outside con %s\n", p->ss->ss->s->ass->id);
// 	printf("outside con %d\n", p->ss->ss->s->ass->exp->tm->fac->cnt);
// 	scanner_close();

// //while
//    scanner_open("Correct/0_test copy 23.code");
//   while (currentToken() != EOS && currentToken() != ERROR) {
// 	   parseProcedure();
//     nextToken();
//   }
//       printf("\n-----------------------------------\n");
//   printf("procedure Id is %s\n", p->id);
//   printf("Dec int Id is: %s\n", p->ds->d->di->id);

// 	printf("while con %d\n", p->ss->s->lp->c->cmp->exp->tm->fac->cnt);
// 	printf("while con %s\n", p->ss->s->lp->c->cmp->sign);
// 	printf("while con %s\n", p->ss->s->lp->c->cmp->exp2->tm->fac->id);

// 	printf("inside id %s\n", p->ss->s->lp->ss->s->ass->id);
// 	printf("inside exp %d\n", p->ss->s->lp->ss->s->ass->exp->tm->fac->cnt);

//  	scanner_close();

// // x and if
//    scanner_open("Correct/0_test copy 24.code");
//   while (currentToken() != EOS && currentToken() != ERROR) {
// 	parseProcedure();
//     nextToken();
//   }
//   printf("\n-----------------------------------\n");
//   printf("procedure Id is %s\n", p->id);
//   printf("Dec int Id is: %s\n", p->ds->d->di->id);

//   printf("first %s\n",p->ss->s->ass->id);
//   printf("first %d\n",p->ss->s->ass->exp->tm->fac->cnt);

//   printf("Cond1 %d\n", p->ss->ss->s->i->c->cmp->exp->tm->fac->cnt);
//   printf("Cond1 sign %s\n", p->ss->ss->s->i->c->cmp->sign);
//   printf("Cond1 %d\n", p->ss->ss->s->i->c->cmp->exp2->tm->fac->cnt);


//   printf("then stmt id %s\n", p->ss->ss->s->i->ss->s->ass->id);
//   printf("then stmt exp %d\n", p->ss->ss->s->i->ss->s->ass->exp->tm->fac->cnt);

//   printf("then stmt id %s\n", p->ss->ss->s->i->ss->ss->s->ass->id);
//   printf("then stmt exp %d\n", p->ss->ss->s->i->ss->ss->s->ass->exp->tm->fac->cnt);

//   printf("else stmt id %s\n", p->ss->ss->s->i->ss2->s->ass->id);
//   printf("else stmt exp %d\n", p->ss->ss->s->i->ss2->s->ass->exp->tm->fac->cnt);

//     printf("else stmt id %s\n", p->ss->ss->s->i->ss2->ss->s->ass->id);
//   printf("else stmt exp %d\n", p->ss->ss->s->i->ss2->ss->s->ass->exp->tm->fac->cnt);

// //if nested while
//    scanner_open("Correct/0_test copy 25.code");
//   while (currentToken() != EOS && currentToken() != ERROR) {
// 	parseProcedure();
//     nextToken();
//   }
//   printf("\n-----------------------------------\n");
//   printf("procedure Id is %s\n", p->id);
//   printf("Dec int Id is: %s\n", p->ds->d->di->id);

//   printf("if %s\n", p->ss->s->i->c->cmp->exp->tm->fac->id);
//   printf("if %s\n", p->ss->s->i->c->cmp->sign);
//   printf("if %s\n", p->ss->s->i->c->cmp->exp2->tm->fac->id);

//   printf("while %d\n",p->ss->s->i->ss->s->lp->c->cmp->exp->tm->fac->cnt);
//   printf("while %s\n",p->ss->s->i->ss->s->lp->c->cmp->sign);
//   printf("while %s\n",p->ss->s->i->ss->s->lp->c->cmp->exp2->tm->fac->id);
//   printf("while %s\n",p->ss->s->i->ss->s->lp->ss->s->ass->id);
//   printf("while %d\n",p->ss->s->i->ss->s->lp->ss->s->ass->exp->tm->fac->cnt);
//  scanner_close();

scanner_open("Correct/0_test copy 26.code");
  while (currentToken() != EOS && currentToken() != ERROR) {
	parseProcedure();
    nextToken();
  }
//scanner_close();

  
// 	scanner_close();
}

// If the current token is something other than expected,
// prints a meaningful error message and halts the program
static void expectedToken(int expected) {
	int actual = currentToken();
	
    if (actual != expected) {
		char actualStr[20];
		char expectedStr[20];
		
		tokenString(actualStr, actual);
		tokenString(expectedStr, expected);
		
        printf("Error: expected %s but recieved %s\n", expectedStr, actualStr);
        exit(0);
    }
}

static void exprChecker(){
	int current=currentToken();

	if(current != ID && current != CONST && current != LPAREN && current != IN){
		char actualStr[20];
		tokenString(actualStr, current);
		printf("Error: Expected ID, CONST, LPAREN, IN but %s\n", actualStr);
		exit(0);
	}
}

static void declSeqChecker(){
	int current=currentToken();

	//BEGIN need check
	if(currentToken() != INTEGER && currentToken() != RECORD && currentToken() != BEGIN){
		char actualStr[20];
		tokenString(actualStr, current);

		printf("Error: expected INTEGER or RECORD or BEGIN but recieved %s\n", actualStr);
		exit(0);
	}
}


/*
*
* Parse functions go here
*
*/



void parseProcedure(){
	//procedure check
	expectedToken(PROCEDURE);

	p = (struct nodeProcedure*) calloc(1, sizeof(struct nodeProcedure));
	p->ds=(struct nodeDeclSeq*) calloc(1, sizeof(struct nodeDeclSeq));
	p->ss=(struct nodeStmtSeq*) calloc(1, sizeof(struct nodeStmtSeq));

	//ID
	nextToken();
	expectedToken(ID);

	char value[10];
	getId(value);
	p->id=(char*) calloc(10, sizeof(char));
	strcpy(p->id, value);

	//IS
	nextToken();
	expectedToken(IS);

	//ID
	nextToken();
	parseDeclSeq(p->ds);

	nextToken();
	//Later check 

	parseStmtSeq(p->ss);

	//end checker
}

//(x)
void parseDeclSeq(struct nodeDeclSeq *ds2){
	
	declSeqChecker();
	ds2->d=(struct nodeDecl*) calloc(1, sizeof(struct nodeDecl));

	parseDecl(ds2->d);

	nextToken();

	if(currentToken() == INTEGER || currentToken() == RECORD){
		ds2->ds=(struct nodeDeclSeq*) calloc(1, sizeof(struct nodeDeclSeq));
		parseDeclSeq(ds2->ds);
	}
	declSeqChecker();

}

void parseStmtSeq(struct nodeStmtSeq *ss2){
	ss2->s=(struct nodeStmt*) calloc(1, sizeof(struct nodeStmt));

	// (working)
	parseStmt(ss2->s);


	//END or Not
	//printf("Stmt current is %d\n",currentToken());
    nextToken();
	
    ////printf("\ncurrent is %d\n",currentToken());
	
	if(currentToken() == ID || currentToken() == IF || currentToken() == WHILE || currentToken() == OUT){
    //printf("Stmt2 current is %d\n",currentToken());
		ss2->ss=(struct nodeStmtSeq*) calloc(1, sizeof(struct nodeStmtSeq));
		parseStmtSeq(ss2->ss);
	}
	
}

// (working)
void parseStmt(struct nodeStmt *s2){
	

	int current=currentToken();
	
	if(current==ID){
		s2->ass=(struct nodeAssign*) calloc(1, sizeof(struct nodeAssign));
		//(x)
		parseAssign(s2->ass);
	}else if(current==IF){
		s2->i=(struct nodeIf*) calloc(1, sizeof(struct nodeIf));
		parseIf(s2->i);
	}else if(current==WHILE){
		s2->lp=(struct nodeLoop*) calloc(1, sizeof(struct nodeLoop));
		parseLoop(s2->lp);
	}else if(current==OUT){
		s2->out=(struct nodeOut*) calloc(1, sizeof(struct nodeOut));
		parseOut(s2->out);
	}else{
		char actualStr[20];
		tokenString(actualStr, current);
		printf("Error: Expected ID, IF, WHILE, OUT but %s\n", actualStr);
		exit(0);
	}
  
	
}

//(x)
void parseAssign(struct nodeAssign *ass2){
	char value[10];
	getId(value);
	ass2->id=(char*) calloc(10, sizeof(char));
	strcpy(ass2->id, value);

	int current = nextToken();
	if(current == LBRACE){
		//id <index> := <expr> ;
		ass2->idx=(struct nodeIndex*) calloc(1, sizeof(struct nodeIndex));
		ass2->exp=(struct nodeExpr*) calloc(1, sizeof(struct nodeExpr));
		parseIndex(ass2->idx);
		
		//assign
		nextToken();
		expectedToken(ASSIGN);

		//expr
		nextToken();
		parseExpr(ass2->exp);

		expectedToken(SEMICOLON);

	}else if(current == ASSIGN){
		int current_2 = nextToken();

		if(current_2==CONST || current_2==ID || current_2==IN || current_2==LPAREN){
			//id := <expr> ;
			ass2->idx=(struct nodeIndex*) calloc(1, sizeof(struct nodeIndex));
			ass2->exp=(struct nodeExpr*) calloc(1, sizeof(struct nodeExpr));
			parseIndex(ass2->idx);
			parseExpr(ass2->exp);
			
			expectedToken(SEMICOLON);
		}else if(current_2==NEW){
			//id := new record [<expr>];
			ass2->exp=(struct nodeExpr*) calloc(1, sizeof(struct nodeExpr));
			//record
			nextToken();
			expectedToken(RECORD);

			//LBRACE
			nextToken();
			expectedToken(LBRACE);

			//expr
			nextToken();
			parseExpr(ass2->exp);

			//RBRACE check
			expectedToken(RBRACE);

			//Semi-colon
			nextToken();
			expectedToken(SEMICOLON);

		}else if(current_2==RECORD){
			//id := record id; 
			//id
			nextToken();
			expectedToken(ID);

			char value[10];
			getId(value);
			
			ass2->id2=(char*) calloc(10, sizeof(char));
			strcpy(ass2->id2, value);
			
			//Semi-colon
			nextToken();
			expectedToken(SEMICOLON);

		}else{
			char actualStr[20];
			tokenString(actualStr, current_2);
			printf("Error: Expected EXPR token, NEW, or RECORD but %s\n", actualStr);
			exit(0);
		}
	}else{
		char actualStr[20];
		tokenString(actualStr, current);
		printf("Error: Expected LBRACE or ASSIGN but %s\n", actualStr);
		exit(0);
	}
	
}

void parseIndex(struct nodeIndex *idx2){

	if(currentToken() == LBRACE){
		//expr
		nextToken();
		int current=currentToken();

		idx2->exp=(struct nodeExpr*) calloc(1, sizeof(struct nodeExpr));
		parseExpr(idx2->exp);

		//RBRACE check
		expectedToken(RBRACE);
	}
	//epsilon
}

void parseExpr(struct nodeExpr *expr2){
	exprChecker();
	expr2->tm = (struct nodeTerm*) calloc(1, sizeof(struct nodeTerm));
	parseTerm(expr2->tm);
	//+ or -
	int current = currentToken();
	//printf("current is %d\n", current);
	if(current == ADD || current == SUBTRACT){
		expr2->exp=(struct nodeExpr*) calloc(1, sizeof(struct nodeExpr));
		expr2->math=(char*) calloc(1, sizeof(char));
		if(current == ADD){
			strcpy(expr2->math, "+");
		}else if(current == SUBTRACT){
			strcpy(expr2->math, "-");
		}
		//expr
		nextToken();
		parseExpr(expr2->exp);
	}
	////printf("\ncurrent is %d", currentToken());
	
}

void parseTerm(struct nodeTerm *tm2){
	tm2->fac=(struct nodeFactor*) calloc(1, sizeof(struct nodeFactor));
	parseFactor(tm2->fac);

	int current = currentToken();

	//printf("Term current is %d\n", currentToken()); //THEN
	if(current == MULTIPLY || current == DIVIDE){
		tm2->tm=(struct nodeTerm*) calloc(1, sizeof(struct nodeTerm));
		tm2->math=(char*) calloc(1, sizeof(char));
		if(current == MULTIPLY){
			strcpy(tm2->math, "*");
		}else if(current == DIVIDE){
			strcpy(tm2->math, "/");
		}
		//term
		nextToken();
		parseTerm(tm2->tm);
	}
	////printf("\nTerm current is %d\n", currentToken()); 
}

void parseFactor(struct nodeFactor *fac2){
	int current = currentToken();
	if(current==ID){

		char value[10];
		getId(value);
		fac2->id=(char*) calloc(10, sizeof(char));
		strcpy(fac2->id, value);

		int current_2=nextToken();
		if(current_2==LBRACE){
			//expr
			nextToken();

			fac2->exp=(struct nodeExpr*) calloc(1, sizeof(struct nodeExpr));
			parseExpr(fac2->exp);

			//RBRACE Checker
			expectedToken(RBRACE);
			
			nextToken();
		}
		
	}else if(current==CONST){
		int value = getConst();
		fac2->cnt = value;
		
		nextToken();
	}else if(current==LPAREN){
		//expr
		nextToken();
		exprChecker();

		fac2->exp=(struct nodeExpr*) calloc(1, sizeof(struct nodeExpr));
		parseExpr(fac2->exp);

		//RPAREN check
		expectedToken(RPAREN);

		nextToken();
	}else if(current==IN){

		//LPAREN
		nextToken();
		expectedToken(LPAREN);
		
		//RPAREN
		nextToken();
		expectedToken(RPAREN);

		nextToken();
		
	}
	
	
}

// (x)
void parseIf(struct nodeIf *i2){

	//condition
	nextToken();
	i2->c=(struct nodeCond*) calloc(1, sizeof(struct nodeCond));
	parseCond(i2->c);

	expectedToken(THEN);
	nextToken();
	
	i2->ss=(struct nodeStmtSeq*) calloc(1, sizeof(struct nodeStmtSeq));
	parseStmtSeq(i2->ss);
	int current = currentToken();
	
	if(current == ELSE){
		i2->ss2=(struct nodeStmtSeq*) calloc(1, sizeof(struct nodeStmtSeq));
		nextToken();
		parseStmtSeq(i2->ss2);
	}

	expectedToken(END);
}

//(x)
void parseCond(struct nodeCond *c2){
	int current = currentToken();
	if(current==CONST || current==ID || current==IN || current==LPAREN){
		c2->cmp=(struct nodeCmpr*) calloc(1, sizeof(struct nodeCmpr));
		parseCmpr(c2->cmp); //then or-then

		int current_2= currentToken();
		if(current_2==OR || current_2==AND){
			c2->c=(struct nodeCond*) calloc(1, sizeof(struct nodeCond));
			c2->sign=(char*) calloc(1, sizeof(char));

			if(current_2==OR){
				strcpy(c2->sign, "OR");
			}else if(current_2==AND){
				strcpy(c2->sign, "AND");
			}
			
			nextToken();
			parseCond(c2->c);
		}

	}else if(current ==NOT){
		nextToken();
		c2->c=(struct nodeCond*) calloc(1, sizeof(struct nodeCond));
		parseCond(c2->c);
	}else{
		char actualStr[20];
		tokenString(actualStr, current);
		printf("Error: Expected EXPR token or NOT but %s\n", actualStr);
		exit(0);
	} 
}

void parseLoop(struct nodeLoop *lp2){
	lp2->c = (struct nodeCond*) calloc(1, sizeof(struct nodeCond));
	lp2->ss= (struct nodeStmtSeq*) calloc(1, sizeof(struct nodeStmtSeq));
	//cond
	nextToken();
	parseCond(lp2->c);

	//do check

	//stmt-seq
	nextToken();
	parseStmtSeq(lp2->ss);

	//end check
}

//(x)
void parseCmpr(struct nodeCmpr  *cmp2){
	cmp2->exp=(struct nodeExpr*) calloc(1, sizeof(struct nodeExpr));
	cmp2->exp2=(struct nodeExpr*) calloc(1, sizeof(struct nodeExpr));
	cmp2->sign =(char*) calloc(1, sizeof(char));
	
	parseExpr(cmp2->exp);
	//sign = or <
	int current=currentToken();
	if(current == EQUAL){
		strcpy(cmp2->sign, "=");
	}else if (current == LESS){
		strcpy(cmp2->sign, "<");
	}else{
		char actualStr[20];
		tokenString(actualStr, current);
		printf("Error: Expected EQUAL or < but %s\n", actualStr);
		exit(0);
	}

	//exprs
	nextToken();
	parseExpr(cmp2->exp2);
	////printf("\nloop current is %d\n", currentToken());
}

void parseOut(struct nodeOut *out){
	//LPAREN
	nextToken();
	//exp
	nextToken();
	out->exp=(struct nodeExpr*) calloc(1, sizeof(struct nodeExpr));
	parseExpr(out->exp);
	//semi-colon
	nextToken();
}


void parseDecl(struct nodeDecl *d2){
	if(currentToken() == INTEGER){
		d2->di=(struct nodeDeclInteger*) calloc(1, sizeof(struct nodeDeclInteger));
		parseDeclInteger(d2->di);
	}
	if(currentToken() == RECORD){
		d2->dr=(struct nodeDeclRecord*) calloc(1, sizeof(struct nodeDeclRecord));
		parseDeclRecord(d2->dr);
	}


}

void parseDeclInteger(struct nodeDeclInteger *di2){
	//ID
	nextToken();
	expectedToken(ID);

	char value[10];
	getId(value);
	di2->id=(char*) calloc(10, sizeof(char));
	strcpy(di2->id, value);
	
	//semi-colon
	nextToken();
	expectedToken(SEMICOLON);
}

void parseDeclRecord(struct nodeDeclRecord *dr2){
	nextToken();
	expectedToken(ID);
	
	char value[10];
	getId(value);
	dr2->id=(char*) calloc(10, sizeof(char));
	strcpy(dr2->id, value);

	//semi-colon
	nextToken();
	expectedToken(SEMICOLON);
}
