#ifndef __COMMANDS__
#define __COMMANDS__

#include <cstring>

void help();

void enter(char**);

void createDirectory(char**);

void deleteFileOrDirectory(char**);

void recursiveDeleteDirectory(const char*);

bool move(char**);

void my_rename(char**);

void ls();

#endif
