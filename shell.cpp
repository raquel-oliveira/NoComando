#include "shell.h"

using namespace std;

char* stc(string str) {
	char *cstr = new char[str.length() + 1];
	strcpy(cstr, str.c_str());
	return cstr;
}

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
		cout << "Entrar aonde? Tente de novo." << endl;
	else{
		if(chdir(argv[1]) != 0)
			cout << "Não entrou" << endl;
	}
}

void where() {
	char* path = new char[1000];
	getcwd(path, 1000);
	cout << path << endl;
	delete[] path;
}

/*
* For this routine. The user should be in the path of the file
to rename.
TODO: works with absolute path and all relative paths
*/
void my_rename(char** argv){
	/*snprintf (argv[2], sizeof(argv[2]), "../MST/%s", argv1);
	if (rename (file, path)) {
		if (errno == EXDEV) {

		} else {
			perror("rename"); exit(EXIT_FAILURE);
		};
	}*/
	char* source = new char[1000];
	getcwd(source, 1000);
	strcat(source, "/"); strcat(source, argv[1]);

	char * dest = new char[1000];
	getcwd(dest, 1000);
	strcat(dest, "/"); strcat(dest, argv[2]);

	int result = rename(source, dest);
  if (result != 0)
    perror( "Problema para renomear" );
	delete [] source;
	delete [] dest;
}


bool execute(char** argv) {
	if(strcmp(argv[0], "sair") == 0)
		return false;
	else if(strcmp(argv[0], "entrar") == 0)
		enter(argv);
	else if(strcmp(argv[0], "onde") == 0)
		where();
	else if(strcmp(argv[0], "renomear") == 0)
		my_rename(argv);
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
