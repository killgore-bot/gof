#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <errno.h>
#include <mpi.h>

int create(int size,int **matrix,int world_rank,int world_size, int mem );
//int display(int size, int **matrix);
int countNeighbor(int size,int **matrix, int **temp, int steps, int world_rank,
int mem,int world_size,int argc, char* argv[]);
int main( int argc, char* argv[])
{
int size, **matrix, **temp, world_rank, world_size, mem;
size=atoi (argv[1]);
int steps=atoi (argv[2]);
matrix = (int**)malloc((size + 2) * sizeof(int*));
temp= (int**)malloc((size + 2) * sizeof(int*));

int z;
for (z = 0;z<size + 2;z++){
matrix[z] = (int*)malloc((size + 2) * sizeof(int));
temp[z] = (int*)malloc((size + 2) * sizeof(int));
	}
  clock_t start = clock();
**matrix = create(size,matrix,world_rank,world_size,mem);

MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
MPI_Comm_rank(MPI_COMM_WORLD, &world_size);

mem = ((size)/world_size);
**matrix == countNeighbor(size,matrix,temp,steps,world_rank,mem,world_size,argc,argv);

//display(size, matrix);
clock_t stop = clock();
double time_taken = (double)(stop - start) / CLOCKS_PER_SEC;
printf("\n Time elapsed : %f s ", time_taken);
//printf("from processor %s, rank %d, no.of processors %d",processor_name,
//world_rank,world_size")
return 0;
}
//int create(int size, int **matrix)
int create(int size,int **matrix,int world_rank,int world_size, int mem)
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
//int countNeighbor(int size, int **matrix, int **temp,)
int countNeighbor(int size,int **matrix, int **temp, int steps, int world_rank,
int mem,int world_size,int argc, char* argv[])
{
  //while (1){

MPI_Init(&argc, &argv);
MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
MPI_Comm_size(MPI_COMM_WORLD, &world_size);

mem = ((size)/ world_size);

  int i,j,k;
  for(k =0; k<steps; k++)
  {
for( i=1;i<size+1;i++)
        {
		for( j=1;j<size+1;j++)

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
if (world_size > 1)
{
//MPI_Request request;
if ( world_rank != 0 && world_rank != world_size -1)
{
  MPI_Ssend(&matrix[0][0],1,MPI_INT,world_rank-1,1,MPI_COMM_WORLD);

  MPI_Ssend(&matrix[mem -1][0],1,MPI_INT,world_rank + 1,0,MPI_COMM_WORLD);

  MPI_Recv(&matrix[mem-1][0], world_size, MPI_INT, world_rank + 1, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

  MPI_Recv(&matrix[0][0], world_size, MPI_INT, world_rank - 1, 0, MPI_COMM_WORLD,MPI_STATUS_IGNORE);
}

else if (world_rank = world_size -1)
{
  MPI_Ssend(&matrix[0][0], 1, MPI_INT, world_rank - 1, 1, MPI_COMM_WORLD);

  MPI_Recv(&matrix[0][0], world_size, MPI_INT, world_rank - 1, 0, MPI_COMM_WORLD,MPI_STATUS_IGNORE);

}

else
{

MPI_Ssend(&matrix[mem-1][0], 1, MPI_INT, world_rank + 1, 0, MPI_COMM_WORLD);

MPI_Recv(&matrix[mem -1][0], world_size, MPI_INT, world_rank + 1, 1, MPI_COMM_WORLD,MPI_STATUS_IGNORE);
}

}

MPI_Barrier (MPI_COMM_WORLD);

int m,n;
	for( m=0; m<mem ;m++)
        {
		for( n=0;n<size+2;n++)
            {
            matrix[m][n]=temp[m][n];
            }
        }
        MPI_Finalize();
return **matrix;
}
}
