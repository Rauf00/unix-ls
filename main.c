#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "UnixLs.h"

bool isL = false;
bool isI = false;
bool isR = false;
int optionsLen = 0;

static void getOptions(char* options) {
    if (strstr(options, "l")) {
        isL = true;
        optionsLen++;
    }
    if (strstr(options, "i")) {
        isI = true;
        optionsLen++;
    }
    if (strstr(options, "R")) {
        isR = true;
    }
}

int main(int argc, const char *argv[]) {
    if (argc > 3) {
        printf("Invalid num of args\n");
        return 0;
    }
    // no options, no path
    if (argc == 1) {
        UnixLs_ls(".", isI, isL, optionsLen);
    } 
    // options, no path
    else if (argc == 2 && strstr(argv[1], "-")) {
        char options[4];
        strcpy(options, argv[1]);
        getOptions(options);
        if (isR) {
            UnixLs_recurse(".", isI, isL, optionsLen);
        } else {
            UnixLs_ls(".", isI, isL, optionsLen);
        }
    } 
    // path, no options
    else if (argc == 2 && !strstr(argv[1], "-")) {
        char dirName[100];
        strcpy(dirName, argv[1]);
        UnixLs_ls(dirName, isI, isL, optionsLen);
    } 
    // path, options
    else if (argc == 3 && strstr(argv[1], "-")) {
        char dirName[100];
        char options[4];
        strcpy(dirName, argv[2]);
        strcpy(options, argv[1]);
        getOptions(options);
        if (isR) {
            UnixLs_recurse(dirName, isI, isL, optionsLen);
        } else {
            UnixLs_ls(dirName, isI, isL, optionsLen);
        }
    }
    return 0;
}

