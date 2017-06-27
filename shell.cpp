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

void help() {
	cout << "Aqui está a ajuda!" << endl;
	cout << "Os comandos disponíveis são:" << endl;
	cout << "  ajuda" << endl;
	cout << "  entrar NOME_DA_PASTA" << endl;
	cout << "  onde estou?" << endl;
	cout << "  renomear NOME_DO_ARQUIVO/PASTA" << endl;
	cout << "  criar pasta NOME_DA_PASTA" << endl;
	cout << "  deletar pasta NOME_DA_PASTA" << endl;
	cout << "  sair" << endl;
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
	else if(strcmp(argv[0], "ajuda") == 0)
		help();
	else if(strcmp(argv[0], "criar") == 0)
		createFolder(argv);
	else if(strcmp(argv[0], "deletar") == 0)
		deleteFolder(argv);
	else if(strcmp(argv[0], "mover") == 0)
		move(argv);
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
