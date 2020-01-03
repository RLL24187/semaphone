#include "phone.h"

int main(){
  int shmd, semd;
  struct sembuf sb;
  sb.sem_num = 0;
  sb.sem_op = -1;
  printf("trying to get in...\n");
  semd = semget(KEY, 1, 0);
  if (semd < 0){
    printf("Error in write.c semget: %s\n", strerror(errno));
  }
  semop(semd, &sb, 1); //down the semaphore
  shmd = shmget(KEY, sizeof(char *), 0);
  if (shmd < 0){
    printf("Error in write.c shmget: %s\n", strerror(errno));
  }
  
  return 0;
}
