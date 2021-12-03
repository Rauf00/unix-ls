#ifndef _UNIX_LS_
#define _UNIX_LS_

void UnixLs_ls(char* dirName, bool isI, bool isL, bool isR, int optionsLen);
void UnixLs_recurse(char* dirName, bool isI, bool isL, int optionsLen);

#endif