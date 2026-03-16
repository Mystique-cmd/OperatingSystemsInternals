/*The file basically lists the running process in a linux system by inspecting the /proc directory
On , linux the kernel exposes information about running process through a special virtual filesystem located ar /proc
Inside this directory there are numerous subdirectories, each named with teh PID. The program works by listing
these numbered directories and reading the process name from a file within each one*/

#include <stdio.h> //for std io operations - printf, snprintf, fopen ...
#include <stdlib.h> // for general utilities - memory allocation , processes control, conversions, random no. searching, sorting
#include <dirent.h> // for directory handling functions - opendir, readdir, closedir..
#include <string.h> // for string manipulation functions - strcspn
#include <ctype.h> // for character type functions

#define PROC_DIR "/proc"    //defines a constant for the path to the proc filesystem
#define COMM_FILE "comm" /*defines a constant for the filename comm. Inside each /proc/<PID> the file named comm
contains the command name associated with that process*/


/*This function checks if a given string consists entirely of digits. It iterates through each character of a string while (*str)
If it finds any character that is not  a digit (!isdigit(*), it immediately returns 0. If the loop completes  without finding any
non-digit characters it means the string represents a number and it returns 1. This is used to identify which directory names
in /proc are PIDs*/
int is_number(const char *str){
    while (*str){
        if (!isdigit(*str)) return 0;
        str ++;
    }
    return 1;
}

/*This is the entry point of the program. It declares variables to handle the directory stream (dir) and individual directory entries
(entry) . It calls opendir() to open teh /proc directory. If it fails due to sth like permission issues then it will print an error and exit
*/
int main () {
    DIR * dir;
    struct dirent * entry;

    dir = opendir(PROC_DIR);
    if (!dir){
        perror("opendir");
        return 1;
    }

//This two lines simply print the header of the output table, making it readable
    printf("%-10s %-s\n", "PID", "Process Name");
    printf("=====================\n");

/*The while loop  is the core of the program. readdir(dir) reads the next entry( file or subdirectory) from the /proc directory
The loop continues as long as there are entries to read*/
    while ((entry = readdir(dir)) != NULL){

/*For each entry it calls is_number()  on the entry's name ( entry -> d_name). This check filters out all non-process related files
and directories in /proc, ensuring we only look at directories whose names are PIDs*/
        if (is_number(entry -> d_name)){

/*If the entry is a PID , this code constructs the full path to that process comm file. For example if the PID is 1234 the path
becomes /proc/i234/comm*/
            char path[256];
            snprintf(path, sizeof(path), "%s/%s/%s" , PROC_DIR, entry->d_name, COMM_FILE);

/*It opens the constructed path for reading ( fopen(path "r"). If the file is opened successfully , it reads the first line from it
into the name buffer  using fgets(). The function fgets() usually includes a newline character at the end of the string. The line
name[strcspn..... finds and removes this newlilne by replacing it with a null terminator. It then prints the PID and the cleaned process
name. Finally it closes the file*/
            FILE *fp = fopen(path, "r");
            if (fp){
                char name [256];
                if (fgets(name, sizeof (name), fp) != NULL){
                    name[strcspn(name ,"\n")] = '\0';
                    printf("%-10s %-s\n", entry ->d_name, name);
                }
                fclose(fp);
            }
        }
    }
// this closes hte proc directory after the loop finishes to free up resources. A return of 0 indicates that the program
//executed successfully
    closedir(dir);
    return 0;
}