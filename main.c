#include <stdlib.h>

#include <string.h>
#include <ctype.h>
#include <stdio.h>

#include "scanner.h"
#include "core.h"
#include "tree.h"

static struct nodeProcedure *p;
static int expected;

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
void parseCmpr();




int main() {  

	//scanner("Correct/0_test copy 19.code");
  //Test_scanner("Correct/0_test.code");

//     scanner_open("Correct/0_test.code");
//   while (currentToken() != EOS && currentToken() != ERROR) {
// 	parser();
//     nextToken();
//   }
//   //printf("\n-----------------------------------\n");
//   //printf("procedure Id is %s\n", p->id);
//   //printf("Dec Id is: %s\n", p->ds->d->di->id);
//   //printf("Assign Id is: %s\n",p->ss->s->ass->id);
//   //printf("expr1 is: %d\n",p->ss->s->ass->exp->tm->fac->cnt);
//   scanner_close();

//   scanner_open("Correct/0_test copy 18.code");
//   while (currentToken() != EOS && currentToken() != ERROR) {
// 	parser();
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

  scanner_open("Correct/0_test copy 19.code");
  while (currentToken() != EOS && currentToken() != ERROR) {
	  parser();
    nextToken();
  }
  printf("\n-----------------------------------\n");
  printf("procedure Id is %s\n", p->id);
  printf("Dec int Id is: %s\n", p->ds->d->di->id);
  printf("Dec record Id is: %s\n", p->ds->ds->d->dr->id);
  printf("Dec int Id is: %s\n", p->ds->ds->ds->d->di->id);

  printf("Cond1 %d\n", p->ss->s->i->c->cmp->exp->tm->fac->cnt);
  printf("Cond sign %s\n", p->ss->s->i->c->cmp->sign);
  printf("Cond2 %d\n", p->ss->s->i->c->cmp->exp2->tm->fac->cnt);

  printf("then stmt id %s\n", p->ss->s->i->ss->s->ass->id);
  printf("then stmt exp %d\n", p->ss->s->i->ss->s->ass->exp->tm->fac->cnt);

  printf("then2 stmt id %s\n", p->ss->s->i->ss->ss->s->ass->id);
  printf("then2 stmt exp %d\n", p->ss->s->i->ss->ss->s->ass->exp->tm->fac->cnt);

  printf("else stmt id %s\n", p->ss->s->i->ss2->s->ass->id);
  printf("else stmt exp %d\n", p->ss->s->i->ss2->s->ass->exp->tm->fac->cnt);
    printf("else stmt2 id %s\n", p->ss->s->i->ss2->ss->s->ass->id);
  printf("else stmt2 exp %d\n", p->ss->s->i->ss2->ss->s->ass->exp->tm->fac->cnt);

  //   //printf("else stmt id %s\n", p->ss->s->i->ss2->s->ass->id); working
//   //printf("else stmt exp %d\n", p->ss->s->i->ss2->s->ass->exp->tm->fac->cnt); working
  

  return 0;
}

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

	assignId();;
	//check nextToken is IS
	if (nextToken() != IS){
		//error
	}else{
		//current Token is INTEGER or RECORD
		nextToken();
	}
	parseDeclSeq(p->ds);
	nextToken();
	parseStmtSeq(p->ss);
}

void parseDeclSeq(struct nodeDeclSeq *ds2){
	if(currentToken() != INTEGER && currentToken() != RECORD){
		//error
		//printf("Error\n");
	}
	ds2->d=(struct nodeDecl*) calloc(1, sizeof(struct nodeDecl));
	
	parseDecl(ds2->d);
	nextToken();
	if(currentToken() == INTEGER || currentToken() == RECORD){
		ds2->ds=(struct nodeDeclSeq*) calloc(1, sizeof(struct nodeDeclSeq));
		parseDeclSeq(ds2->ds);

	}

}

void parseStmtSeq(struct nodeStmtSeq *ss2){
	////printf("\ncurrent is %d", currentToken());
	ss2->s=(struct nodeStmt*) calloc(1, sizeof(struct nodeStmt));

	////printf("\ncurrent is %d\n",currentToken());
	parseStmt(ss2->s);
	//END or NoT
	
    nextToken();
	
  ////printf("\ncurrent is %d\n",currentToken());
	
	if(currentToken() == ID || currentToken() == IF || currentToken() == WHILE || currentToken() == OUT){
        //printf("Stmt2 current is %d\n",currentToken());
		ss2->ss=(struct nodeStmtSeq*) calloc(1, sizeof(struct nodeStmtSeq));
		parseStmtSeq(ss2->ss);
	}
	// if(currentToken() == END){
	// 	return;
	// }
}

