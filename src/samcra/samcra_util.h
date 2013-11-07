// Inclusion guards
#ifndef SAMCRA_UTIL_H
#define SAMCRA_UTIL_H
//  end inclusion guards
#ifndef NULL
#define NULL 0
#endif
#ifndef INF
#define INF 9.9e99
#endif
#ifndef POWER
#define POWER 10
#endif

struct fiblist {	  /*global definition of the type fiblist*/
  double key;
  int    id;
  int    el;
  int    degree;
  int    mark;
  struct fiblist *parent;
  struct fiblist *child;
  struct fiblist *left;
  struct fiblist *right;
};

// ---------------  structs  ---------------------------

struct el{
  struct fiblist *list;
  int index;
  struct el *next;
};

struct dynamic_array{
  int data1;
 int index1;
  struct dynamic_array *next1;
};

struct dynamic_vector{
  double data2;
  int index2;
  struct dynamic_vector *next2;
};

// ---------------  alloc's  ---------------------------
int *c_ivector();
int **c_imatrix();
double *c_dvector();
double ***c_d3tensor();
struct fiblist **fiblist_vector();
struct fiblist ***fiblist_matrix();
struct el **el_vector();
struct dynamic_array **dynamic_array_vector();
struct dynamic_vector ***dynamic_vector_matrix();

void free_c_ivector();
void free_c_imatrix();
void free_c_dvector();
void free_c_d3tensor();
void free_fiblist_vector();
void free_fiblist_matrix();
void free_el_vector();
void free_dynamic_array_vector();
void free_dynamic_vector_matrix();
#endif //SAMCRA_UTIL_H
