// Rohit Khiani
// id - khianirm
// CS-632
// hw-5

#include <stdio.h>
#include <stdlib.h>

#define BLOCK_SIZE 16


__global__ void rules(int size, int *simulation, int *newsimulation)
{
    // We want id ∈ [1,size]
    int d_row = blockDim.y * blockIdx.y + threadIdx.y + 1;
    int d_col = blockDim.x * blockIdx.x + threadIdx.x + 1;
    int id = d_row * (size+2) + d_col;

    int count;

    if (d_row <= size && d_col <= size) {

        // Get the number of neighbors for a given simulation point
        count = simulation[id+(size+2)] + simulation[id-(size+2)] //upper lower
                     + simulation[id+1] + simulation[id-1]             //right left
                     + simulation[id+(size+3)] + simulation[id-(size+3)] //diagonals
                     + simulation[id-(size+1)] + simulation[id+(size+1)];

        int cell = simulation[id];
        // Here we have explicitly all of the game rules
        if (cell == 1 && count < 2)
            newsimulation[id] = 0;
        else if (cell == 1 && (count == 2 || count == 3))
            newsimulation[id] = 1;
        else if (cell == 1 && count > 3)
            newsimulation[id] = 0;
        else if (cell == 0 && count == 3)
            newsimulation[id] = 1;
        else
            newsimulation[id] = cell;
    }
}

void errorCheck()
{
  cudaError_t error = cudaGetLastError();
  if(error != cudaSuccess)
  {
    // print the CUDA error message and exit
    printf("CUDA error: %s\n", cudaGetErrorString(error));
    exit(-1);
  }
}

int main(int argc, char* argv[])
{
    int i,j;
    int* matrix;
    int* d_matrix;
    int* t_matrix;
    int* d_tmpsimulation;
    int size = 4999;
    int maxIter = 1<<12;

    int N = sizeof(int)*(size+2)*(size+2);
    matrix = (int*)malloc(N);


    cudaMalloc(&d_matrix, N);
    cudaMalloc(&t_matrix, N);


    for(i = 0; i<=size+1; i++) {
        for(j = 0; j<=size+1; j++) {
          if (i == 0 || j == size ){
              matrix[i*(size+2)+j] = 0;
          }
          else if (i == size || j== size){
              matrix[i*(size+2)+j] = 0;
          }
            else matrix[i*(size+2)+j] = rand() % 2;
        }
    }


    cudaMemcpy(d_matrix, matrix, N, cudaMemcpyHostToDevice);

    dim3 blockSize(BLOCK_SIZE, BLOCK_SIZE,1);
    int linsimulation = (int)ceil(size/(float)BLOCK_SIZE);
    dim3 simulationSize(linsimulation,linsimulation,1);

    dim3 cpyBlockSize(BLOCK_SIZE,1,1);
    dim3 cpysimulationRowssimulationSize((int)ceil(size/(float)cpyBlockSize.x),1,1);
    dim3 cpysimulationColssimulationSize((int)ceil((size+2)/(float)cpyBlockSize.x),1,1);

    errorCheck();

    for (i = 0; i<maxIter; i++) {
        rules<<<simulationSize, blockSize>>>(size, d_matrix, t_matrix);

        d_tmpsimulation = d_matrix;
        d_matrix = t_matrix;
        t_matrix = d_tmpsimulation;
    }

    for (i = 4096; i< 5000; i++) {


        rules<<<simulationSize, blockSize>>>(size, d_matrix, t_matrix);


        d_tmpsimulation = d_matrix;
        d_matrix = t_matrix;
        t_matrix = d_tmpsimulation;
    }


    cudaMemcpy(matrix, d_matrix, N, cudaMemcpyDeviceToHost);


    for (i = 0; i<=size+1; i++) {
        for (j = 0; j<=size+1; j++) {
            printf("%d",matrix[i*(size+2) + j]);
        }
        printf("\n");
    }



    cudaFree(d_matrix);
    cudaFree(t_matrix);
    free(matrix);

    return 0;
}
