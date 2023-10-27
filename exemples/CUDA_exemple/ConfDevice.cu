#include <stdio.h> 

int main() {

  FILE * inputFile = fopen("/users/imr/rheritea/Documents/Processeur_multimedia/parallelisation_processeur/gpuinfo_barn-e-01", "w");
  if ( inputFile == NULL ) {
    fprintf( stderr, "Cannot open file \n");
    exit( 0 );
  }

  int nDevices;

  cudaGetDeviceCount(&nDevices);
  for (int i = 0; i < nDevices; i++) {
    cudaDeviceProp prop;
    cudaGetDeviceProperties(&prop, i);
    fprintf( inputFile, "Device Number: %d\n", i);
    fprintf( inputFile, "  Device name: %s\n", prop.name);
    fprintf( inputFile, "  Memory Clock Rate (KHz): %d\n",
           prop.memoryClockRate);
    fprintf( inputFile, "  Global Memory (bytes): %ld\n",
           prop.totalGlobalMem);
    fprintf( inputFile, "  Memory Bus Width (bits): %d\n",
           prop.memoryBusWidth);
    fprintf( inputFile, "  Peak Memory Bandwidth (GB/s): %f\n",
           2.0*prop.memoryClockRate*(prop.memoryBusWidth/8)/1.0e6);
    fprintf( inputFile, "   Max Thread per block : %d \n",prop.maxThreadsPerBlock);
    fprintf( inputFile, "   Multiproc count : %d \n",prop.multiProcessorCount);
    fprintf( inputFile, "   Max Grid size : %d %d %d \n",prop.maxGridSize[0], prop.maxGridSize[1], prop.maxGridSize[2]);
    fprintf( inputFile, "   Max thread dim : %d %d %d \n",prop.maxThreadsDim[0], prop.maxThreadsDim[1], prop.maxThreadsDim[2]);
    fprintf( inputFile, "   Registres per block : %d \n",prop.regsPerBlock);
    fprintf( inputFile, "\n");
  }
} 
