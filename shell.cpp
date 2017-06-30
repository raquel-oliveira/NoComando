#include "commands.h"
#include "util.h"

using namespace std;

char** processInput() {
	string input;
	getline(cin, input);
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

bool execute(char** argv, char** previous) {
	if(strcmp(argv[0], "sair") == 0)
		return false;
	else if(strcmp(argv[0], "entrar") == 0)
		enter(argv);
	else if(strcmp(argv[0], "onde") == 0)
		pwd();
	else if(strcmp(argv[0], "renomear") == 0)
		my_rename(argv);
	else if(strcmp(argv[0], "ajuda") == 0)
		help();
	else if(strcmp(argv[0], "criar") == 0)
		createDirectory(argv);
	else if(strcmp(argv[0], "deletar") == 0)
		deleteFileOrDirectory(argv);
	else if(strcmp(argv[0], "mover") == 0)
		move(argv);
	else if(strcmp(argv[0], "listar") == 0)
		ls();
	else if(strcmp(argv[0], "repetir") == 0) {
		if(previous != NULL)
			execute(previous, NULL);
	}
	return true;
}

int main() {
	char** argv;
	char** previous = NULL;
	bool running = true;
	while(running) {
		cout << "> ";
		//reads and parses input line
		argv = processInput();
		//executes command
		running = execute(argv, previous);
		if(previous != NULL && strcmp(argv[0], "repetir") != 0) {
			int i = 0;
			while(previous[i] != NULL) {
				delete[] previous[i];
				i++;
			}
			delete[] previous;
		}
		if(strcmp(argv[0], "repetir") != 0)
			previous = argv;
	}
}
