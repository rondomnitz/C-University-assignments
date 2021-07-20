#include "adjacency.h"
/* decleration of function for tha main*/
int path(adjmat mat, int, int);
void fillMatrix(adjmat);
void printMatrix(adjmat);

int main()
{
   int u,v;
   adjmat matrix;
   fillMatrix(matrix); /*Call to the function 'fillMatrix' below*/
   printMatrix(matrix); /*Call to the function 'printMatrix' below*/
   while((scanf("%d",&u) != EOF) && (scanf("%d",&v) != EOF) && (u != -1 && v != -1))
   {
      int res;
      printf("\n Please insert 2 index of the tree for checking relation:\n");
      printf("Your u is: %d \n", u); 
      printf("Your v is: %d \n", v);
      if(u==-1 && v==-1)
	  printf("End Path functin. GoodBye");
      res=path(matrix,u,v);
      if(res)
	  printf("\nTRUE!\n");
      else 
          printf("\nFALSE!\n");
   }
return 0;
} 
/*function of calculate if u is a father or an ancestor of v return "TRUE" or "FALSE"*/
int path(adjmat mat, int u, int v) /*u= father; v=son*/
{
   int i;
   int root=TRUE;
   int father;
   if(u>N || v>N) /*out of range*/
      return FALSE;
   if(u==v) /*if indexs are equalse*/
      return TRUE;
   if(mat[u][v])
      return TRUE; /* if mat[u][v] it means that u is the father of v */
 
   for(i=0; i<N; i++)
   {
	if(mat[i][v])
	{
           root=FALSE;			
           father=i;            
        }
   }	
   if(root) /* if we got to the root and still didn't find a father*/
      return FALSE;

   return path(mat,u,father); /* reqursion step, we will try to find an ancestor*/	        
}


void fillMatrix(adjmat matrix) 
/* This function  fill values in the Matrix*/
{
  int i,j;
  printf("Welcom. Please insert %d values (0 or 1) for the %d*%d matrix that defines the tree:\n", N*N,N,N);    
     for(i=0;i<N;i++)
       	for(j=0;j<N;j++)
        	scanf("%d", &matrix[i][j]);
}
void printMatrix(adjmat matrix) 
/*This function print the Matrix*/
{
   int i,j;
   printf("\n The matrix you inserted is:\n");
   for(i=0;i<N;i++)
   {
	for(j=0;j<N;j++) 	
         {
		printf("%d", matrix[i][j]);
                printf("\t");                  
         }  
   printf("\n");
   } 
}
