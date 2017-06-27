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

bool move(char** argv){
	bool r;
	if (argv[3] == NULL)
		return false;


	if (argv[1] != NULL){
		if (checkPath(argv[1])== NFILE) r = false;
		else if (checkPath(argv[1]) == NDIR) r = true;
		else {
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
				if (r == false) {
					//TODO: Move file to path
					std::cout << "MOVER ARQUIVO" << std::endl;
					return true;
				} else {
					//TODO: Recusively move
					std::cout << "MOVER PASTA" << std::endl;
					return true;
				}
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