void parseStmt(struct nodeStmt *s2){
	
	//nextToken();
	int current=currentToken();
	
	if(current==ID){
		s2->ass=(struct nodeAssign*) calloc(1, sizeof(struct nodeAssign));
		parseAssign(s2->ass);
    //printf("Assign current is %d\n", currentToken());
	}else if(current==IF){
		s2->i=(struct nodeIf*) calloc(1, sizeof(struct nodeIf));
		parseIf(s2->i);
		//printf("\nLast stmt current is %d\n", currentToken()); //THENc
		nextToken();
		//printf("\nLast stmt2 current is %d\n", currentToken()); //THENc
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
	////printf("\ncurrent is %d", currentToken());
	char value[10];
	getId(value);
	////printf("\nid is %s\n", value);
	ass2->id=(char*) calloc(10, sizeof(char));
  ////printf("%d\n", ass2);
  // //printf("then stmt id addr%d\n", p->ss->s->i->ss->s->ass);
  // //printf("then stmt id addr%d\n", p->ss->s->i->ss2->s->ass);
	strcpy(ass2->id, value);

	
	int current = nextToken();
	
	if(current == LBRACE){
		//id <index> := <expr> 
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
		////printf("\ncurrent is %d", current_2);

		if(current_2==CONST || current_2==ID || current_2==IN || current_2==LPAREN){
			//id := <expr> ;
			////printf("\ncurrent is %d", current_2);	
			////printf("\ncurrent is %d", currentToken());	
			ass2->idx=(struct nodeIndex*) calloc(1, sizeof(struct nodeIndex));
			ass2->exp=(struct nodeExpr*) calloc(1, sizeof(struct nodeExpr));
			parseIndex(ass2->idx);
			parseExpr(ass2->exp);
			
		}else if(current_2==NEW){
			//id := new record [<expr>];
			ass2->exp=(struct nodeExpr*) calloc(1, sizeof(struct nodeExpr));
			//record
			nextToken();
			//LBRACE
			nextToken();
			//expr
			nextToken();
			////printf("\ncurrent is %d", currentToken());
			parseExpr(ass2->exp);
			//Semi-colon
			nextToken();
		}else if(current_2==RECORD){
			//id := record id; 
			//id
			nextToken();
			char value[10];
			getId(value);
			////printf("\nid is %s\n", value);
			ass2->id2=(char*) calloc(10, sizeof(char));
			strcpy(ass2->id2, value);
			// //printf("\nvalue is %s", ass2->id2);
			// //printf("\nvalue is %s", ass2->id);
			nextToken();
		}
	}
	//printf("this is %d\n",currentToken());
	////printf("\nthis is %d\n",currentToken());
	
}

void parseIndex(struct nodeIndex *idx2){

	if(currentToken() == LBRACE){
		////printf("\ncurrent is %d\n", currentToken());
		//expr
		nextToken();
		idx2->exp=(struct nodeExpr*) calloc(1, sizeof(struct nodeExpr));
		parseExpr(idx2->exp);
		////printf("\ncurrent is %d\n", currentToken());

		//RBRACE check
	}
	////printf("\nIndex current is %d\n", currentToken());
	//epsilon
	// else if (currentToken() == CONST){
	// 	char value[1];
	// 	idx2->eps=(char*) calloc(10, sizeof(char));
	// 	strcpy(idx2->eps, "eps");
	// }


}

void parseExpr(struct nodeExpr *expr2){
	expr2->tm = (struct nodeTerm*) calloc(1, sizeof(struct nodeTerm));

	////printf("\nExpr current is %d\n", currentToken());
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
	////printf("\nTerm current is %d\n", currentToken());
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
	////printf("\nFac current is %d\n",currentToken());
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

			//RBRACE
			nextToken();
		}
		
	}else if(current==CONST){
		int value = getConst();
		//printf("\nvalue is%d\n", value);
		fac2->cnt = value;
		
		nextToken();
		//printf("current is %d\n", currentToken());
	}else if(current==LPAREN){
		//expr
		nextToken();
		fac2->exp=(struct nodeExpr*) calloc(1, sizeof(struct nodeExpr));
		parseExpr(fac2->exp);

		//RPAREN check

		nextToken();
	}else if(current==IN){
		////printf("\nIN current is %d\n", currentToken());
		// fac2->id=(char*) calloc(10, sizeof(char));
		// strcpy(fac2->id, "in");
		////printf("\nIN2 current is %d\n", currentToken());

		//LPAREN
		nextToken();
		
		//RPAREN
		nextToken();

		nextToken();
		
	}
	////printf("\nparse Fact current is %d", currentToken());
	
}

