#ifndef _NR_END
#define _NR_END 1

#include <stdlib.h>

int *c_ivector(nl,nh)
long nh,nl;
/* allocate an int vector with subscript range v[nl..nh] */
{
	int *v;

	v=(int *)calloc(nh-nl+1+_NR_END, sizeof(int));
	return v-nl+_NR_END;
}

double *c_dvector(nl,nh)
long nh,nl;
/* allocate a double vector with subscript range v[nl..nh] */
{
	double *v;

	v=(double *)calloc(nh-nl+1+_NR_END, sizeof(double));
	return v-nl+_NR_END;
}

int **c_imatrix(nrl,nrh,ncl,nch)
long nch,ncl,nrh,nrl;
/* allocate a int matrix with subscript range m[nrl..nrh][ncl..nch] */
{
	long i, nrow=nrh-nrl+1,ncol=nch-ncl+1;
	int **m;

	/* allocate pointers to rows */
	m=(int **) calloc(nrow+_NR_END, sizeof(int*));
	m += _NR_END - nrl;

	/* allocate rows and set pointers to them */
	m[nrl]=(int *) calloc(nrow*ncol+_NR_END, sizeof(int));
	m[nrl] += _NR_END - ncl;

	for(i=nrl+1;i<=nrh;i++) m[i]=m[i-1]+ncol;

	/* return pointer to array of pointers to rows */
	return m;
}

double ***c_d3tensor(nrl,nrh,ncl,nch,ndl,ndh)
long nch,ncl,ndh,ndl,nrh,nrl;
/* allocate a double 3tensor with range t[nrl..nrh][ncl..nch][ndl..ndh] */
{
	long i,j,nrow=nrh-nrl+1,ncol=nch-ncl+1,ndep=ndh-ndl+1;
	double ***t;

	/* allocate pointers to pointers to rows */
	t=(double ***) calloc(nrow+_NR_END, sizeof(double**));
	t += _NR_END-nrl;

	/* allocate pointers to rows and set pointers to them */
	t[nrl]=(double **) calloc(nrow*ncol+_NR_END, sizeof(double*));
	t[nrl] += _NR_END - ncl;

	/* allocate rows and set pointers to them */
	t[nrl][ncl]=(double *) calloc(nrow*ncol*ndep+_NR_END, sizeof(double));
	t[nrl][ncl] += _NR_END-ndl;

	for(j=ncl+1;j<=nch;j++) t[nrl][j]=t[nrl][j-1]+ndep;
	for(i=nrl+1;i<=nrh;i++) {
		t[i]=t[i-1]+ncol;
		t[i][ncl]=t[i-1][ncl]+ncol*ndep;
		for(j=ncl+1;j<=nch;j++) t[i][j]=t[i][j-1]+ndep;
	}

	/* return pointer to array of pointers to rows */
	return t;
}

struct el **el_vector(nl,nh)
long nh,nl;
/* allocate an struct el vector with subscript range v[nl..nh] */
{
	struct el **v;
	v=(struct el **)calloc(nh-nl+1+_NR_END, sizeof(struct el*));
	return v-nl+_NR_END;
}

struct fiblist **fiblist_vector(nl,nh)
long nh,nl;
/* allocate an struct fiblist vector with subscript range v[nl..nh] */
{
	struct fiblist **v;
	v=(struct fiblist **)calloc(nh-nl+1+_NR_END, sizeof(struct fiblist*));
	return v-nl+_NR_END;
}

struct fiblist ***fiblist_matrix(nrl,nrh,ncl,nch)
long nch,ncl,nrh,nrl;
/* allocate a fiblist matrix with subscript range m[nrl..nrh][ncl..nch] */
{
	long i, nrow=nrh-nrl+1,ncol=nch-ncl+1;
	struct fiblist ***m;

	/* allocate pointers to rows */
	m=(struct fiblist ***) calloc(nrow+_NR_END, sizeof(struct fiblist **));
	m += _NR_END - nrl;

	/* allocate rows and set pointers to them */
	m[nrl]=(struct fiblist **) calloc(nrow*ncol+_NR_END, sizeof(struct fiblist *));
	m[nrl] += _NR_END - ncl;

	for(i=nrl+1;i<=nrh;i++) m[i]=m[i-1]+ncol;

	return m;
}

