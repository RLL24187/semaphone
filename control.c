#include "phone.h"


int main(int argc, char * argv[]){
  if (argc > 1){
    int *data;
    int shmd, semd, v;
    union semun su;
    su.val = 1;
    struct sembuf sb;
    sb.sem_num = 0; //this is the semaphore number you want to use
    //sb.sem_flg = SEM_UNDO;
    sb.sem_op = -1; //downs the semaphore
    if (!strcmp(argv[1], "-c" )){ //create
      // If creating (command line argument: -c):
      // Should make the shared memory, semaphore and file (open the file with the truncate flag).
      // Set any values that are needed.
      // char input[3];
      semd = semget(KEY, 1, IPC_CREAT | IPC_EXCL | 0644);  //excl makes sure it's not created again
      if (semd < 0){ //file already exists
        printf("Error semd create: %s\n", strerror(errno));
        semd = semget(KEY, 1, 0); //the 1 means that you want 1 semaphore
        v = semctl(semd, 0, GETVAL, 0); //gets the value of the semaphore.
        printf("semctl returned: %d\n", v);

      }
      else{ //file didn't exist yet

        v = semctl(semd, 0, SETVAL, su);
        printf("semctl returned: %d\n", v); //value of semaphore
        printf("semaphore created\n");

        shmd = shmget(KEY, sizeof(char *), IPC_CREAT | IPC_EXCL | 0644);
        if (shmd < 0){
          printf("Error shmd: %s\n", strerror(errno));
        }
        printf("shared memory created\n");

        int fd = open("telephone.txt", O_CREAT | O_TRUNC | O_RDWR, 0644);
        if (fd < 0){
          printf("Error in open in create: %s\n", strerror(errno));
        }
        close(fd);
        printf("file 'telephone.txt' created!\n");
      }
      // printf("shmd: %d\n, shmd);
      //
      // data = shmat(shmd, 0, 0);
      //
      // char[200] buffer;
      // fgets(buffer,  200, stdin); //read in the user input
    }
    else if (!strcmp(argv[1], "-r" )){ //remove
      // Remove the shared memory, the semaphore and the story.
      // Display the full contents of the story.
      // This should wait until the semaphore is available.
        printf("trying to get in...\n");
        semd = semget(KEY, 1, 0);
        if (semd < 0){
          printf("Error semget in remove: %s\n", strerror(errno));
        }

        int fd = open("telephone.txt", O_RDONLY); //removing doesn't require WR permissions
        if (fd < 0){
          printf("Error in open in remove: %s\n", strerror(errno));
        }

        printf("The story so far: \n");
        char story[1024];
        read(fd, story, 1024);
        if (strlen(story) != 0){ //try to get rid of seg fault error
          *(strrchr(story, '\n')+ 1) = '\0'; //strrchr returns a pointer to last occurrence of a character, null terminate it
        }
        printf("%s\n", story);
        close(fd);
        // shmdt
        shmctl(shmd,IPC_RMID, 0);
        printf("shared memory deleted\n");
        semctl(semd,IPC_RMID, 0);
        printf("semaphore deleted\n");
        // Detach the segment from a variable (once per process) -- shmdt (shared memory detach)
        // Remove the segment (happens once, not once per process) -- shmctl (shared memory control)
    }
    else if (!strcmp(argv[1], "-v" )){ //view

    }
  }
  return 0;
}
