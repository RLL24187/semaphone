#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/stat.h>
#include <time.h>
#include <dirent.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>

int main(int argc, char * argv[]){
  if (argc > 1){
    if (!strcmp(argv[1], "-c" ){ //create
      // If creating (command line argument: -c):
      // Should make the shared memory, semaphore and file (open the file with the truncate flag).
      // Set any values that are needed.
      int *data;
      int shmd;
      char input[3];
      shmd = shmget(KEY, sizeof(int), IPC_CREAT | IPC_EXCL | 0644);
      if (errno < 0){
        printf("Error shmget: %s\n", strerror(errno));
      }
      if (shmd < 0){
        printf("Error shmd: %s\n", sterror(errno));
        return 1;
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
