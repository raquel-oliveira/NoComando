#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <cstring>

using namespace std;

char* stc(string str) {
	char *cstr = new char[str.length() + 1];
	strcpy(cstr, str.c_str());
	return cstr;
}

char** processInput() {
	vector<char*> argv;
	char* arg;
	string input;
	getline(cin, input);
	char* cinput = stc(input);
	arg = strtok(cinput, " ");
  	while (arg != NULL){
    	argv.push_back(arg);
    	arg = strtok(NULL, " ");
  	}
  	delete[] cinput;
  	argv.push_back(arg);
  	return &argv[0];
}

bool execute(char** argv) {
	if(strcmp(argv[0], "sair") == 0)
		return false;
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
	}
}