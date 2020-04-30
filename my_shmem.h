#include <mpi.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/shm.h>
#include<fcntl.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/mman.h>
#include<sys/time.h>
#include<sys/stat.h>
#include<sys/types.h>



#define NofBlock 200


struct keys
{
  int shmemIndex[NofBlock];
  
  int key[NofBlock];
  int blockIndex;
  void* sharedMem[NofBlock];
  
};

struct keys keys;




void shmem_init(int argc, char* argv[])
{
  keys.blockIndex=0;
  for(int i=0;i<NofBlock;i++)
    {
    keys.key[i] = i+100;
  }
  MPI_Init(&argc, &argv);
}


void shmem_finalize()
{
  for(int i=0;i<keys.blockIndex;i++)
    {
    shmdt(keys.sharedMem[i]);
    shmctl(keys.shmemIndex[i],IPC_RMID,NULL);
  }
  MPI_Finalize();
}


int shmem_n_pes()
{
  int size;
  MPI_Comm_size(MPI_COMM_WORLD,&size);
  return size;
}

int shmem_my_pe()
{
  int index;
  MPI_Comm_rank(MPI_COMM_WORLD,&index);
  return index;
}



void* shmem_malloc(size_t size)
{
  
  keys.blockIndex++;
  key_t intKey=keys.key[keys.blockIndex];
  

  keys.shmemIndex[keys.blockIndex] = shmget(intKey, shmem_n_pes()*size, 0666|IPC_CREAT);
  
  if(keys.shmemIndex[keys.blockIndex]==-1)
    {
    perror("share memory failed:");
    return NULL;
  }

  keys.sharedMem[keys.blockIndex] = malloc(shmem_n_pes()*size);
  keys.sharedMem[keys.blockIndex] = shmat(keys.shmemIndex[keys.blockIndex], NULL, 0);

  
  return (keys.sharedMem[keys.blockIndex] + shmem_my_pe()*size);
}


void shmem_int_get(int* target, int* source, int length, int pe)
{  
  if(shmem_my_pe()==pe)
    {
    if(length==1)
      {
      *target=*source;
    }
    else
      {
      for(int i=0;i<length;i++)
	{
	*(target+i)=*(source+i);
      }
    }
  }
  else
    {
    
    if(length==1)
      {
      *target=*(source+pe-shmem_my_pe());
    }
    else
      {
      for(int i=0;i<length;i++)
	{
	*(target+i)=*(source+i);
      }
    }
  }

}

void shmem_int_put(int* source, int* target, int length, int pe)
{  
  if(shmem_my_pe()==pe)
    {
    if(length==1)
      {
      *source = *target;
    }
    else
      {
      for(int i=0;i<length;i++)
	{
	*(source+i)=*(target+i);
      }
    }
  }
  else
    {
    if(length == 1)
      {
      *(source+(pe-shmem_my_pe()))=*target;
    }
    else
      {
      for(int i=0;i<length;i++)
	{
	*(source+i)=*(target+i);
      }
    }
  }
}


void shmem_quiet(void)
{
  int i;


}




