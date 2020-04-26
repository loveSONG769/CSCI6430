#include<shmem.h>
#include<fcntl.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/mman.h>
#include<sys/time.h>
#include<sys/stat.h>
#include<sys/types.h>

#define SHM_SIZE 1024
#define NAME_SIZE 255

int main(){
  shmem_init();

  int my_pe, n_pes;
  my_pe = shmem_my_pe();
  n_pes = shmem_n_pes();


  //name vector
  char** name;
  
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
   for(int i=0;i<n_pes;i++){
    int count = 0;
    while(1){
      for(int i=1;i<n_pes; i++){
	if(shared[i][0]==1){
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
      }

      if(shared == -1){
      }
      if(sharedPE==(char*)-1){
	}
   
      shmdt(sharedPE);
    }
   
  }
  
  shmem_barrier_all();
  free(shared);
  free(name);
  shmem_finalize();  
}