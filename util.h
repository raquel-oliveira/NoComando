#ifndef __UTIL__
#define __UTIL__

#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <cstring>
#include <sstream>

#include <sys/stat.h> // to check file/dir
#include <sys/types.h> // to check file/dir
#include <unistd.h> // to check file/dir

#include <stdbool.h>

#define NDIR 0
#define NFILE 1

int checkPath(char* path);

char* stc(std::string str);

void where();

#endif
