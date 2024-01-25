/*
   270201071 Merve Nur Ozan
   270201072 Gökay Gülsoy
*/
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>

/*@brief This structure must be used as nodes for the linked list.
 * @r_node: must point to the right node of the linked list.
 * @value: must hold the given number.**/
typedef struct node {
    struct node *r_node;
    unsigned value;
}node;

/*@brief This is the main hash table pointer. You must use a function to create a
 *double-linked list to index the corresponding linked list with modular
 *arithmetic (taking care of modulus/remainder value) for the corresponding
 *function.
 * @node: Double linked list pointer. The first index of the storage 1D link list
 *must be calculated with modular arithmetic. The second will hold the
 *numbers whose modulus result is the same.
 * @nof_element: must hold the total amount of the stored numbers. **/
typedef struct hash_table {
    node** list;
    unsigned nof_elements;
}hash_table;

/*@brief To pass multiple structures to a thread during call/creating, you will
 *need a specialized structure holding all the required sub-structures.
 *You can design this structure as you wish. **/
typedef struct parameterPass
{
    hash_table* hashTableParameter;
    int* arrayOfNumbers;
    int numberOfTHreads;

} parameterPass;

// pointer to hash table
hash_table *hashTable;
// varible to keep track of thread ids
// which will be initialized as zero
int thread_id;
// mutex lock variable
pthread_mutex_t lock;

/* @brief, you must count the amount of numbers in the given CSV file.
 * @return value must hold the amount of numbers.
 * @filename: holds the name of CSV filename **/
unsigned countNumOfElements(char* filename) {

    FILE *file_ptr;
    char str[60];
    file_ptr = fopen(filename, "r");

    if (file_ptr == NULL) {
        printf("File couldn't be opened");
        exit(1);
    }

    int num_elements = 0;
    while (fgets(str, 60, file_ptr) != NULL)
    {
        num_elements++;
    }

    fclose(file_ptr);

    /*we subtract 1 because first line is contains headers*/
    return num_elements-1;
}

/*@brief You will allocate an array with the amount of num_elements.Then, you
*
will read all the numbers from the given .csv file into this array
* @return pointer must point to the array allocated dynamically and hold the
*
numbers.
* @filename: must hold the CSV filename.
* @num_element: must hold the amount of number in the given .csv file. */
unsigned* readNumbers(char* filename,unsigned num_element) {

    int *number_array = malloc(num_element * sizeof(unsigned));
    FILE *file_ptr;
    file_ptr = fopen(filename, "r");
    char str[60];
    char *token;

    int index = 0;

    /*reading the header line*/
    fgets(str, 60, file_ptr);
    
    while (fgets(str,60,file_ptr) != NULL) {

        // getting rid of number id
        strtok(str, ",");
        token = strtok(NULL, ",");
        number_array[index] = atoi(token);
        index++;
    }

    fclose(file_ptr);

    return number_array;
}

/* @brief You must initialize the basis 2D linked list structure. The outlier
 *dimension must include (numOfThread * (numOfThread + 1))/2 indices.
 *Each dimension will hold a linked list to store each modular result
 *for each number respectively.
 * @numOfThread: is the number of threads entered by the user.
 * @numOfElements: holds the amount of numbers within the given CSV file.*/
hash_table *initializeHashTable(unsigned numOfThread, unsigned numOfElements)
{
    hashTable->nof_elements = numOfElements;
    int outlier_size = (numOfThread * (numOfThread + 1)) / 2;
    hashTable->list = (node **)malloc(sizeof(node *) * outlier_size);

    // initializing each 1D Linked List to NULL
    for (int i = 0; i < outlier_size; i++) {
        hashTable->list[i] = NULL;
    }
}

