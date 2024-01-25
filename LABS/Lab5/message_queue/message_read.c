#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
  
// structure for message queue
struct message_buffer 
{
    long message_type;
    char message_text[100];
}message;
  
int main()
{
    /* 
        Unix requires a key of type key_t defined in file sys/types.h 
        for requesting resources such as shared memory segments, message queues and semaphores. 

        A key is simply an integer of type key_t; however, you should not use int or long, since the length of a key is system dependent.
    */

    key_t key; 

    int message_id;  
  
    /*    
        key_t ftok(const char *path, int id);  
        paths between reader and writer must be the same.
    */
    key = ftok(".", 250);
  

    /*
        The msgget() system call returns the System V message queue
        identifier associated with the value of the key argument.  

        If IPC_CREAT is used, msgget() either returns the message queue identifier for a newly created message queue, 
        or returns the identifier for a queue which exists with the same key value

    */    

    message_id = msgget(key, 0666); // permissions are rw-rw-rw- (user-group-others)
                                                // for more detail about the permissions 
                                                // visit https://www.guru99.com/file-permissions.html  


    /*
        The msgrcv() system call is used to receive messages from a message queue. 
        The calling process must have read permission to receive a message.
        
        msgrcv(int msqid, void *msgp, size_t msgsz, long msgtyp, int msgflg);
    */

    msgrcv(message_id, &message, sizeof(message), 1, 0);

    // display the message
    printf("Data Received is : %s \n",  message.message_text);
  

    /*

        msgctl() performs the control operation specified by cmd on the
        System V message queue with identifier msqid.
        
        msgctl(int msqid, int cmd, struct msqid_ds *buf);

        with IPC_RMID, remove the message queue.
    */

    msgctl(message_id, IPC_RMID, NULL);  
    return 0;
}
