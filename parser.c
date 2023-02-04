#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "scanner.h"
#include "core.h"
#include "tree.h"
#include "parser.h"

void parser();
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

// If the current token is something other than expected,
// prints a meaningful error message and halts the program
static void expectedToken(int expected) {
	int actual = currentToken();
	
    if (actual != expected) {
		char actualStr[20];
		char expectedStr[20];
		
		tokenString(actualStr, actual);
		tokenString(expectedStr, expected);
		
        printf("Error: expected %s but recieved %s", expectedStr, actualStr);
        exit(0);
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
  scanner_open(filename);
  //scanner_open("Correct/1.code");

  while (currentToken() != EOS && currentToken() != ERROR) {
	
	int current = currentToken();

	char str[20];
	tokenString(str, current);

	printf("%s", str);

	parser();
	printf("\n");

    // Advance to the next token
    nextToken();
  }
//1.code  
//   printf("procedure Id is %s\n", p->id);
//   printf("Dec Id is: %s\n", p->ds->d->di->id);
//   printf("Assign Id is: %s\n",p->ss->s->ass->id);
//   printf("expr1 is: %d\n",p->ss->s->ass->exp->tm->fac->cnt);

//2.code  
  printf("procedure Id is %s\n", p->id);
  printf("Dec Id is: %s\n", p->ds->d->di->id);
  printf("Assign Id is: %s\n",p->ss->s->ass->id);
  printf("expr1 is: %d\n",p->ss->s->ass->exp->tm->fac->cnt);
  printf("expr2 is: %d\n",(p->ss->s->ass->exp->exp->tm->fac->cnt));
  printf("expr2 is: %d\n",(p->ss->s->ass->exp->exp->exp->tm->fac->cnt));

//simple out(4) test
//   printf("procedure Id is %s\n", p->id);
//   printf("Dec Id is: %s\n", p->ds->d->di->id);
//   printf("out expr is: %d\n",p->ss->s->out->exp->tm->fac->cnt);
  
	// Scanning is done, release memory
  scanner_close();
}


/*
*
* Parse functions go here
*
*/


void parser(){
	if(currentToken() == PROCEDURE){
		parseProcedure();
	}else if(currentToken() == expected){
		
	}else{
		//error
	}
}

//assign procedure Id to procedure node
void assignId(){
	char value[10];
	nextToken();
	getId(value);
	p->id=(char*) calloc(10, sizeof(char));
	strcpy(p->id, value);
}

void parseProcedure(){
	p = (struct nodeProcedure*) calloc(1, sizeof(struct nodeProcedure));
	p->ds=(struct nodeDeclSeq*) calloc(1, sizeof(struct nodeDeclSeq));
	p->ss=(struct nodeStmtSeq*) calloc(1, sizeof(struct nodeStmtSeq));

	assignId();
	//check nextToken is IS
	if (nextToken() != IS){
		//error
	}else{
		//current Token is INTEGER or RECORD
		nextToken();
	}
	
	parseDeclSeq(p->ds);
	parseStmtSeq(p->ss);

	//END
	nextToken();
}

void parseDeclSeq(struct nodeDeclSeq *ds2){
	if(currentToken() != INTEGER && currentToken() != RECORD){
		//error
		printf("Error\n");
	}
	ds2->d=(struct nodeDecl*) calloc(1, sizeof(struct nodeDecl));

	parseDecl(ds2->d);
	if(currentToken() == INTEGER || currentToken() == RECORD){
		ds2->ds=(struct nodeDeclSeq*) calloc(1, sizeof(struct nodeDeclSeq));
		parseDeclSeq(ds2->ds);
	}

	//BEGIN일 경우 stmt 문 시작
	nextToken();
}

void parseStmtSeq(struct nodeStmtSeq *ss2){
	ss2->s=(struct nodeStmt*) calloc(1, sizeof(struct nodeStmt));

	parseStmt(ss2->s);
	//END or Not
	nextToken();
	if(currentToken() != END){
		ss2->ss=(struct nodeStmtSeq*) calloc(1, sizeof(struct nodeStmtSeq));
		parseStmtSeq(ss2);
	}
}

void parseStmt(struct nodeStmt *s2){

	int current=currentToken();
	if(current==ID){
		s2->ass=(struct nodeAssign*) calloc(1, sizeof(struct nodeAssign));
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
	}
}

void parseAssign(struct nodeAssign *ass2){

	//assign ID
	char value[10];
	getId(value);
	ass2->id=(char*) calloc(10, sizeof(char));
	strcpy(ass2->id, value);

	int current = nextToken();
	if(current == LPAREN){
		//id <index> := <expr> ;
		ass2->idx=(struct nodeIndex*) calloc(1, sizeof(struct nodeIndex));
		ass2->exp=(struct nodeExpr*) calloc(1, sizeof(struct nodeExpr));
		parseIndex(ass2->idx);
		//assign
		nextToken();
		//expr
		nextToken();
		parseExpr(ass2->exp);
	}else if(current == ASSIGN){
		int current_2 = nextToken();

		if(current_2==CONST || current_2==ID){
			//id := <expr> ;
			ass2->idx=(struct nodeIndex*) calloc(1, sizeof(struct nodeIndex));
			ass2->exp=(struct nodeExpr*) calloc(1, sizeof(struct nodeExpr));
			parseIndex(ass2->idx);
			parseExpr(ass2->exp);
		}else if(current_2==NEW){
			//id := new record [<expr>];
			ass2->exp=(struct nodeExpr*) calloc(1, sizeof(struct nodeExpr));
			//record
			nextToken();
			//LPAREN
			nextToken();
			//expr
			nextToken();
			parseExpr(ass2->exp);
		}else if(current_2==RECORD){
			//id := record id; 
			//id
			int id2 = nextToken();
			char value[10];
			getId(value);
			ass2->id2=(char*) calloc(10, sizeof(char));
			strcpy(ass2->id2, value);
		}
	}

	//semi-colon
	nextToken();
	//printf("\nthis is %d\n",currentToken());
	
}

void parseIndex(struct nodeIndex *idx2){
	if(currentToken() == LPAREN){
		idx2->exp=(struct nodeExpr*) calloc(1, sizeof(struct nodeExpr));
		parseExpr(idx2->exp);
		//RPAREN
		//nextToken();
	}
	//epsilon
	// else if (currentToken() == CONST){
	// 	char value[1];
	// 	idx2->eps=(char*) calloc(10, sizeof(char));
	// 	strcpy(idx2->eps, "eps");
	// }


}

void parseExpr(struct nodeExpr *expr2){
	expr2->tm = (struct nodeTerm*) calloc(1, sizeof(struct nodeTerm));

	parseTerm(expr2->tm);
	//+ or -
	int current = nextToken();
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
	}else{
		prevToken();
	}
	
}

