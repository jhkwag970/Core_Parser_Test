#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "scanner.h"
#include "core.h"
#include "tree.h"
#include "parser.h"

#define VNAME 20
#define VNUM 20
#define CNTNULL -1

void parseProcedure();
void parseDeclSeq(struct nodeDeclSeq *ds2);
void parseStmtSeq(struct nodeStmtSeq *ss2);
void parseDecl(struct nodeDecl *d2);
void parseDeclInteger(struct nodeDeclInteger *di2);
void parseDeclRecord(struct nodeDeclRecord *dr2);
void parseStmt(struct nodeStmt *s2);
void parseAssign(struct nodeAssign *ass2);
void parseIf(struct nodeIf *i2);
void parseLoop(struct nodeLoop *lp2);
void parseOut(struct nodeOut *out2);
void parseIndex(struct nodeIndex *idx2);
void parseExpr(struct nodeExpr *exp2);
void parseTerm(struct nodeTerm *tm2);
void parseFactor(struct nodeFactor *fac2);
void parseCond(struct nodeCond *c2);
void parseCmpr(struct nodeCmpr *cmp2);
void printIntArray();
void printRecArray();
void varChecker(char *value);
void varUndeclaredChecker(char *value);
void varRecChecker(char *value);

struct nodeProcedure *p;
static char intArray[VNUM][VNAME];
static char recArray[VNUM][VNAME];

static int intIdx;
static int recIdx;
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
	// printf("------------------------\n");
	// printf("filename: %s\n", filename);
	scanner_open(filename);
	intIdx=0;
	recIdx=0;
	parseProcedure();
	
	scanner_close();
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



/*
*
* Parse functions go here
*
*/


//(x)
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

	expectedToken(BEGIN);

	nextToken();
	//Later check 

	parseStmtSeq(p->ss);

	//end checker
	expectedToken(END);
	
	nextToken();
	expectedToken(EOS);
}

//(x)
void parseDeclSeq(struct nodeDeclSeq *ds2){
	
	if(currentToken() != INTEGER && currentToken() != RECORD){
		char actualStr[20];
		tokenString(actualStr, currentToken());

		printf("Error: expected INTEGER or RECORD or BEGIN but recieved %s\n", actualStr);
		exit(0);
	}
	ds2->d=(struct nodeDecl*) calloc(1, sizeof(struct nodeDecl));

	parseDecl(ds2->d);
	nextToken();

	if(currentToken() == INTEGER || currentToken() == RECORD){
		ds2->ds=(struct nodeDeclSeq*) calloc(1, sizeof(struct nodeDeclSeq));
		parseDeclSeq(ds2->ds);
	}


}

//(x)
void parseStmtSeq(struct nodeStmtSeq *ss2){
	ss2->s=(struct nodeStmt*) calloc(1, sizeof(struct nodeStmt));

	parseStmt(ss2->s);
	//END or Not
    nextToken();
	
	if(currentToken() == ID || currentToken() == IF || currentToken() == WHILE || currentToken() == OUT){

		ss2->ss=(struct nodeStmtSeq*) calloc(1, sizeof(struct nodeStmtSeq));
		parseStmtSeq(ss2->ss);
	}
	
}

