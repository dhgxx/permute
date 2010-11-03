#ifndef _PERMUTE_H_
#define _PERMUTE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*If you need more space, increase MAXSTACK*/
#define MAXSTACK 16384*100 

/*A linked stack implementation*/

typedef long int StackEntry;

typedef struct node {
  StackEntry entry;
  struct node *next;
} Node;

typedef struct stack {
  Node *top;
} Stack;

typedef enum bool {
  FALSE = 0,
  TRUE = 1
} Boolean;

void Error(const char *);
void CreateStack(Stack *);
Boolean StackEmpty(Stack *);
Node *MakeNode(StackEntry);
void Push(StackEntry, Stack *);
void Pop(StackEntry *, Stack *);
void ClearStack(Stack *);
void TraverseStack(Stack *, void (*) (StackEntry));

#endif /* _PERMUTE_H_ */
