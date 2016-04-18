/*Created by H. De Neve and altered by F.A. Kuipers
  05/03/2003*/

/*This Fibonacci file contains all the modules to build, maintain and use a Fibonacci heap.
It makes use of a globally defined type fiblist for the elements of the Fibonacci heap. It only requires
two variables in your main program, one for the name of the list and one for the number of elements in the list, both pointers.

Besides the necessary information fields to build the Fibonacci heap ( degree,mark,parent,child,left,right), the elements of
the Fibonacci list contain three information fields. The heap is ordered on the basis of the "key" value. The remaining
information fields are optional attributes, necessarily identifying the object of which the value is expressed by the value of "key".
The names of these additional fields originate from the k-shortest path problem where the list is composed of elements characterised
by a node identifier and a node element, both integers.The additional fields do not interfere with the sorting mechanism.
The additional fields are declared as integers which leaves the possibility that they are originating from pointers pointing to
information fields with a much larger information content than just two integers.

Functions:
------------

void create_heap(heap,num)

	heap: pointer to pointer to variable of type fiblist
	num:  pointer to int

	This function creates and intialises a Fibonacci heap called "heap". The number of elements in the heap, "*num" is set
	to zero


struct fiblist *insert(heap,num,key,id,el)

	heap: pointer to pointer to variable of type fiblist
	num:  pointer to int
	key:  double
	id:   int
	el:   int

	This function returns a pointer to the element which has been added to the Fibonacci heap called "heap". The element
	is characterised by its value "key" and the two additional information fields, "id" and "el". The number of elements
	in the Fibonacci heap is increased by one.


struct fiblist *extract_min_from_list(heap,num)

	heap: pointer to pointer to variable of type fiblist
	num:  pointer to int

	This function returns a pointer to the element bearing the minimum value of "key" in the Fibonacci heap called "heap".
	The minimum element is removed from the list and num is decreased by one.


void decrease_key(heap,x,k)

	heap: pointer to pointer to variable of type fiblist
	x:    pointer to variable of type fiblist
	k:    double

	This function decreases the value of "key" in the element pointed to by x in the heap called "heap" to k.

*/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "samcra_util.h"


/*listfunctions for double linked Fibonacci heap*/
void create_heap(heap,num)
     struct fiblist **heap;
     int *num;
{
  *heap=NULL;	/*initialisation of the Fibonacci heap, minpointer = NULL */
  *num=0;		/*initialisation of the seperate counter which keeps track of the number of elements in the heap*/
}

struct fiblist *insert(heap,num,key,id,el)
     struct fiblist **heap;
     int *num;
     double key;
     int id,el;
{
  struct fiblist *newelement;
  newelement=(struct fiblist*) malloc(sizeof(*newelement)); /*allocating memory for the new element*/

  newelement->key=key;
  newelement->id=id;
  newelement->el=el;
  newelement->degree=0;
  newelement->mark=0;
  newelement->parent=NULL;
  newelement->child=NULL;
  newelement->left=newelement;
  newelement->right=newelement;

  if(*heap==NULL)       /*if heap points to the NULL pointer*/
    {
      *heap=newelement;
      *num=1;
    }
  else		      /*concatenation*/
    {
      newelement->left=(*heap)->left;
      (*heap)->left->right=newelement;
      (*heap)->left=newelement;
      newelement->right=*heap;
      *num+=1;
      if(newelement->key < (*heap)->key)
  	*heap=newelement;  			/*changing the pointer to the element containing the minimum key*/
    }
  return(newelement);
}

struct fiblist *extract_min_from_list(heap,num)      /*returns a pointer to the element containing the minimum key and deletes the element from the heap*/
     struct fiblist **heap;
     int *num;
{
  int i;
  struct fiblist *a,*b,*z, *s;
  void consolidate();

  z=*heap;
  if(z!=NULL)
    {
      if(z->child!=NULL)	     /*updating the children of z, if any*/
	{
	  a=z->child;
	  for(i=1;i<=(z->degree);i++){ /*z->degree gives the number of children of z*/
	    if(a!=a->right){
	      b=a->right;
	      a->left->right=a->right;  /*remove a from children*/
	      a->right->left=a->left;
	      a->left=z->left;	  /*insert a into main root list, left from z*/
	      z->left->right=a;
	      z->left=a;
	      a->right=z;
	      a->parent=NULL;
	      a=b;
	    }
	  }
	  a->left=z->left;	  /*remove last child of z*/
	  z->left->right=a;
	  z->left=a;
	  a->right=z;
	  a->parent=NULL;
	  z->child=NULL;
	}
      if(z==z->right){
	*heap=NULL;
      }
      else
	{
	  *heap=z->right;
	  z->left->right=z->right;      /*removing z*/
	  z->right->left=z->left;
	  *num-=1;
	  consolidate(heap,num);
	}
    }
  return(z);
}