struct dynamic_array **dynamic_array_vector(nl,nh)
long nh,nl;
/* allocate an struct dynamic_array vector with subscript range v[nl..nh] */
{
	struct dynamic_array **v;
	v=(struct dynamic_array **)calloc(nh-nl+1+_NR_END, sizeof(struct dynamic_array*));
	return v-nl+_NR_END;
}

struct dynamic_vector ***dynamic_vector_matrix(nrl,nrh,ncl,nch)
long nch,ncl,nrh,nrl;
/* allocate a dynamic_vector matrix with subscript range m[nrl..nrh][ncl..nch] */
{
	long i, nrow=nrh-nrl+1,ncol=nch-ncl+1;
	struct dynamic_vector ***m;

	/* allocate pointers to rows */
	m=(struct dynamic_vector ***) calloc(nrow+_NR_END, sizeof(struct dynamic_vector **));
	m += _NR_END - nrl;

	/* allocate rows and set pointers to them */
	m[nrl]=(struct dynamic_vector **) calloc(nrow*ncol+_NR_END, sizeof(struct dynamic_vector *));
	m[nrl] += _NR_END - ncl;

	for(i=nrl+1;i<=nrh;i++) m[i]=m[i-1]+ncol;

	return m;
}

void free_c_ivector(v,nl,nh)
int *v;
long nh,nl;
/* free an int vector allocated with ivector() */
{
	free((char*) (v+nl-_NR_END));
}

void free_c_dvector(v,nl,nh)
double *v;
long nh,nl;
/* free a double vector allocated with dvector() */
{
	free((char*) (v+nl-_NR_END));
}

void free_c_imatrix(m,nrl,nrh,ncl,nch)
int **m;
long nch,ncl,nrh,nrl;
/* free an int matrix allocated by imatrix() */
{
	free((char*) (m[nrl]+ncl-_NR_END));
	free((char*) (m+nrl-_NR_END));
}

void free_c_d3tensor(t,nrl,nrh,ncl,nch,ndl,ndh)
double ***t;
long nch,ncl,ndh,ndl,nrh,nrl;
/* free a double d3tensor allocated by d3tensor() */
{
	free((char*) (t[nrl][ncl]+ndl-_NR_END));
	free((char*) (t[nrl]+ncl-_NR_END));
	free((char*) (t+nrl-_NR_END));
}

void free_el_vector(v,nl,nh)
long nh,nl;
struct el **v;
/* free a struct el vector allocated with el_vector() */
{
	free((char*) (v+nl-_NR_END));
}

void free_fiblist_vector(v,nl,nh)
long nh,nl;
struct fiblist **v;
/* free a struct fiblist vector allocated with fiblist_vector() */
{
	free((char*) (v+nl-_NR_END));
}

void free_fiblist_matrix(m,nrl,nrh,ncl,nch)
struct fiblist ***m;
long nch,ncl,nrh,nrl;
/* free a struct fiblist matrix allocated by struct fiblist_matrix() */
{
	free((char*) (m[nrl]+ncl-_NR_END));
	free((char*) (m+nrl-_NR_END));
}

void free_dynamic_array_vector(v,nl,nh)
long nh,nl;
struct dynamic_array **v;
/* free a struct dynamic_array vector allocated with dynamic_array_vector() */
{
	free((char*) (v+nl-_NR_END));
}


void free_dynamic_vector_matrix(m,nrl,nrh,ncl,nch)
struct dynamic_vector ***m;
long nch,ncl,nrh,nrl;
/* free a struct dynamic_vector matrix allocated by struct dynamic_vector_matrix() */
{
	free((char*) (m[nrl]+ncl-_NR_END));
	free((char*) (m+nrl-_NR_END));
}


#undef _NR_END
#endif //SAMCRA_UTIL_H
