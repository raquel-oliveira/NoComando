#ifndef __COMMANDS__
#define __COMMANDS__

#include <string>
//#include <cstring>

std::string help();

std::string enter(char** argv);

std::string createFolder(char** argv);

std::string deleteFolder(char** argv);

std::string move(char** argv);

std::string my_rename(char** argv);

std::string ls();

#endif