void consolidate(heap,num)
     struct fiblist **heap;
     int *num;
{
  int i,order,d;
  struct fiblist **A, *a, *x, *y, *s;

  //order=(int) (log(*num)/log((1+sqrt(5))/2)+2);
  order = (*num)+1; /*I am not sure what the worst-case maximum of the degree is*/
  A = fiblist_vector(0,order);
  //for(i=0; i<=order; i++) A[i]=NULL;

  x=*heap;
  d=(*heap)->degree;
  A[d]=*heap;
  a=(*heap)->right;
  while(a!=*heap)
    {
      x=a;
      d=x->degree;
      while(A[d]!=NULL)
	{
	  y=A[d];
	  if(x->key > y->key)
	    {
	      s=x;	       /*reversing x and y*/
	      x=y;
	      y=s;
	    }

	  if(y==*heap)
	    *heap=(*heap)->right;
	  if(y==a)
	    a=y->left;

	  y->left->right=y->right;  /*remove y*/
	  y->right->left=y->left;
	  y->parent=x;   			/*The only place where the parent info is updated*/
	  y->mark=0;
  (x->degree)+=1;                 /*Degrees can only increment, never decrease*/
	  if(x->child!=NULL)	  /*restoring double linked list at one level below*/
	    {
	      y->left=x->child->left;
	      x->child->left->right=y;
	      x->child->left=y;
	      y->right=x->child;
	    }
	  else
	    {
	      x->child=y;
	      y->left=y;
	      y->right=y;
	    }
	  A[d]=NULL;
	  d+=1;
	}
      A[d]=x;
      a=a->right;
    }
  *heap=NULL;
  for(i=0;i<=order;i++)
    {
      if(A[i]!=NULL)
	{
	  if(*heap==NULL)
	    {
	      *heap=A[i];
	      A[i]->left=A[i];
	      A[i]->right=A[i];
	    }
	  else
	    {
	      A[i]->left=(*heap)->left;
	      (*heap)->left->right=A[i];
	      (*heap)->left=A[i];
	      A[i]->right=*heap;
	      if(A[i]->key < (*heap)->key)
		*heap=A[i];
	    }
	}
    }
  free_fiblist_vector(A,0,order);
}

void decrease_key(heap,x,k)
     struct fiblist **heap;
     struct fiblist *x;
     double k;
{
  struct fiblist *y, *s;
  void cut();
  void cascading_cut();

  if(k>x->key)
    fprintf(stderr,"New value is larger than key\n");
  else
    {
      x->key=k;
      y=x->parent;
      if((y!=NULL)&&(x->key<y->key))
	{
	  cut(heap,x,y);
	  cascading_cut(heap,y);
	}
      if((x->key)<((*heap)->key))
	(*heap)=x;
    }
}

void cut(heap,x,y)
     struct fiblist **heap;
     struct fiblist *x, *y;
{
  if(x==x->right)
    y->child=NULL;
  else
    {
      if(x==y->child)
	y->child=x->right;
      x->left->right=x->right;     /*remove x*/
      x->right->left=x->left;
    }
  (y->degree)-=1;

  x->left=(*heap)->left;	    /*insert x into heap*/
  (*heap)->left->right=x;
  (*heap)->left=x;
  x->right=(*heap);
  x->parent=NULL;
  x->mark=0;
}

void cascading_cut(heap,y)
     struct fiblist **heap;
     struct fiblist *y;
{
  struct fiblist *z;
  void cut();
  void cascading_cut();

  z=y->parent;
  if(z!=NULL)
    {
      if(y->mark==0)
	y->mark=1;
      else
	{
	  cut(heap,y,z);
	  cascading_cut(heap,z);
	}
    }
}

void putlist(struct el** headref, int index, struct fiblist* list)
{
  struct el* newelement = malloc(sizeof(struct el));

  newelement->list = list;
  newelement->index = index;
  newelement->next = (*headref);
  (*headref) = newelement;
}

void delete_list(struct el** headref)
{
  struct el* current = *headref;
  struct el* next;

  while(current!=NULL){
    next = current->next;
    free(current->list);
    free(current);
    current = next;
  }
  *headref = NULL;
}

void insertlist(struct el** headref, int index, struct fiblist *list)
{
  if(*headref==NULL){
    putlist(headref,index,list);
  }
  else{
    struct el* current = *headref;
    struct el* prevcur;

    while((current!=NULL)&&(current->index!=index)){
      prevcur = current;
      current = current->next;
    }

    if(current!=NULL){
      current->list = list;
    }
    else{
      putlist(&(prevcur->next),index,list);
    }
  }
}

struct fiblist *getlist(struct el* head, int index)
{
  struct el* current = head;
  int count = 0;             /*the index of the node we're currently looking at*/

  while(current != NULL){
    if(current->index==index){
      return(current->list);
    }
    count++;
    current = current->next;
  }
  fprintf(stderr,"error\n");
  return(NULL);
}
