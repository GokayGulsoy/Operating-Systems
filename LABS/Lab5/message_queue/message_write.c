// C Program for Message Queue (Writer Process)
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define MAX 100
  
// structure for message queue
struct message_buffer
{
    long message_type;
    char message_text[MAX];
}message;
  
int main()
{

    /* 
        Unix requires a key of type key_t defined in file sys/types.h 
        for requesting resources such as shared memory segments, 
        message queues and semaphores. 

        A key is simply an integer of type key_t; however, 
        you should not use int or long, since the length of a key is system dependent.
    */

    key_t key;

    int message_id;
  
    // ftok to generate unique key

    /*    
        key_t ftok(const char *path, int id);  
        paths between reader and writer must be the same.
    */
    // Hence, to generate unique key

    key = ftok(".", 250);
  
    /*
        The msgget() system call returns the System V message queue
        identifier associated with the value of the key argument.  

        If IPC_CREAT is used, msgget() either returns the message queue identifier for a newly created message queue, 
        or returns the identifier for a queue which exists with the same key value

    */    

    message_id = msgget(key, 0666 | IPC_CREAT);
    message.message_type = 1;
  
    printf("Write Data : ");
    fgets(message.message_text, MAX, stdin);
  
    /*
        The msgsnd() system call is used to send messages from a message queue. 
        The calling process must have write permission on the message queue in order to send a message

        msgsnd(int msqid, const void *msgp, size_t msgsz, int msgflg);    
    */
    msgsnd(message_id, &message, sizeof(message), 0);
  
    // display the message
    printf("Data send is : %s \n", message.message_text);  
    return 0;
}
