#include "util.h"

void enter(char** argv) {
	if(argv[1] == NULL)
		std::cout << "Entrar onde? Tente de novo." << std::endl;
	else{
		if(chdir(argv[1]) != 0)
			std::cout << "Erro: não entrou na pasta." << std::endl;
	}
}

void createFolder(char** argv) {
	if(argv[2] == NULL)
		std::cout << "Qual será o nome da pasta? Tente de novo." << std::endl;
	else{
		char* path = new char[1000];
		getcwd(path, 1000);
		strcat(path, "/"); strcat(path, argv[2]);
		if(mkdir(path,S_IRWXU|S_IRWXG|S_IRWXO) != 0)
			std::cout << "Erro: não criou pasta." << std::endl;
	}
}

void deleteFolder(char** argv) {
	if(argv[2] == NULL)
		std::cout << "Qual pasta? Tente de novo." << std::endl;
	else{
		char* path = new char[1000];
		getcwd(path, 1000);
		strcat(path, "/"); strcat(path, argv[2]);
		if(rmdir(path) != 0)
			std::cout << "Erro: não deletou pasta." << std::endl;
	}
}

void my_rename(char** argv){
	if (argv[3] == NULL){
		return;
	}
	if (strcmp(argv[2], "para") != 0){
		std::cout << "Escreva o nome 'para' para dizer onde quer mover" << std::endl;
		return;
	}

	char* source = new char[1000];
	getcwd(source, 1000);
	strcat(source, "/"); strcat(source, argv[1]);

	char * dest = new char[1000];
	if (strcmp(argv[0], "mover") == 0){
		strcat(dest, argv[3]);
		strcat(dest, "/");
		strcat(dest, argv[1]);
	}
	else if (strcmp(argv[0], "renomear") == 0){
		getcwd(dest, 1000);
		strcat(dest, "/"); strcat(dest, argv[3]);
	}

	int result = rename(source, dest);
  if (result != 0)
    perror( "Problema" );
	delete [] source;
	delete [] dest;
}

//TODO: move something to the actual directory
//TODO: don't use same as rename, use something that allows the move of files/dir from diferent source paths
bool move(char** argv){
	if (argv[3] == NULL)
		return false;

	if (argv[1] != NULL){
		if (checkPath(argv[1]) == -1) {
			std::cout << "Acho que não é o arquivo correto. Tente novamente" << std::endl;
			return false;
		}
	} else{
		std::cout << "Mover o que?\nTente de novo" << std::endl;
		return false;
	}
	if (strcmp(argv[2], "para") == 0){
		if (argv[3] != NULL) {
			if (checkPath(argv[3]) == NFILE){
				std::cout << "Não pode mover para dentro de um arquivo :c" << std::endl;
			} else if (checkPath(argv[3]) == NDIR){
					my_rename(argv);
			} else{
				std::cout << "Você deve mover para uma pasta" << std::endl;
			}
		} else{
			std::cout << "Mover para onde?" << std::endl;
		}
	} else {
		std::cout << "Escreva o nome 'para' para dizer onde quer mover" << std::endl;
	}
	return false;
}
