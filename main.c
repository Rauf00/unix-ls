#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "UnixLs.h"

#define MAX_FILE_PATH_SIZE 4096

static bool isL = false;
static bool isI = false;
static bool isR = false;
static bool isPathOption = false;
static int optionsLen = 0;

static void getOptions(char* options) {
    if (!strstr(options, "l") && !strstr(options, "i") && !strstr(options, "R")) {
        printf("Error: invalid option\n");
        exit(1);
    }
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
    if (argc > 5) {
        printf("Invalid num of args\n");
        return 0;
    }

    if(argc == 1) {
        UnixLs_ls(".", isI, isL, isR, optionsLen);
        return 0;
    }

    for (int i = 1; i < argc; i++) {
        if (strstr(argv[i], "-")) {
            char options[5];
            strcpy(options, argv[i]);
            getOptions(options);
        } else {
            isPathOption = true;
        }
    }

    if (isPathOption) {
        char dirName[MAX_FILE_PATH_SIZE];
        strcpy(dirName, argv[argc - 1]);
        if (isR) {
            UnixLs_recurse(dirName, isI, isL, optionsLen);
        } else {
            UnixLs_ls(dirName, isI, isL, isR, optionsLen);
        }
    } else {
        if (isR) {
            UnixLs_recurse(".", isI, isL, optionsLen);
        } else {
            UnixLs_ls(".", isI, isL, isR, optionsLen);
        }
    }
    return 0;
}