void parseIf(struct nodeIf *i2){
	////printf("\ncurrent is %d\n", currentToken());
	//condition
	nextToken();
	////printf("\ncurrent is %d\n", currentToken());
	i2->c=(struct nodeCond*) calloc(1, sizeof(struct nodeCond));
	parseCond(i2->c);
	nextToken();

	i2->ss=(struct nodeStmtSeq*) calloc(1, sizeof(struct nodeStmtSeq));
	parseStmtSeq(i2->ss);
	int current = currentToken();
	//printf("ELSE is %d\n", currentToken());
	if(current == ELSE){
		i2->ss2=(struct nodeStmtSeq*) calloc(1, sizeof(struct nodeStmtSeq));
		nextToken();
		//printf("Inside ELSE %d\n", currentToken());
		parseStmtSeq(i2->ss2);
		//printf("Inside ELSE2 %d\n", currentToken());
	}
}

void parseCond(struct nodeCond *c2){
	////printf("\ncurrent is %d\n", currentToken());
	int current = currentToken();
	if(current==CONST || current==ID || current==IN || current==LPAREN){
		c2->cmp=(struct nodeCmpr*) calloc(1, sizeof(struct nodeCmpr));
		parseCmpr(c2->cmp); //then or-then

		int current_2= currentToken();
		////printf("\nloop current is %d\n", currentToken());
		if(current_2==OR || current_2==AND){

			if(current_2==OR){
				strcpy(c2->sign, "OR");
			}else if(current_2==AND){
				strcpy(c2->sign, "AND");
			}
			
			c2->c=(struct nodeCond*) calloc(1, sizeof(struct nodeCond));
			c2->sign=(char*) calloc(1, sizeof(char));
			nextToken();
			parseCond(c2->c);
		}

	}else if(current ==NOT){

	} //THEN (1) then(1!)
	

}

void parseLoop(struct nodeLoop *lp2){
}

void parseCmpr(struct nodeCmpr  *cmp2){
	cmp2->exp=(struct nodeExpr*) calloc(1, sizeof(struct nodeExpr));
	cmp2->exp2=(struct nodeExpr*) calloc(1, sizeof(struct nodeExpr));
	cmp2->sign =(char*) calloc(1, sizeof(char));
	////printf("\nloop current is %d\n", currentToken());
	parseExpr(cmp2->exp);
	//sign = or <
	int current=currentToken();
	////printf("\nloop current is %d\n", currentToken());
	if(current == EQUAL){
		strcpy(cmp2->sign, "=");
	}else if (current == LESS){
		strcpy(cmp2->sign, "<");
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
		////printf("\ncurrent is %d\n",currentToken());
	}
	if(currentToken() == RECORD){
		d2->dr=(struct nodeDeclRecord*) calloc(1, sizeof(struct nodeDeclRecord));
		parseDeclRecord(d2->dr);
	}
	////printf("\ncurrent is %d\n",currentToken());
}

void parseDeclInteger(struct nodeDeclInteger *di2){
	char value[10];
	nextToken();
	getId(value);
	di2->id=(char*) calloc(10, sizeof(char));
	strcpy(di2->id, value);
	////printf("\n Value is %s\n", di2->id);
	//semi-colon
	nextToken();
	////printf("\ncurrent is %d\n",currentToken());
}

void parseDeclRecord(struct nodeDeclRecord *dr2){
	char value[10];
	nextToken();
	getId(value);
	dr2->id=(char*) calloc(10, sizeof(char));
	strcpy(dr2->id, value);
	//semi-colon
	nextToken();
}