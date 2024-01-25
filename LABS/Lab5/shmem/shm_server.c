#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define SHMSZ 50

int main(int argc, char *argv[])
{
    int shmid;
    key_t key = 1234;
    char *shm, *s;


    /* Create the segment. */
    /* nonnegative int shmget(key_t key, size_t size, int shmflg) */

    if ((shmid = shmget(key, SHMSZ, IPC_CREAT | 0666)) < 0) // if it is created IPC_ACCESS
    {
        perror("shmget");
        exit(1);
    }

    /* Now we attach the segment to our data space. */
    /* void *shmat(int shmid, const void *shmaddr, int shmflg) */
    if ((shm = shmat(shmid, NULL, 0)) == NULL)
    {
        perror("shmat");
        exit(1);
    }

    /* Now put some things into the memory for the other process to read. */
    s = shm;

    for(int j = 0; j < strlen(argv[1]); j++)
    {
        *(s++) = argv[1][j];
        printf("%c", *(s-1));
    }
    
    // *s++ = ' ';
    
    printf("\n");

    *s = NULL;
    /* Finally, we wait until the other process changes the first character of our memory
     * to '*', indicating that it has read what we put there.
     */
    while (*shm != '*')
        sleep(1);

    /* int shmctl(int shmid, int cmd, struct shmid_ds *buf);
    If the shared segment is no longer needed, remove it from the system with the shmctl */
    if ((shmctl(shmid, IPC_RMID, NULL)) < 0)
    {
        perror("shmctl");
        exit(1);
    }

    exit(0);
}
