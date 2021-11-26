#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 #include <sys/stat.h>
#include <dirent.h>

void UnixLs_ls(char* dirName, char* options) {
	DIR* pDir = opendir(dirName);
    struct dirent* pDirEntry = readdir(pDir);
	while (pDirEntry != NULL)
	{   
        if (options == NULL) {
            if (pDirEntry->d_name[0] == '.'){
                pDirEntry = readdir(pDir);
                continue;
            }
            printf("%s  ", pDirEntry->d_name);
            pDirEntry = readdir(pDir);
        }
        else {
            // -i: print the index number of each file
            if (strstr(options, "i")) {
                if (pDirEntry->d_name[0] == '.'){
                    pDirEntry = readdir(pDir);
                    continue;
                }
                struct stat statBuffer;
                stat(pDirEntry->d_name, &statBuffer);
                printf("%ld %s  ", statBuffer.st_ino ,pDirEntry->d_name);
                pDirEntry = readdir(pDir);
            }
        } 
	}
    printf("\n");
}
