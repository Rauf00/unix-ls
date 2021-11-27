#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "UnixLs.h"

int main(int argc, const char *argv[])
{
    if (argc > 3) {
        printf("Invalid num of args\n");
        return 0;
    }
    if (argc == 1) {
        UnixLs_ls(".", NULL);
    } 
    else if (argc == 2 && strstr(argv[1], "-")) {
        char options[4];
        strcpy(options, argv[1]);
        UnixLs_ls(".", options);
    } 
    else if (argc == 2 && !strstr(argv[1], "-")) {
        char dirName[100];
        strcpy(dirName, argv[1]);
        UnixLs_ls(dirName, NULL);
    } 
    else if (argc == 3 && strstr(argv[1], "-")) {
        char dirName[100];
        char options[4];
        strcpy(options, argv[1]);
        strcpy(dirName, argv[2]);
        UnixLs_ls(dirName, options);
    }
    
    return 0;
}