void parseTerm(struct nodeTerm *tm2){
	tm2->fac=(struct nodeFactor*) calloc(1, sizeof(struct nodeFactor));

	parseFactor(tm2->fac);
}

void parseFactor(struct nodeFactor *fac2){
	
	if(currentToken()==ID){
		//IFnextTokent() == LPAREN ELSE
	}else if(currentToken()==CONST){
		int value = getConst();
		printf("\nvalue is%d\n", value);
		fac2->cnt = value;
	}else if(currentToken()==LPAREN){

	}else if(currentToken()==IN){

	}

}

void parseIf(struct nodeIf *i){
	//condition
	nextToken();
	i->c=(struct nodeCond*) calloc(1, sizeof(struct nodeCond));
	parseCond(i->c);
	//then
	nextToken();
	i->sq=(struct nodeStmtSeq*) calloc(1, sizeof(struct nodeStmtSeq));
	parseStmtSeq(i->sq);
	//else or end
	int current = nextToken();
	if(current == ELSE){
		i->sq2=(struct nodeStmtSeq*) calloc(1, sizeof(struct nodeStmtSeq));
		parseStmtSeq(i->sq2);
		//END
		nextToken();
	}
}

void parseCond(struct nodeCond *c){

}

void parseLoop(){
}

void parseOut(struct nodeOut *out){
	//LPAREN
	nextToken();
	//exp
	nextToken();
	out->exp=(struct nodeExpr*) calloc(1, sizeof(struct nodeExpr));
	parseExpr(out->exp);
	//RPAREN
	nextToken();
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
	char value[10];
	nextToken();
	getId(value);
	di2->id=(char*) calloc(10, sizeof(char));
	strcpy(di2->id, value);
	//semi-colon
	nextToken();
	//BEGIN or INTEGER or RECORD
	nextToken();
}

void parseDeclRecord(struct nodeDeclRecord *dr2){
	char value[10];
	nextToken();
	getId(value);
	dr2->id=(char*) calloc(10, sizeof(char));
	strcpy(dr2->id, value);
	//semi-colon
	nextToken();
	//BEGIN or INTEGER or RECORD
	nextToken();

}