#include "phone.h"

// Will attempt to access the resources using the semaphore
// Once in, it should display the last line added to the file (use shared memory to contain the size of the last line).
// Prompt the user for the next line.
// Once a new line is read, write that to the file, update the shared memory and then release the semaphore
int main(){
  int shmd, semd;
  struct sembuf sb;
  sb.sem_num = 0;
  sb.sem_op = -1;
  printf("trying to get in...\n");
  semd = semget(KEY, 1, 0);
  if (semd < 0){
    printf("Error in semget in write.c: %s\n", strerror(errno));
    return 1; //should not continue if the user hasn't created anything yet
  }
  semop(semd, &sb, 1); //down the semaphore
  shmd = shmget(KEY, sizeof(char *), 0);
  if (shmd < 0){
    printf("Error in shmget in write.c: %s\n", strerror(errno));
    return 1;
  }

  int fd = open("telephone.txt", O_WRONLY | O_APPEND);
  if (fd < 0){
    printf("Error in open in write.c: \n", strerror(errno));
    return 1;
  }
  char *lastline = shmat(shmd, 0, 0); //attach shared memory to an available address (contain size of last line)
  printf("last addition: %s\n", lastline);
  char input[1024];
  printf("your new addition: ");
  fgets(input, 1024, stdin);
  write(fd, input, strlen(input));
  shmdt(input); //detach the segment
  close(fd);
  strcpy(lastline, input); //last line is updated to what input was
  printf("thank you for your addition. it has been added!\n");
  sb.sem_op = 1; //done using the resourse, so we have to up the semaphore
  semop(semd, &sb, 1); //ups the semaphore
  return 0;
}
