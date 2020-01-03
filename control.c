#include "phone.h"


int main(int argc, char * argv[]){
  if (argc > 1){
    if (!strcmp(argv[1], "-c" ){ //create
      // If creating (command line argument: -c):
      // Should make the shared memory, semaphore and file (open the file with the truncate flag).
      // Set any values that are needed.
      int *data;
      int shmd, semd, v, r;
      // char input[3];
      semd = semget(KEY, 1, IPC_CREAT | IPC_EXCL | 0644);  //excl makes sure it's not created again
      if (semd < 0){ //file already exists
        printf("Error semd create: %s\n", sterror(errno));
        semd = semget(KEY, 1, 0); //the 1 means that you want 1 semaphore
        v = semctl(semd, 0, GETVAL, 0); //gets the value of the semaphore.
        printf("semctl returned: %d\n", v);

      }
      else{ //file didn't exist yet
        union semun su;
        su.val = 1;
        r = semctl(semd, 0, SETVAL, su);
        printf("semctl returned: %d\n", r);

        struct sembuf sb;
        sb.sem-num = 0; //this is the semaphore number you want to use
        //sb.sem_flg = SEM_UNDO;
        sb.sem_op = -1; //downs the semaphore
        printf("semaphore created\n", );

        shmd = shmget(KEY, sizeof(int), IPC_CREAT | IPC_EXCL | 0644);
        if (shmd < 0){
          printf("Error shmd: %s\n", sterror(errno));
        }
        printf("shared memory created\n");
      }
      printf("shmd: %d\n, shmd);

      data = shmat(shmd, 0, 0);

      char[200] buffer;
      fgets(buffer,  200, stdin); //read in the user input
    }
    else if (!strcmp(argv[1], "-r" ){ //remove

    }
    else if (!strcmp(argv[1], "-v" ){ //view

    }
  }

}
