#include<cstdlib>
#include<iostream>
#include<cmath>
#include<stdio.h>
#include<time.h>
#include<limits.h>

typedefunsignedint uint;

// matrix dimension
uint matrixDim = 1<<14;

// allocating memory in CPU
void memoryAllocation(float *&A,float *&x,float *&y,
		uint m , uint n)
{
	A = (float*)malloc(m*n*sizeof(float));
	x = (float*)malloc(n*sizeof(float));
	y = (float*)malloc(m*sizeof(float));
}

//fill matrix from a file
void fillMatrix_file(float *&A,float *&x,float *&y,
		uint&m,char*fname)
{
	FILE* in = fopen(fname, "r");
	fscanf(in, "%d\n",&m);

	// symetric squar matrix ,m=row ,n=col
	uint n = m;
	memoryAllocation(A, x, y,m,n);

	uint i,j;
	for (i = 0; i < m; ++i) {
		for (j=0; j < n; ++j) {
			fscanf(in,"%f",&A[i*n+j]);
		}
		fscanf(in, "%f\n",&A[i*n+n-1]);
	}
	fclose(in);
	for (i=0; i<n; ++i) {
		x[i]=1;
	}

}

//fill matrix with random arrays
void fillMatrix_random(float *&A, float *&x,float *&y, uint &m)
{
	uint n = m = matrixDim;
	memoryAllocation(A, x, y, m, n);
	uint i,j;
	//row major order
	for (i=0; i<m; ++i) 
		for (j=0; j<n; ++j) 
			A[i*n+j]= 10 * (double) rand()/(INT_MAX + 1.0f);

	// initial vector V_0
	for (i=0; i<n; ++i) 
		x[i]=1;

}


// creat a symetrix Tridiagonal matrix 
void fillMatrix_symetrixTridiagonalMatrix( float *&A, float *&x, float *&y, uint &m)
{
	uint n=m=matrixDim;
	float d_0 = 1.0 ,d_1 = 0.5;
	memoryAllocation(A, x, y, m, n);
	uint i , j;
	// row major order
	for (i=0; i<m; ++i) {
		if (i ==j) 
			A[i*n+ j] = d_0;
		elseif (i ==j+1)
			A[i*n+j]=d_1;
		elseif (i+1 == j)
			A[i*n+j]=d_1;
		else
			A[i*n+j]=0;
	
	}
	
	//initial vector V_0
	for (i=0; i<n; ++i) {
		x[i]=1;
	}
		
}

// calculating the largest eigenvalue and its eigen vector 
void PowerMethodC ( float *A , float *x,float *y,float&l, uint &nIter,
		uint m ,uint n)
{
	uint maxNumMethodIteration = 64;
	uint i,j,k,ii;

	for ( ii = 0; ii<maxNumMethodIteration ; ++ii) {

		printf("iter# %d lamda: %f \n", ii, l);

		for (k=0; k<n; k++) {
			y[k] = 0 ;
		}

		for (i=0; i< m; ++i) {
			for (j=0; j<n; ++j) {
				y[i]+= x[i]*A[i*n+j];
			}
		}

		// calculating norm
		l=0;
		for (k=0; k<n; k++) {
			l += y[k]*y[k];
		}

		l = sqrt(l);

		for (k=0; k<n; k++) {
			x[k] = y[k]/l ;
		}

	}
	// l is the norm

	nIter = ii + 1;
}


// initialization
void init(float *&A, float *&x, float *&y, uint &m)
{
	fillMatrix_symetrixTridiagonalMatrix(A,x,y,m);

	//fillMatrix_random(A,x,y,m);	
}

int main () {

	//int matrixDim;
	//cin >> matrixDim;
	uint m,n, nIter=0 ;
	float *A, *x, *y, lambda_1=0;
	init (A, x, y, m);
	n = m;
	PowerMethodC(A,x,y, lambda_1, nIter ,m , n);
	printf("nIters : %d ,MatrixDim : %d, Lambda : %f, \n"
			,nIter,matrixDim,lambda_1);



	return 0;
}

