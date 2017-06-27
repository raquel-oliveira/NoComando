#include "util.h"

int checkPath(char* path){
	struct stat sb;
	if( stat( path, &sb) != -1) {
		if( S_ISREG( sb.st_mode ) != 0 )
			return NFILE;
		else if (S_ISDIR (sb.st_mode) != 0 )
			return NDIR;
	}
	return -1;
}

char* stc(std::string str) {
	char *cstr = new char[str.length() + 1];
	strcpy(cstr, str.c_str());
	return cstr;
}

void where() {
	char* path = new char[1000];
	getcwd(path, 1000);
	std::cout << path << std::endl;
	delete[] path;
}
