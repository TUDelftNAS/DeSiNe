/* Executor of MF code (for Push-Relabel) */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <values.h>

/* statistic variables */
long n_push  = 0;         /* number of pushes */
long n_rel   = 0;         /* number of relabels */
long n_up    = 0;         /* number of updates */
long n_gap   = 0;         /* number of gaps */
long n_gnode = 0;         /* number of nodes after gap */  

/* definitions of types: node & arc */

#include "types_pr.h"

/* parser for getting extended DIMACS format input and transforming the
   data to the internal representation */

#include "parser_fl.c"

/* function for constructing maximal flow */

#include "h_prf.c"


int maxflow ( char** network, node** ndp, arc** arp, long** cap, double *flow, long *nmin )
{

//arc *a;
node *source, *sink, *i;
long n, m; 
//long ni, na;
int  cc;


//#define N_NODE( i ) ( (i) - *ndp + *nmin )
//#define N_ARC( a )  ( ( a == NULL )? -1 : (a) - *arp )

*flow = 0;

parse( network, &n, &m, ndp, arp, cap, &source, &sink, nmin );

//printf("c nodes:       %10ld\nc arcs:        %10ld\nc\n", n, m);

cc = prflow ( n, *ndp, *arp, *cap, source, sink, flow );

if ( cc ) { fprintf ( stderr, "Allocating error\n"); return 1 ; }

free(queue);
free(layers);
/*    printf ("flow: %.0lf\n", *flow);

    for ( i = *ndp; i < *ndp + n; i ++ )
      {
	ni = N_NODE(i);
	for ( a = i -> first; a != NULL; a = a -> next )
	  {
	    na = N_ARC(a);
	    if ( (*cap)[na] > 0 )
	      printf ( "f %7ld %7ld %12ld\n",
		      ni, N_NODE( a -> head ), (*cap)[na] - ( a -> r_cap )
		      );
	  }
      }
    printf("\n");*/
  
}
