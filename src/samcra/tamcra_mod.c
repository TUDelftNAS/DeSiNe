/*
tamcra_mod.c
This modules calculates the tamcra-path between a source and destination node
F.A. Kuipers 18/02/2000
*/


#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "samcra_util.h"

typedef struct elm{
	int k;
	int first;
	struct elm *next;
	} element;

void tamcrapath(START,END,adj,max,datadj,numm,A,aantalnodes,buffer,path,hopcount,minimum_k,k_used)

int START;
int END;
int **adj;
int *max;
double ***datadj;
int numm;
int aantalnodes;
double *A;
int buffer;
int **path;
int *hopcount;
int *minimum_k;
int *k_used;

{
  int countdown,entries;
  int i,j,l,m,n,k,a,u,v,q,r,s,p,*counter,*num,pathcounter,*max_q;
  double ref, newvalue, *intermediate, endvalue;
  int **previ, **prevj, **poscounter;
  double ***sum;
  struct fiblist *helppo, **heap, **M, ***N;
  struct fiblist *selectmaximum();
  element *nextpointer,*newpointer;

  /*declaration of the functions maintaining the Fibonacci heap, see Cormen for implementing and maintaining Fibonacci heaps*/
  void create_heap();
  struct fiblist *extract_min_from_list();
  struct fiblist *insert();
  void consolidate();
  void decrease_key();
  void cut();
  void cascading_cut();


  /*memory allocation*/
  counter = c_ivector(1,aantalnodes);
  num = c_ivector(1,aantalnodes);
  intermediate = c_dvector(1,numm);
  max_q = c_ivector(1,aantalnodes);
  previ = c_imatrix(1,aantalnodes,1,buffer);      //previous node in the path
  prevj = c_imatrix(1,aantalnodes,1,buffer);      //index of previous node
  poscounter = c_imatrix(1,aantalnodes,1,buffer);
  sum = c_d3tensor(1,numm,1,aantalnodes,1,buffer);  /*keeps track of the sum of the linkmetrics on the path*/
  heap = fiblist_vector(1,1);
  M = fiblist_vector(1,aantalnodes);
  N = fiblist_matrix(1,aantalnodes,1,buffer);

  create_heap(heap,num);
  helppo=insert(heap,num,0.0,START,1);
  M[START]=helppo;
  N[START][1]=helppo;
  counter[START]+=1;
  for(l=1; l<=numm; l++){
    sum[l][START][1]=0.0;
  }

  k=0;
  countdown=0;  /*because only N-1 connections are measured, but in this case also END is taken into account*/
  //pathcounter=0;
  entries=0;
  endvalue = 1.0;
  (*minimum_k)=0;
  (*k_used) = 0;

  /*main algorithm*/
  while(countdown < buffer)
    {
      /*
	Select the minimum element from the Fibonacci list
      */
      helppo=extract_min_from_list(heap,num);

      if(helppo==NULL)
	{
	  countdown=buffer;
	}
      else
	{
	  i=helppo->id; /*i represents the extracted node from the fib heap*/
	  j=helppo->el;

	  if(i==START)
	    q=1;
	  else{
	    q=poscounter[previ[i][j]][prevj[i][j]];
	  }
	  for(s=1;s<=buffer;s++){
	    if(poscounter[i][s]==q){
	      q++;
	      s=0;
	    }/*if*/
	  }/*for*/
	  poscounter[i][j]=q;
	  max_q[i]=q;

	  if(i==END){
	    //countdown++;
	    pathcounter=1;
	    u=i;
	    v=j;
	    while(u!=START){
	      path[countdown][pathcounter++]=u;
	      s=u;
	      u=previ[u][v];
	      v=prevj[s][v];
	    }
	    path[countdown][pathcounter]=u;
	    hopcount[countdown++] = pathcounter;   /*number of hops taken by the path as calculated by tamcra*/
	  }

	  for(m=1; m<=max[i]; m++)
	    {
	      /*Go to the mth neighbour of node i*/
	      a=adj[i][m];

	      newvalue=0;
	      /*
		intermediate[l] = sum of all the lth constraints up to node a
		newvalue = maximum of intermediate[l] devided by the requested
		lth constraint
	      */
	      for(l=1; l<=numm; l++)
		{
		  intermediate[l]=(sum[l][i][j]+datadj[l][i][m]);
		  if((intermediate[l]/A[l]) > newvalue)
		    newvalue=intermediate[l]/A[l];
		} /*for*/

	      p=1;
	      /*
		Check if a is not dominated. This is checked against all entries
		that have entered the queue of node a. If a is not dominated then
		p=counter[a]+1. Counter[a] represents the number of times an entry
		entered the queue of a.
	      */
	      while(p<=counter[a]){
		l=1;
		while(l<=numm){
		  if((intermediate[l]-sum[l][a][p]) >= 0.0)
		    l++;
		  else
		    l=numm+2;
		}
		if(l==(numm+1))
		  p=(counter[a]+1);
		p++;
	      }

	      /*
		Newvalue shouldn't exceed 1, because then the constraints aren't met.
		The new entrie may also not be dominated (p=counter[a]+1). Then we
		can insert the node. First we keep track of the path by inserting a's
		previous node i and its place in the queue j. We also keep track of the
		sum of the metrics up to node a. Then we insert the node into the fibonacci
		heap and increase the counter.
	      */
	      if((newvalue <=endvalue)&&(p==(counter[a]+1)))
		{
		  if(counter[a]<buffer){
		    p=counter[a]+1;
		    previ[a][p]=i;
		    prevj[a][p]=j;
		    for(l=1; l<=numm; l++){
		      sum[l][a][p]=intermediate[l];
		    }
		    helppo=insert(heap,num,newvalue,a,p);
		    if(counter[a]==0)
		      M[a]=helppo;
		    else if(newvalue > (M[a]->key))
		      M[a]=helppo;
		    counter[a]+=1;
		    N[a][counter[a]]=helppo;
		  }/*if*/
		  else if(newvalue < (M[a]->key)){
		    p=M[a]->el;
		    previ[a][p]=i;
		    prevj[a][p]=j;
		    for(l=1; l<=numm; l++)
		      sum[l][a][p]=intermediate[l];
		    decrease_key(heap,M[a],newvalue);
		    M[a]=selectmaximum(N[a],buffer);
		  }/*else if*/
		  //if((a==END)&&(newvalue<endvalue))
		    //endvalue = newvalue;
		}/*newvalue*/
	    }/*for*/
	}/*else*/
    }/*while*/


  /*for(a=1;a<=pathcounter;a++)
    fprintf(stderr,"%d ",path[a]);
  fprintf(stderr,"\n");*/

  /*minimum queue-size needed to retrieve the shortest path*/
  (*minimum_k) = max_q[END];

  /*queue-size used to calculate the path*/
  for(a=1;a<=aantalnodes;a++){
    if(counter[a]>(*k_used))
      (*k_used) = counter[a];
  }

  /*free memory*/

  for(a=1;a<=aantalnodes;a++){
    if(counter[a]!=0){
      //free(M[a]);
      for(i=1;i<=counter[a];i++)
	free(N[a][i]);
    }
  }

  free_fiblist_matrix(N,1,aantalnodes,1,buffer);
  free_fiblist_vector(M,1,aantalnodes);
  free_fiblist_vector(heap,1,1);
  free_c_d3tensor(sum,1,numm,1,aantalnodes,1,buffer);
  free_c_imatrix(poscounter,1,aantalnodes,1,buffer);
  free_c_imatrix(prevj,1,aantalnodes,1,buffer);
  free_c_imatrix(previ,1,aantalnodes,1,buffer);
  free_c_ivector(max_q,1,aantalnodes);
  free_c_dvector(intermediate,1,numm);
  free_c_ivector(num,1,1);
  free_c_ivector(counter,1,aantalnodes);
}

struct fiblist *selectmaximum(NN,aantalpaden)

struct fiblist **NN;
int aantalpaden;
{
  struct fiblist *z, *ref;
  int i;

  z=NN[1];
  for (i=1; i<=aantalpaden;i++)
    {
      ref=NN[i];
      if(ref->key > z->key)
	z=ref;
    }
  return(z);
}
