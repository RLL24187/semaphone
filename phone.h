#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <time.h>
#include <dirent.h>

#include <sys/stat.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>

#define KEY 24601

union semun { //must include in header file b/c this will be run on LINUX machine
  int              val;    // Value for SETVAL
  struct semid_ds *buf;    // Buffer for IPC_STAT, IPC_SET
  unsigned short  *array;  // Array for GETALL, SETALL
  struct seminfo  *__buf;  // Buffer for IPC_INFO
};
