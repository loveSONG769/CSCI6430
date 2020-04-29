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

#ifndef OPENSHMEM_H
#define OPENSHMEM_H
#define PORT 5555
#define NofBlock 200


struct keySet{
  int keyV[NofBlock];
  int shm_id[NofBlock];
  void* shared[NofBlock];
  int block_num;
};
struct keySet keyset;

void shmem_init(int argc, char* argv[]){
  keyset.block_num=0;
  for(int i=0;i<NofBlock;i++){
    keyset.keyV[i] = i + 1000;
  }

  MPI_Init(&argc, &argv);
}

int shmem_n_pes(){
  int size;
  MPI_Comm_size(MPI_COMM_WORLD,&size);
  return size;
}

int shmem_my_pe(){
  int index;
  MPI_Comm_rank(MPI_COMM_WORLD,&index);
  return index;
}
 
  //shared memory
  char** shared;
  shared = (char**)malloc(n_pes*sizeof(char*));

  name = (char**)malloc(n_pes*sizeof(char*));
  for(int i=0;i<n_pes;i++){
    name[i] = (char *)malloc(NAME_SIZE*sizeof(char));
  }

  for(int i=0;i<my_pe;i++){
    sprintf(name[i],"%d..%d",i,my_pe);
  }
  for(int i=my_pe+1;i<n_pes;i++){
    sprintf(name[i],"%d..%d",my_pe,i);
  }

  //assign the memory for shared space
  
  //assign the memory for name
 
  
  //shared object
  for(int i=my_pe+1;i<n_pes;i++){
    key_t mykey = ftok(name[i],0);
    if(my_key == -1){
    }
    //make shared object for each communication
    int shm_id = shmget(mykey,SHM_SIZE,0666 | IPC_CREAT);
    if(shm_id == -1){
    }

    if(shared[i] == (char *)-1){
    }
    memset(shared[i],0,SHM_SIZE);
  }
    
  shmem_barrier_all();
  

  if(my_pe == 0){ 
    printf("Main process my_pe:%d\n",my_pe);
    for(int i=0;i<n_pes;i++){
     if(i!=my_pe)
       printf("%d ,name[%d] : %s\n",my_pe,i,name[i]);
   }
    int count = 0;
    while(1){
      for(int i=1;i<n_pes; i++){
	if(shared[i][0]==1){
	  printf("Receive from PE: %d, Message:%s\n",i,shared[i][0]+1);
          share[i][0] = 0;
          count++;

	}
      }
      if(count == n_pes - 1) break;
    }
 
    shmdt(shared);
    
  }else{ 
    for(int i=0;i<n_pes;i++){
      if(i != my_pe)
      {
      key_t mykey = ftok(name[0],0);
      if(mykey == -1){
	perror("ftok falied: ");
	return -1;
      }

      if(shared == -1){
	perror("Shared Memory Failed: ");
        return -1;
      }
      if(sharedPE==(char*)-1){
	perror("shmat: ");
        return -1;

	}
   
      shmdt(sharedPE);
    }
   
  }
  
  shmem_barrier_all();
  free(shared);
  free(name);
  shmem_finalize();  
}
