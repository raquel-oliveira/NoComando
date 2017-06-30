#ifndef __COMMANDS__
#define __COMMANDS__

#include <string>
//#include <cstring>

std::string help();

std::string enter(char**);

std::string createDirectory(char**);

std::string deleteFileOrDirectory(char**);

std::string recursiveDeleteDirectory(const char*);

std::string move(char**);

std::string my_rename(char**);

std::string ls();

double findMemValue(const char*);

std::string monitoring();

#endif
