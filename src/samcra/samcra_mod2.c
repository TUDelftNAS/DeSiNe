/*
samcra_mod.c
This modules calculates the samcra-path between a source and destination node
F.A. Kuipers 22/09/2000
*/


#include <string.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include "samcra_util.h"
#include "linked_list.h"

void samcrapath2(START,END,adj,max,datadj,numm,A,aantalnodes,path,hopcount,minimum_k,k_used)

int START;
int END;
int **adj;
int *max;
double ***datadj;
int numm;
int aantalnodes;
double *A;
int *path;
int *hopcount;
int *minimum_k;
int *k_used;

{
  int countdown,entries,mark;
  int i,j,l,m,n,k,a,u,v,q,r,s,p,*counter,num,pathcounter,*max_q;
  double ref, newvalue, *intermediate, endvalue;
  struct dynamic_array **previ, **prevj, **poscounter,**marked;
  struct dynamic_vector ***sum;
  struct fiblist *helppo, *heap,*po;
  struct el **N;

  /*declaration of the functions maintaining the Fibonacci heap, see Cormen for implementing and maintaining Fibonacci heaps*/
  void create_heap();
  struct fiblist *extract_min_from_list();
  struct fiblist *insert();
  void consolidate();
  void decrease_key();
  void cut();
  void cascading_cut();
  void putlist();
  void delete_list();
  void insertlist();
  struct fiblist *getlist();


  /*memory allocation*/
  counter = c_ivector(1,aantalnodes);
  intermediate = c_dvector(1,numm);
  max_q = c_ivector(1,aantalnodes);
  previ = dynamic_array_vector(1,aantalnodes);      //previous node in the path
  prevj = dynamic_array_vector(1,aantalnodes);      //index of previous node
  poscounter = dynamic_array_vector(1,aantalnodes);
  marked = dynamic_array_vector(1,aantalnodes);
  N = el_vector(1,aantalnodes);
  sum = dynamic_vector_matrix(1,numm,1,aantalnodes);  //keeps track of the sum of the linkmetrics on the path

  create_heap(&heap,&num);
  helppo=insert(&heap,&num,0.0,START,1);
  insertlist(&N[START],0,helppo);
  counter[START]+=1;
  for(l=1; l<=numm; l++){
    insertdatad(&sum[l][START],0,0.0);
  }

  k=0;
  countdown=0;  /*because only N-1 connections are measured, but in this case also END is taken into account*/
  pathcounter=0;
  entries=0;
  endvalue = 1.0;
  (*hopcount)=0;
  (*minimum_k)=0;
  (*k_used) = 0;

  for(i=1;i<=aantalnodes;i++)
    for(j=1;j<=length_array(poscounter[i]);j++)
      insertdata(&poscounter[i],j-1,0);

  /*main algorithm*/

  while(countdown < 1)
    {
      /*
	Select the minimum element from the Fibonacci list
      */
      helppo=extract_min_from_list(&heap,&num);

      if(helppo==NULL)
	{
	  countdown=1;
	}
      else
	{
	  i=helppo->id; /*i represents the extracted node from the fib heap*/
	  j=helppo->el;

	  if(i==START)
	    q=1;
	  else{
	    q=getdata(poscounter[getdata(previ[i],j-1)],(getdata(prevj[i],j-1)-1));
	  }
	  for(s=1;s<=length_array(poscounter[i]);s++){
	    if(getdata(poscounter[i],s-1)==q){
	      q++;
	      s=0;
	    }/*if*/
	  }/*for*/
	  insertdata(&poscounter[i],j-1,q);
	  max_q[i]=q;

	  if(i==END){
	    countdown++;
	    pathcounter=1;
	    u=i;
	    v=j;
	    while(u!=START){
	      path[pathcounter++]=u;
	      s=u;
	      u = getdata(previ[u],v-1);
	      v = getdata(prevj[s],v-1);
	    }
	    path[pathcounter]=u;
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
		  intermediate[l]=(getdatad(sum[l][i],j-1)+datadj[l][i][m]);
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
		mark=1;
		while(mark<=numm){
		  if((getdatad(sum[mark][a],p-1)-intermediate[mark]) >= 0.0){
		    mark++;
		  }
		  else
		    mark=numm+2;
		}
		l=1;
		while(l<=numm){
		  if((getdatad(sum[l][a],p-1)/A[l])>endvalue)
		    mark=numm+1;
		  l++;
		}
		if(mark==(numm+1))
		  insertdata(&marked[a],p-1,1);
		p++;
	      }
	      p=1;

	      while(p<=counter[a]){
		l=1;
		while(l<=numm){
		  if((intermediate[l]-getdatad(sum[l][a],p-1)) >= 0.0)
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
		  for(p=1;p<=counter[a];p++){
		    if(getdata(marked[a],p-1)==1){
		      if(newvalue<=getlist(N[a],p-1)->key){
			insertdata(&previ[a],p-1,i);
			insertdata(&prevj[a],p-1,j);
			for(l=1; l<=numm; l++){
			  insertdatad(&sum[l][a],p-1,intermediate[l]);
			}
			decrease_key(&heap,getlist(N[a],p-1),newvalue);
			insertdata(&marked[a],p-1,0);
			p=counter[a]+2;
		      }
		    }
		  }

		  if(p==counter[a]+1){
		    insertdata(&previ[a],p-1,i);
		    insertdata(&prevj[a],p-1,j);
		    for(l=1; l<=numm; l++){
		      insertdatad(&sum[l][a],p-1,intermediate[l]);
		    }
		    helppo=insert(&heap,&num,newvalue,a,p);
		    counter[a]+=1;
		    insertlist(&N[a],counter[a]-1,helppo);
		  }
		  if((a==END)&&(newvalue<endvalue))
		    endvalue = newvalue;
		}/*newvalue*/
	    }/*for*/
	}/*else*/
    }/*while*/

  /*number of hops taken by the path as calculated by samcra = pathcounter*/
  (*hopcount) = pathcounter;

  /*minimum queue-size needed to retrieve the shortest path*/
  (*minimum_k) = max_q[END];

  /*queue-size used to calculate the path*/
  for(a=1;a<=aantalnodes;a++){
    if(counter[a]>(*k_used))
      (*k_used) = counter[a];
  }

  /*free memory*/

  for(a=1;a<=aantalnodes;a++){
    delete_list(&N[a]);
  }

  for(a=1;a<=aantalnodes;a++){
    delete_array(&previ[a]);
    delete_array(&prevj[a]);
    delete_array(&poscounter[a]);
    delete_array(&marked[a]);
  }

  for(a=1;a<=numm;a++){
    for(i=1;i<=aantalnodes;i++){
      delete_vector(&sum[a][i]);
    }
  }

  free_dynamic_vector_matrix(sum,1,numm,1,aantalnodes);
  free_el_vector(N,1,aantalnodes);
  free_dynamic_array_vector(marked,1,aantalnodes);
  free_dynamic_array_vector(poscounter,1,aantalnodes);
  free_dynamic_array_vector(prevj,1,aantalnodes);
  free_dynamic_array_vector(previ,1,aantalnodes);
  free_c_ivector(max_q,1,aantalnodes);
  free_c_dvector(intermediate,1,numm);
  free_c_ivector(counter,1,aantalnodes);
}
