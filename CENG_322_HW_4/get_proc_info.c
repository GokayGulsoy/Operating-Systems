/*
Group Number: G18
Student number: 270201071 Merve Nur Ozan
Student number: 270201072 Gökay Gülsoy
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

// helper function to check
// whether argument is number or not
int isNumber(char* param) {
    // if empty string is
    // passed as parameter 
    // we directly return -1
    if (strcmp(param,"") == 0) {
       return -1;               
    }

     int len = strlen(param);
     for (int i = 0; i < len; i++) {
         if (!isdigit(param[i])) {
            return -1; 
         }
     } 
    
     return 1;
}	

// User space wrapper application
int main(int argc, char *argv[]) {
    // we are checking the number of arguments passed
    // from the command line
    if(argc != 4) {
        printf("Argument Number Error: Number of arguments passed doesn't match\n");
        exit(1);
    }

    char* app_file_path = argv[1];
    char* argument_type = argv[2];
    char* argument_value = argv[3];

    char insert_module[300];
    char remove_module[] = "sudo rmmod proc_info_module";
    
    // checking whether given pid is negative
    if (strcmp(argument_type, "-pid") == 0 && argument_value <= 0) {
        printf("PID value error: pid value cannot be negative or zero!\n");
        exit(1);      
    }
  
    // inserting the module with the given parameter  
    // and giving error if given second parameter is not 
    // equal to either -pid or -pname
    if (strcmp(argument_type, "-pid") == 0 && isNumber(argument_value) == 1) {
        int numeric_argument = atoi(argument_value);
        sprintf(insert_module,"sudo insmod %s upid=%d",app_file_path, numeric_argument);
    } 
    else if (strcmp(argument_type, "-pname") == 0 && isNumber(argument_value) == -1) {
        sprintf(insert_module,"sudo insmod %s upname=%s",app_file_path, argument_value);
    }
    else {
        printf("Argument Type Error: Given argument type and value combination is invalid. Pass either correct -pid or -pname combination! \n");
        exit(1); 
    }
        
    
    // Inserting the module by executing shell command
    int return_value = system(insert_module);
    if(return_value != 0) {
        printf("Module Insertion Error: Insertion of module failed.\n");
        exit(1);
    }

    // reading contents of proc file
    // and printing them to terminal
    char* line = NULL;
    size_t len = 0;
    ssize_t read_value;
    FILE *proc_file_ptr = fopen("/proc/proc_info_module", "r");
    if(proc_file_ptr == NULL) {
        printf("Proc file open error: Failed to open /proc file!\n");
        // removing the module before exiting the program
        system(remove_module); 
        exit(1);
    }

    while((read_value = getline(&line, &len, proc_file_ptr)) != -1) {
        printf("%s", line);
    }

    
    // closing the proc file
    fclose(proc_file_ptr);
    

    // Removing the module    
    return_value = system(remove_module);
    if(return_value != 0) {
        printf("Proc file remove error: Removal of module failed!\n");
        exit(1);
    }
    
    return 0;
}
