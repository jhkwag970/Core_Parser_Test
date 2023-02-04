#include <stdlib.h>

#include <string.h>
#include <ctype.h>
#include <stdio.h>

#include "parser.h"
#include "tree.h"




int main() {  

	//scanner("Correct/1.code");

  // struct nodeProcedure *p;
  // int *a = (int*) calloc(1, sizeof(int));;
  // *a=1009;
  // printf("%d\n", *a);

  Test_scanner("Correct/0_test.code");

  //  struct nodeProcedure *p = (struct nodeProcedure*) calloc(1, sizeof(struct nodeProcedure));
  //  if(p->ds == NULL){
  //   printf("yes");
  //  }
  // p->ds = (struct nodeDeclSeq*) calloc(1, sizeof(struct nodeDeclSeq));
  // p->id="X";

  // struct nodeDeclSeq* ds2 = (p->ds);
  // ds2->d=(struct nodeDecl*) calloc(1, sizeof(struct nodeDecl));

  // struct nodeDecl* d2= (ds2->d);
  // d2->di=(struct nodeDeclInteger*) calloc(1, sizeof(struct nodeDeclInteger));

  // struct nodeDeclInteger* di2 = (d2->di);
  // di2->id = "Integer x;";

  // printf("%s\n", p->id);
  // printf("%s\n", di2->id);

  // p->ds->d=(struct nodeDecl*) calloc(1, sizeof(struct nodeDecl));
  // p->ds->d->di=(struct nodeDeclInteger*) calloc(1, sizeof(struct nodeDeclInteger));
  // p->ds->d->di->id="Integer Y;";

  // printf("%s\n", p->id);
  // printf("%s\n", p->ds->d->di->id);
  // free(p->ds);
  // free(p);
  

  return 0;
}