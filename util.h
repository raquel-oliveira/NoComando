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
#include <dirent.h>

#include <stdbool.h>

#define NDIR 0
#define NFILE 1

/*
* Given a path
* @return 1(NFILE) if is a file
* @return 0(NDIR) if is a directory
* @return -1 otherwise.
*/
int check_path(char* path);

/*
* @param string
* @return the same string of input as char *
*/
char* stc(std::string str);

// Prints current path
void pwd();

//Base name of a file
const char *get_basename(const char *filename);

/*
* @return true if path has '.' or '..'
* @return false otherwise
*/
bool is_dot_dir(const char *filename);

#endif
