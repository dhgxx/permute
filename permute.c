#include "stack.h"

/* The train permutation program begins here!*/

Stack           backup[MAXSTACK]; /* To backup the stacks for recursion.*/
long int        bkindex = 0;  /* To number the backed-up stacks. */
long int        frame_depth = 0; /* The depth of the recursion. */
long            total = 0; /* The total modes of the permutation. */

void            Initialize(Stack *, Stack *, Stack *, StackEntry);
void            PrintEntry(StackEntry);
Stack          *BackUp(Stack *);
void            SendTrain(Stack *, Stack *);
void            Permute(Stack *, Stack *, Stack *);

/* To initialize everything to begin. */
void
Initialize(Stack *out, Stack *spur, Stack *in, StackEntry ntrains)
{
  CreateStack(out);
  CreateStack(spur);
  CreateStack(in);

  while (ntrains > 0) {
	Push(ntrains, out);
	ntrains--;
  }
}

/* To print out the entry in a stack. */
void
PrintEntry(StackEntry item)
{
  printf("%ld ", item);
  return;
}

/* To back up a stack for the recursion. */
Stack *
BackUp(Stack *rail)
{
  register Node  *np;
  StackEntry      item;
  Stack           temp;
  CreateStack(&temp);
  CreateStack(&backup[bkindex]); /* 'backup' is declared as a global.*/
  
  if (StackEmpty(rail)) {
	;
  } else {
	np = rail->top;
	while (np != NULL) {
	  Push(np->entry, &temp);
	  np = np->next;
	}
	
	while (!StackEmpty(&temp)) {
	  Pop(&item, &temp);
	  Push(item, &backup[bkindex]);
	}
  }
  
  bkindex++;
  return &backup[bkindex - 1];
}

void
SendTrain(Stack *to, Stack *from)
{
  StackEntry      entry;
  
  if (StackEmpty(from)) {
	Error("No train to be sent!\n");
  } else {
	Pop(&entry, from);
	Push(entry, to);
	return;
  }
}

void
Permute(Stack *out, Stack *in, Stack *spur)
{
  Stack *temp_out;
  Stack *temp_spur;
  Stack *temp_in; /* the backups. */

  if (StackEmpty(out)) {
	
	while (!StackEmpty(spur))
	  SendTrain(in, spur);
	
	TraverseStack(in, PrintEntry); /* A mode is detected, */
	total++;                       /* then print out the results.*/ 
	ClearStack(in);                /* release the memory. */
#ifdef __TRAVERSE__
	printf("\n");
#endif
  } else {

	if (1 - frame_depth % 2) { /* To decide how to send trains. */
	  SendTrain(spur, out);    /* If 'frame_depth' is odd, */
	} else {                   /* 'out' to 'spur'. If 'frame_depth */
	  SendTrain(in, spur);     /* is even, 'spur' to 'in'. */
	}
	
	temp_out = BackUp(out);
	temp_spur = BackUp(spur);
	temp_in = BackUp(in);
	frame_depth++; /* To enter into a new recursion. */
	Permute(temp_out, temp_in, temp_spur);
	frame_depth--; /* Now back to the higher level of recursion. */

	if (!StackEmpty(out) && !StackEmpty(spur))
	  Permute(out, in, spur);
  }
}

int
main()
{
  Stack           rail_out, rail_in, spur;
  StackEntry      ntrains;
  
  printf("How many trains to permute? ");
  scanf("%ld", &ntrains);
  Initialize(&rail_out, &spur, &rail_in, ntrains);
  Permute(&rail_out, &rail_in, &spur);
  printf("The total sum of modes is %ld\n", total);
  printf("the depth is now %ld\n", bkindex);
  exit(0);
}
