#include "util.h"

void help() {
    std::cout << "Aqui está a ajuda!" << std::endl;
    std::cout << "Os comandos disponíveis são:" << std::endl;
    std::cout << "  ajuda" << std::endl;
    std::cout << "  entrar NOME_DA_PASTA" << std::endl;
    std::cout << "  onde estou?" << std::endl;
    std::cout << "  renomear NOME_DO_ARQUIVO/PASTA" << std::endl;
    std::cout << "  criar pasta NOME_DA_PASTA" << std::endl;
    std::cout << "  deletar pasta NOME_DA_PASTA" << std::endl;
    std::cout << "  sair" << std::endl;
}

std::string enter(char** argv) {
    if(argv[1] == NULL)
        return "Entrar onde? Tente de novo.";
    else{
        if(chdir(argv[1]) != 0)
            return "Erro: não entrou na pasta.";
        return "";
    }
}

std::string createFolder(char** argv) {
    if(argv[2] == NULL)
        return "Qual pasta?\nTente de novo.";
    else{
        char* path = new char[1000];
        getcwd(path, 1000);
        strcat(path, "/"); strcat(path, argv[2]);
        if(mkdir(path,S_IRWXU|S_IRWXG|S_IRWXO) != 0)
            return "Erro: não criou pasta." ;
        return "";
    }
}

std::string deleteFolder(char** argv) {
    if(argv[2] == NULL)
        return "Qual pasta?\nTente de novo.";
    else{
        char* path = new char[1000];
        getcwd(path, 1000);
        strcat(path, "/"); strcat(path, argv[2]);
        if(rmdir(path) != 0)
            return "Erro: não deletou pasta.";
        return "";
    }
}

std::string my_rename(char** argv){
    if (argv[3] == NULL){
        return "Tente de novo";
    }
    if (strcmp(argv[2], "para") != 0){
        return "Escreva o nome 'para' para dizer onde quer mover";
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
    delete [] source;
    delete [] dest;
  if (result != 0)
    return "Problema" ;
   return "";
}

//TODO: move something to the actual directory
//TODO: don't use same as rename, use something that allows the move of files/dir from diferent source paths
std::string move(char** argv){
    if (argv[3] == NULL)
        return "Tente de novo";

    if (argv[1] != NULL){
        if (check_path(argv[1]) == -1) {
            return "Acho que não é o arquivo correto. Tente novamente";
        }
    } else{
        return "Mover o que?\nTente de novo";
    }
    if (strcmp(argv[2], "para") == 0){
        if (argv[3] != NULL) {
            if (check_path(argv[3]) == NFILE){
                return "Não pode mover para dentro de um arquivo :c";
            } else if (check_path(argv[3]) == NDIR){
                    my_rename(argv);
            } else{
                return "Você deve mover para uma pasta";
            }
        } else{
            return "Mover para onde?";
        }
    } else {
        return "Escreva o nome 'para' para dizer onde quer mover";
    }
    return "Tente de novo";
}

std::string ls() {
    std::string d;
    char* path = new char[1000];
    getcwd(path, 1000);
    DIR *dir;
    struct dirent *drnt;
    dir = opendir(path);
    if(dir != NULL) {
        drnt = readdir(dir);
        while(drnt != NULL)  {
            d += drnt->d_name;
            d += "\n";
            drnt = readdir(dir);
        }
    }
    delete [] path;
    closedir(dir);
    return d;
}
