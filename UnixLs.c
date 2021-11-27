#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 #include <sys/stat.h>
#include <dirent.h>
#include <time.h>
#include <unistd.h>
#include <grp.h>
#include <pwd.h>

static char* getGroup(gid_t grpNum) {
  struct group *grp;
  grp = getgrgid(grpNum); 
  if (grp) {
    return grp->gr_name;
  } else {
    printf("No group name for %u found\n", grpNum);
  }
}

static char* getUserName(uid_t uid) {
  struct passwd *pw = NULL;
  pw = getpwuid(uid);
  if (pw) {
    return pw->pw_name;
  } else {
    printf("No name found for %u\n", uid);
  }
}

static char* getDate(time_t mtime) {
    static char date[80];
    struct tm* localModifiedTime = localtime(&mtime);
    strftime(date, sizeof date, "%b %d %Y %H:%M", localModifiedTime);
    return date;
}

static char* getPermissions(mode_t mode, int fileType) {
    static char permissions[10];
    // is symbolic link?
    if (fileType == DT_LNK) {
        return "lrwxrwxrwx";
    }
    // is directory?
    permissions[0] = (S_ISDIR(mode)) ? 'd' : '-'; 
    // user permissions
    permissions[1] = (mode & S_IRUSR) ? 'r' : '-'; 
    permissions[2] = (mode & S_IWUSR) ? 'w' : '-'; 
    permissions[3] = (mode & S_IXUSR) ? 'x' : '-';
    // user permissions
    permissions[4] = (mode & S_IRGRP ) ? 'r' : '-'; 
    permissions[5] = (mode & S_IWGRP ) ? 'w' : '-'; 
    permissions[6] = (mode & S_IXGRP ) ? 'x' : '-';
    // user permissions
    permissions[7] = (mode & S_IROTH ) ? 'r' : '-'; 
    permissions[8] = (mode & S_IWOTH) ? 'w' : '-'; 
    permissions[9] = (mode & S_IXOTH) ? 'x' : '-';
    return permissions;
}

static char* getFileName(char* fileName) {
    char linkNameBuffer[100]; // is 100 reasonable size for linked filename????????????
    ssize_t count = readlink(fileName, linkNameBuffer, 100);
    if (count != -1) {
        strncat(fileName, "->", 3);
        strncat(fileName, linkNameBuffer, strlen(linkNameBuffer));
    }
    return fileName;
}

void UnixLs_ls(char* dirName, char* options) {
	DIR* pDir = opendir(dirName);
    if (pDir == NULL) {
        printf("ERROR: Directory doesn't exist!\n");
        return;
    }
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
            if (strlen(options) == 2 && strstr(options, "i")) {
                // skip hidden files
                if (pDirEntry->d_name[0] == '.'){
                    pDirEntry = readdir(pDir);
                    continue;
                }
                struct stat statBuffer;
                stat(pDirEntry->d_name, &statBuffer);
                printf("%ld %s  ", statBuffer.st_ino ,pDirEntry->d_name);
                pDirEntry = readdir(pDir);
            }
            // -l: use a long listing format
            else if (strstr(options, "l")) {
                if (pDirEntry->d_name[0] == '.'){
                    pDirEntry = readdir(pDir);
                    continue;
                }
                struct stat statBuffer;
                stat(pDirEntry->d_name, &statBuffer);
                // parse values to be printed
                char* groupName = getGroup(statBuffer.st_gid);
                char* userName = getUserName(statBuffer.st_uid);
                char* mtime = getDate(statBuffer.st_mtime);
                char* permissions = getPermissions(statBuffer.st_mode, pDirEntry->d_type);
                char* fileName = getFileName(pDirEntry->d_name);
                if (strstr(options, "i")) {
                    // -li or -il option
                    printf("%ld %s %ld %s %s %ld %s %s\n", statBuffer.st_ino, permissions, statBuffer.st_nlink, userName, groupName, statBuffer.st_size, mtime, fileName);
                } else {
                    printf("%s %ld %s %s %ld %s %s\n", permissions, statBuffer.st_nlink, userName, groupName, statBuffer.st_size, mtime, fileName);
                }
                pDirEntry = readdir(pDir);
            }
        } 
	}
    printf("\n");
}