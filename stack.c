#include "stack.h"

void
Error(const char *message)
{
  if (message == NULL) {
	printf("Null message! Not printed!\n");
	exit(0);
  } else {
	fprintf(stderr, message);
	exit(0);
  }
}

void
CreateStack(Stack *s)
{
  if (s == NULL)
	Error("Stack initialization failed!\n");
  
  if (s->top == NULL)
	return;
  
  s->top = NULL;
}

Boolean
StackEmpty(Stack *s)
{
  if (s == NULL)
	Error("Error, Stack is not initialized!\n");
  
  return (s->top == NULL) ? TRUE : FALSE;
}

Node *
MakeNode(StackEntry item)
{
  register Node  *np;
  
  if ((np = malloc(sizeof(Node))) == NULL) {
	Error("Error making a node!");
  } else {
	np->entry = item;
	np->next = NULL;
  }
  
  return np;
}

void
Push(StackEntry item, Stack *s)
{
  register Node  *np;
  np = MakeNode(item);
  
  if (s == NULL)
	Error("Stack not initialized!\n");
  
  np->next = s->top;
  s->top = np;
}

void
Pop(StackEntry *item, Stack *s)
{
  register Node  *np;
  
  if (StackEmpty(s))
	Error("Error popping nodes from an empty stack!\n");
  
  np = s->top;
  s->top = np->next;
  *item = np->entry;
  np->next = NULL;
  free(np);
}

void
ClearStack(Stack *s)
{
  static StackEntry item;
  
  while (!StackEmpty(s))
	Pop(&item, s);
}

void
TraverseStack(Stack *s, void (*func_p) (StackEntry item))
{
#ifdef __TRAVERSE__
  register Node  *np;
  
  if (StackEmpty(s)) {
	Error("Stack empty, operations not executed.\n");
  } else {
	np = s->top;
	
	while (np != NULL) {
	  func_p(np->entry);
	  np = np->next;
	}
	
  }
#endif
}
