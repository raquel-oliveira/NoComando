#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <cstring>
#include <unistd.h>
#include <sstream>

using namespace std;

char* stc(string str) {
	char *cstr = new char[str.length() + 1];
	strcpy(cstr, str.c_str());
	return cstr;
}

/*char** processInput() {
	vector<char*> argv;
	char* arg;
	string input;
	getline(cin, input);
	cinput = stc(input);
	arg = strtok(cinput, " ");
  	while (arg != NULL){
    	argv.push_back(arg);
    	arg = strtok(NULL, " ");
  	}
  	argv.push_back(arg);
  	cout << 1 << endl;
	cout << argv[0] << endl;
	cout << 2 << endl;
  	return &argv[0];
}*/

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

void enter(char** argv) {
	if(argv[1] == NULL)
		cout << "> Entrar aonde? Tente de novo." << endl;
	else{
		if(chdir(argv[1]) != 0)
			cout << "> Não entrou" << endl;
	}
}

void where(char** argv) {
	char* path = get_current_dir_name();
	cout << "> " << path << endl;
}

bool execute(char** argv) {
	if(strcmp(argv[0], "sair") == 0)
		return false;
	else if(strcmp(argv[0], "entrar") == 0) 
		enter(argv);
	else if(strcmp(argv[0], "onde") == 0) {
		where(argv);
	}
	return true;
}

int main() {
	char** argv;
	bool running = true;
	while(running) {
		cout << "> ";
		//reads and parses input line
		argv = processInput();
		//executes command
		running = execute(argv);
		int i = 0;
		while(argv[i] != NULL) {
			delete[] argv[i];
			i++;
		}
		delete[] argv;
	}
}