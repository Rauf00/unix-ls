#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "UnixLs.h"

int main(int argc, const char *argv[])
{
    if (argc > 2) {
        printf("Invalid num of args\n");
        return 0;
    }
    if (argc == 2) {
        char options[4];
        strcpy(options, argv[1]);
        UnixLs_ls(".", options);
    } else {
        UnixLs_ls(".", NULL);
    }
    
    return 0;
}

