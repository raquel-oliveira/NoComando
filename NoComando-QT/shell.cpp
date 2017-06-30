#include "commands.h"
#include "util.h"

using namespace std;

/*
* @param input
* @return char** input separated by empty space
*/
char** inputByToken(string input){
    stringstream ss(input);
    vector<string> tokens;
    while(!ss.eof()) {
        string token;
        ss >> token;
        tokens.push_back(token);
    }
    int n = tokens.size();
    char** argv = new char*[n+1];
    for(int i = 0; i < n; i++) {
        argv[i] = stc(tokens[i]);
    }
    argv[n] = NULL;
    return argv;
}


char** processInput() {
    string input;
    getline(cin, input);
    return inputByToken(input);
}

std::string execute(char** argv, char** previous) {
    if(strcmp(argv[0], "sair") == 0)
        return ":";
    else if(strcmp(argv[0], "entrar") == 0)
        return enter(argv);
    else if(strcmp(argv[0], "onde") == 0)
        return pwd();
    else if(strcmp(argv[0], "renomear") == 0)
        return my_rename(argv);
    else if(strcmp(argv[0], "ajuda") == 0)
        return help();
    else if(strcmp(argv[0], "criar") == 0)
        return createDirectory(argv);
    else if(strcmp(argv[0], "deletar") == 0)
        return deleteFileOrDirectory(argv);
    else if(strcmp(argv[0], "mover") == 0)
        return move(argv);
    else if(strcmp(argv[0], "listar") == 0)
        return ls();
    else if(strcmp(argv[0], "repetir") == 0) {
        if(previous != NULL)
            return execute(previous, NULL);
    }
    return "";
}

