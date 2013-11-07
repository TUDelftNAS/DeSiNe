/*This module is created to simulate a dynamic array and to make/alter linked lists
F.A. Kuipers 25/01/2000*/

#include <stdio.h>
#include <math.h>
#include <string.h>
#include <assert.h>

/*dynamic_array represents an array of integers*/
struct dynamic_array{
  int data;                    /*data gives the data in the array*/
  int index;                   /*index gives the place in the array*/
  struct dynamic_array* next;  /*point to the next element in the array*/
};

/*dynamic_vector represents a array of doubles*/
struct dynamic_vector{
  double data;
  int index;
  struct dynamic_vector* next;
};

/*This function calculates the length of a dynamic_array, by retrieving
the maximum index number*/
int length_array(struct dynamic_array* head)
{
  struct dynamic_array* current = head;
  int count = 0;

  if(current!=NULL){
    while(current!=NULL){
      if((current->index)>count)
	count = current->index;
      current = current->next;
    }
    return count+1;
  }
  else
    return 0;
}

/*This function puts an element at the head of the array*/
void putdata(struct dynamic_array** headref, int index, int data)
{
  struct dynamic_array* newnode = malloc(sizeof(struct dynamic_array));
 
  newnode->data = data;
  newnode->index = index;
  newnode->next = (*headref);
  (*headref) = newnode;
}

/*This function retrieves the data placed at a certain index.
If there is no data present, a 0 will be returned*/
int getdata(struct dynamic_array* head, int index)
{
  struct dynamic_array* current = head;
  int count = 0;             /*the index of the node we're currently looking at*/
  int result;
  
  while(current != NULL){
    if(current->index==index)
      return(current->data);
    count++;
    current = current->next;
  }
  return(0);
}

/*This function inserts data at a certain place in the array (index).
This function calls the function putdata*/
void insertdata(struct dynamic_array** headref, int index, int data)
{
  if(*headref==NULL){
    putdata(headref,index,data);
  }
  else{
    struct dynamic_array* current = *headref;
    struct dynamic_array* prevcur;

    while((current!=NULL)&&(current->index!=index)){
      prevcur = current;
      current = current->next;      
    }
  
    if(current!=NULL){
	current->data = data;
    }
    else{
      putdata(&(prevcur->next),index,data);
    }
  }
}

/*This function deallocates the memmory allocated for the
dynamic array. When a dynamic array isn't used any more,
this function should be called*/
void delete_array(struct dynamic_array** headref)
{
  struct dynamic_array* current = *headref;
  struct dynamic_array* next;

  while(current!=NULL){
    next = current->next;
    free(current);
    current = next;
  }
  
  *headref = NULL;
}

/*The function below are the same as above, but apply to
the dynamic array of doubles*/

int length_vector(struct dynamic_vector* head)
{
  struct dynamic_vector* temp = head;
  int count = 0;

  if(temp!=NULL){
    while(temp!=NULL){
      if((temp->index)>count)
	count = temp->index;
      temp = temp->next;
    }
    return count+1;
  }
  else
    return 0;
}

void putdatad(headref, index, data)
struct dynamic_vector** headref;
int index;
double data;
{
  struct dynamic_vector* newnode = malloc(sizeof(struct dynamic_vector));
 
  newnode->data = data;
  newnode->index = index;
  newnode->next = (*headref);
  (*headref) = newnode;
}

double getdatad(head, index)
struct dynamic_vector* head;
int index;
{
  struct dynamic_vector* new = head;
  int count = 0;           
  double result;
  
  while(new != NULL){
    if(new->index==index){
      result = (new->data);
      return result;
    }
    count++;
    new = new->next;
  }
  return 0.0;
}

void insertdatad(headref, index, data)
struct dynamic_vector** headref;
int index;
double data;
{
  if(*headref==NULL){
    putdatad(headref, index, data);
  }
  else{
    struct dynamic_vector* current = *headref;
    struct dynamic_vector* prevcur;

    while((current!=NULL)&&(current->index!=index)){
      prevcur = current;
      current = current->next;      
    }
  
    if(current!=NULL){
	current->data = data;
    }
    else{
      putdatad(&(prevcur->next), index, data);
    }
  }
}

void delete_vector(struct dynamic_vector** headref)
{
  struct dynamic_vector* current = *headref;
  struct dynamic_vector* next;

  while(current!=NULL){
    next = current->next;
    free(current);
    current = next;
  }
  
  *headref = NULL;
}