// (x)
void parseStmt(struct nodeStmt *s2){
	

	int current=currentToken();
	
	if(current==ID){
		s2->ass=(struct nodeAssign*) calloc(1, sizeof(struct nodeAssign));
		//(x)
		parseAssign(s2->ass);
	}else if(current==IF){
		s2->i=(struct nodeIf*) calloc(1, sizeof(struct nodeIf));
		//(x)
		parseIf(s2->i);
	}else if(current==WHILE){
		s2->lp=(struct nodeLoop*) calloc(1, sizeof(struct nodeLoop));
		//(x)
		parseLoop(s2->lp);
	}else if(current==OUT){
		s2->out=(struct nodeOut*) calloc(1, sizeof(struct nodeOut));
		//(x)
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
	varUndeclaredChecker(value);

	ass2->id=(char*) calloc(10, sizeof(char));
	strcpy(ass2->id, value);

	int current = nextToken();
	if(current == LBRACE){
		//id [<index>] := <expr> ;
		varRecChecker(value);
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
			varRecChecker(value);

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
			varRecChecker(value);
			//id := record id; 
			//id
			nextToken();
			expectedToken(ID);

			char value2[10];
			getId(value2);
			varUndeclaredChecker(value2);
			varRecChecker(value2);
			
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

//(X)
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

//(x)
void parseExpr(struct nodeExpr *expr2){
	exprChecker();
	expr2->tm = (struct nodeTerm*) calloc(1, sizeof(struct nodeTerm));
	parseTerm(expr2->tm);
	//+ or -
	int current = currentToken();
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
	
}

//(x)
void parseTerm(struct nodeTerm *tm2){
	tm2->fac=(struct nodeFactor*) calloc(1, sizeof(struct nodeFactor));
	parseFactor(tm2->fac);

	int current = currentToken();

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
}

//(x)

void parseFactor(struct nodeFactor *fac2){
	int current = currentToken();
	fac2->cnt=CNTNULL;
	if(current==ID){

		char value[10];
		getId(value);
		varUndeclaredChecker(value);

		fac2->id=(char*) calloc(10, sizeof(char));
		strcpy(fac2->id, value);

		int current_2=nextToken();
		if(current_2==LBRACE){
			varRecChecker(value);
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

//(x)
void parseLoop(struct nodeLoop *lp2){
	lp2->c = (struct nodeCond*) calloc(1, sizeof(struct nodeCond));
	lp2->ss= (struct nodeStmtSeq*) calloc(1, sizeof(struct nodeStmtSeq));
	//cond
	nextToken();
	parseCond(lp2->c);

	//do check
	expectedToken(DO);

	//stmt-seq
	nextToken();
	parseStmtSeq(lp2->ss);

	//end check
	expectedToken(END);
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

//(x)
void parseOut(struct nodeOut *out){
	//LPAREN
	nextToken();
	expectedToken(LPAREN);

	//exp
	nextToken();
	out->exp=(struct nodeExpr*) calloc(1, sizeof(struct nodeExpr));
	parseExpr(out->exp);

	expectedToken(RPAREN);

	//semi-colon
	nextToken();
	expectedToken(SEMICOLON);
}

//(x)
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

//(x)
void parseDeclInteger(struct nodeDeclInteger *di2){
	//ID
	nextToken();
	expectedToken(ID);

	char value[10];
	getId(value);
	varChecker(value);

	di2->id=(char*) calloc(10, sizeof(char));
	strcpy(di2->id, value);
	strcpy(intArray[intIdx], value);
	intIdx++;

	//semi-colon
	nextToken();
	expectedToken(SEMICOLON);
}

//(x)
void parseDeclRecord(struct nodeDeclRecord *dr2){
	nextToken();
	expectedToken(ID);
	
	char value[10];
	getId(value);
	varChecker(value);

	dr2->id=(char*) calloc(10, sizeof(char));
	strcpy(dr2->id, value);
	strcpy(recArray[recIdx], value);
	recIdx++;

	//semi-colon
	nextToken();
	expectedToken(SEMICOLON);
}

void varChecker(char *value){
	int i, j;
	for(i=0; i < intIdx;i++){
		if((!strcmp(intArray[i], value))){
			printf("Error: %s is already declared\n", value);
			exit(0);
		}
	}
	for(j=0; j < recIdx; j++){
		if((!strcmp(recArray[j], value))){
			printf("Error: %s is already declared\n", value);
			exit(0);
		}
	}
}

void varUndeclaredChecker(char *value){
	int i, j;
	for(i=0; i < intIdx;i++){
		if((!strcmp(intArray[i], value))){
			return;
		}
	}
	for(j=0; j < recIdx; j++){
		if((!strcmp(recArray[j], value))){
			return;
		}
	}
	printf("Error: %s is undeclared variable\n", value);
	exit(0);
}

void varRecChecker(char *value){
	int i;
	for(i=0;i< recIdx;i++){
		if((!strcmp(recArray[i], value))){
			return;
		}
	}
	printf("Error: %s is not Record variable\n", value);
	exit(0);
}


void printIntArray(){
	int i;
	for(i=0; i< intIdx;i++){
		printf("Int Variable: %s\n", intArray[i]);
	}
}

void printRecArray(){
	int i;
	for(i=0; i< recIdx;i++){
		printf("Rec Variable: %s\n", recArray[i]);
	}
}
