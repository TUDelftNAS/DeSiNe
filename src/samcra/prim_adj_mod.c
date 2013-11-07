
 /*This module calculates the minimum spannings tree in a graph where the links are characterised by a single metric.
 The value of the metric is expressed by a double.


 INPUT: topology as a matrix of doubles
	number of nodes in the graph
	ROOT: starting node
 RETURN:minimum spannings tree as array of vertices with their ancestors

Hans De Neve, 10/09/97

 */

#include <string.h>
#include <stdio.h>
#include <math.h>
#include "samcra_util.h"

void Prim_adj(adj,numadj,datadj,aantalnodes,primlist,connected,treevalue)

int **adj, *numadj;
double ***datadj;
int aantalnodes;
int *primlist,*connected;
double *treevalue;

{

int i,j,m,*num, *label;
struct fiblist *helppo, **heap, **M ;

void create_heap();  			/*declaration of the functions maintaining the Fibonacci heap*/
struct fiblist *insert();
struct fiblist *extract_min_from_list();
void consolidate();
void decrease_key();
void cut();
void cascading_cut();

/* geheugenallocatie*/

num = c_ivector(1,1);
label = c_ivector(1,aantalnodes);

//heap=(struct fiblist**) malloc(sizeof(int));  /*geheugenallocatie voor pointer*/
heap = fiblist_vector(1,1);
//M=(struct fiblist**) malloc((size_t) (aantalnodes+1)*sizeof(int));
M = fiblist_vector(1,aantalnodes);

/* initialisatie*/


create_heap(heap,num);

for(i=1; i<=aantalnodes; i++)
	{
	M[i]=insert(heap,num,INF,i,1);	  	/*the one is optional*/
	label[i]=0;
	}
decrease_key(heap,M[1],0.0);
primlist[1]=0;
(*treevalue)=0.0;
(*connected)=1;

/*main algorithm*/

helppo=extract_min_from_list(heap,num);      /*selectminimum(pixel)*/
while(helppo!=NULL)
	{
	i=helppo->id;
	(*treevalue)+=helppo->key;
	label[i]=1;
	for(j=1; j<=numadj[i]; j++)
		{
		if(label[adj[i][j]]==0)
			{
			if (datadj[1][i][j] < M[adj[i][j]]->key)    	/*condensatievoorwaarde*/
				{
				decrease_key(heap,M[adj[i][j]],datadj[1][i][j]);
				primlist[adj[i][j]]=i;
				}
			}
		}
	helppo=extract_min_from_list(heap,num);
	}

if((*treevalue)>=INF)
(*connected)=0;

/*vrijmaken van geheugen*/
for(i=1;i<=aantalnodes;i++)
free(M[i]);
free_c_ivector(num,1,1);
free_c_ivector(label,1,aantalnodes);
free_fiblist_vector(heap,1,1);
free_fiblist_vector(M,1,aantalnodes);

}


