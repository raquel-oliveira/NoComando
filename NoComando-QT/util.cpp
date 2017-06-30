#include "util.h"

int check_path(char* path){
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

std::string pwd() {
    char* path = new char[1000];
    return getcwd(path, 1000);
    std::string s = std::string(path);
    delete[] path;
    return s;
}

const char *get_basename(const char *filename) {
    const char *b = strrchr(filename, '/');
    return (b == NULL) ? filename : (b + 1);
}

bool is_dot_dir(const char *filename) {
    return (filename[0] == '.')
             && (filename[1] == '\0' || (filename[1] == '.' && filename[2] == '\0'));
}

void print_console(std::string input){
    std::cout << input << std::endl;
}