/*1st function to be used by number of threads*/
void* insertionFunction(void *parameters) {

    // thread_id is a shared varible
    // which is accessed by all threads
    // we put a mutex lock when incrementing it
    pthread_mutex_lock(&lock);

    parameterPass* parameterGroup = (parameterPass* )parameters;
    hash_table *table = parameterGroup->hashTableParameter;
    int nof_elements = parameterGroup->hashTableParameter->nof_elements;
    int num_of_threads = parameterGroup->numberOfTHreads;

    int interval = nof_elements / num_of_threads + 1;
    unsigned offset = interval * thread_id;
    unsigned last_ele = offset + interval;
    if (last_ele > nof_elements) {

        last_ele = nof_elements;
    }

    for (int i = offset; i < last_ele; i++) {
        int hashIndex = (parameterGroup->arrayOfNumbers[i]) % ((num_of_threads * (num_of_threads+1)) / 2);

        node* new_node = (node *)malloc(sizeof(node));
        new_node->value = parameterGroup->arrayOfNumbers[i];
        new_node->r_node = NULL;

        if (table->list[hashIndex] == NULL)
        {

            table->list[hashIndex] = new_node;
        }

        else
        {              
            new_node->r_node = table->list[hashIndex];
            table->list[hashIndex] = new_node;
        }
    }

    thread_id++;
    pthread_mutex_unlock(&lock);

    pthread_exit(NULL);
}

/*Function for swap subroutine*/
void swap(node* a,node* b) {
    int temp = a->value;
    a->value = b->value;
    b->value = temp;
}

// function for bubble sort*/
void* bubbleSort(void* start) {

    node* our_start = (node *)start;
    int isSwapped;
    node *ptr;
    node *toPtr = NULL;

    // if linked list is empty
    // terminate function
    if (start == NULL) {

        pthread_exit(NULL);
    }

    do {

        isSwapped = 0;
        ptr = our_start;

        while (ptr->r_node != toPtr) {
              
              if (ptr->value > ptr->r_node->value) {
                  swap(ptr, ptr->r_node);
                  isSwapped = 1;
              }

              ptr = ptr->r_node;
        }

        toPtr = ptr;

    } while (isSwapped);

    pthread_exit(NULL);
}

/*main function*/
int main(int argc,char* argv[]) {

        if (argc != 3) {

        printf("Program expects ./executable_name <numbers.csv> <numOfThreads> format\n");
        exit(1);
        }

        // file name given as the second argument
        // from command line
        char *filename = argv[1];
        int num_element = countNumOfElements(filename);
        int *number_array = readNumbers(filename, num_element);

        // number of threads given as the third
        // argument from command line
        int num_of_threads = atoi(argv[2]);
        // dynamically allocating memory for hash table
        hashTable = (hash_table *)malloc(sizeof(hash_table));
        initializeHashTable(num_of_threads, num_element);

        // allocating parameterPass struct
        parameterPass* passedParameters = (parameterPass *)malloc(sizeof(parameterPass));
        passedParameters->arrayOfNumbers = number_array;
        passedParameters->hashTableParameter = hashTable;
        passedParameters->numberOfTHreads = num_of_threads;

        pthread_t thread_array[num_of_threads];
        // initializing thread_id as 0
        thread_id = 0;

        for (int i = 0; i < num_of_threads; i++)
        {
            pthread_create(&(thread_array[i]), NULL, insertionFunction,(void* )passedParameters);
        }

        for (int i = 0; i < num_of_threads; i++) {

            pthread_join(thread_array[i], NULL);
        }

        pthread_mutex_destroy(&lock);
         
      
        int sortingThreadNumber = (num_of_threads * (num_of_threads + 1)) / 2;
        pthread_t thread_array2[sortingThreadNumber];
        for (int i = 0; i < sortingThreadNumber; i++) {

            pthread_create(&(thread_array2[i]), NULL, bubbleSort,(void* )hashTable->list[i]);
        }

        for (int i = 0; i < sortingThreadNumber; i++) {

            pthread_join(thread_array2[i], NULL);
        }

        /* you can see the example output by uncommenting this line
        int counter = 0;
        node *our_node = hashTable->list[0];
        while (our_node != NULL)
        {

            printf("Chain 1 Number %d: %d\n", counter, our_node->value);
            counter++;
            our_node = our_node->r_node;
        }
        */

        /* deallocating all the dynamically
        allocated memory*/
        int outlier_size = (num_of_threads * (num_of_threads + 1)) / 2;

        free(number_array);
        for (int i = 0; i < outlier_size; i++) {

            node *current_node = hashTable->list[i];
            node *prev,*prev_next;
            while (current_node != NULL)
            {
              prev = current_node;
              current_node = current_node->r_node;
              free(prev);
            }
        }
        
        free(hashTable->list);
        free(hashTable);
        free(passedParameters);

        pthread_exit(NULL);        
}