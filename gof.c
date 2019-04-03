#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int create(int size,int **matrix);
int display(int size, int **matrix);
int countNeighbor(int size,int **matrix, int **temp);
int main( int argc, char* argv[])
{
int size, **matrix, **temp;
size=atoi (argv[1]);
int steps=atoi (argv[2]);
matrix = (int**)malloc((size + 2) * sizeof(int*));
temp= (int**)malloc((size + 2) * sizeof(int*));
clock_t start = clock();
int z;
for (z = 0;z<size + 2;z++){
matrix[z] = (int*)malloc((size + 2) * sizeof(int));
temp[z] = (int*)malloc((size + 2) * sizeof(int));
	}
**matrix = create(size,matrix);
for (z = 0; z<steps; z++)
{
**matrix = countNeighbor(size,matrix,temp);
}
display(size, matrix);
clock_t stop = clock();
double time_taken = (double)(stop - start) * 1000.0 / CLOCKS_PER_SEC;
printf("\n Time elapsed in ms: %f", time_taken);
return 0;
}
int create(int size, int **matrix)
{
int a,b;
for( a=1;a<=size;a++){
for( b=1;b<=size;b++){
matrix[a][b]=rand()%2;
int x,y;
for ( x = 0; x<=size+1;x++)
{
  for( y = 0; y <= size+1; y++)
  {
    if( x == 0 || y == 0)
    {
      matrix[x][y] = 0;
    }
    if(x == size+1 || y == size +1)
    {
      matrix[x][y] = 0;
    }
  }
}

}
	}
return **matrix;
}
int display(int size,int **matrix)
{
  int c,d;
for ( c =0; c<size+2;c++)
      {
        for( d = 0;d<size+2;d++)
        {
          printf("%d",matrix[c][d]);
        }
        printf("\n");
      }
return 0;
}
int countNeighbor(int size, int **matrix, int **temp)
{
  //while (1){
  int i,j;
for( i=1;i<size;i++)
        {
		for( j=1;j<size;j++)

            {
int count = 0;
if(matrix[i-1][j]==1){
count+=1;
}
if(matrix[i-1][j-1]==1){
		count+=1;}
if(matrix[i-1][j+1]==1){
		count+=1;
  }
  if(matrix[i+1][j]==1){
				count+=1;
}
if(matrix[i+1][j+1]==1){
	count+=1;
}
if(matrix[i+1][j-1]==1){
				count+=1;
}
if(matrix[i][j-1]==1){
				count+=1;
}
if(matrix[i][j+1]==1){
	count+=1;
}
if(count < 2||count >3)
                    {
                    temp[i][j]=0;
                    }
                if(count ==2)
                    {
                    temp[i][j]=matrix[i][j];
				    }
				if(count ==3)
					{
					temp[i][j]=1;
					}
}
	}
//}
int m,n;
	for( m=0;m<size+2;m++)
        {
		for( n=0;n<size+2;n++)
            {
            matrix[m][n]=temp[m][n];
            }
        }
return **matrix;
}
