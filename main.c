#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "UnixLs.h"

#define MAX_FILE_PATH_SIZE 4096

static bool isL = false;
static bool isI = false;
static bool isR = false;
static int optionsLen = 0;

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
        char dirName[MAX_FILE_PATH_SIZE];
        strcpy(dirName, argv[1]);
        UnixLs_ls(dirName, isI, isL, optionsLen);
    } 
    // path, options
    else if (argc == 3 && strstr(argv[1], "-")) {
        char dirName[MAX_FILE_PATH_SIZE];
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

