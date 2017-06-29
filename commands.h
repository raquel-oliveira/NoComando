#ifndef __COMMANDS__
#define __COMMANDS__

#include <cstring>

void help();

void enter(char** argv);

void createFolder(char** argv);

void deleteFolder(char** argv);

bool move(char** argv);

void my_rename(char** argv);

#endif
