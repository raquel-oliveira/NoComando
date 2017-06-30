#include "util.h"

std::string help() {
    std::string s = "";
    s += "Aqui está a ajuda!<br>";
    s += "Os comandos disponíveis são:<br>";
    s += "  <span style='color: white'>ajuda</span><br>";
    s += "  <span style='color: white'>onde estou?</span><br>";
    s += "  <span style='color: white'>listar</span><br>";
    s += "  <span style='color: white'>entrar</span> NOME_DA_PASTA<br>";
    s += "  <span style='color: white'>renomear</span> NOME_ATUAL <span style='color: white'>para</span> NOVO_NOME<br>";
    s += "  <span style='color: white'>criar pasta</span> NOME_DA_PASTA<br>";
    s += "  <span style='color: white'>deletar</span> NOME<br>";
    s += "  <span style='color: white'>mover</span> NOME <span style='color: white'>para</span> NOME_DA_PASTA<br>";
    s += "  <span style='color: white'>repetir</span><br>";
    s += "  <span style='color: white'>sair</span><br>";
    return s;
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

std::string createDirectory(char** argv) {
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

std::string recursiveDeleteDirectory(const char* path) {
    char* newPath;
    DIR *dir;
    struct dirent *drnt;
    dir = opendir(path);
    if(dir != NULL) {
        drnt = readdir(dir);
        while(drnt != NULL)  {
            if(strcmp(drnt->d_name,".") != 0 && strcmp(drnt->d_name,"..") != 0) {
                newPath = new char[strlen(path) + strlen(drnt->d_name) + 2];
                strcpy(newPath, path);
                strcat(newPath, "/");
                strcat(newPath, drnt->d_name);
                struct stat st;
                if (!stat(newPath, &st)) {
                    if (S_ISDIR(st.st_mode)) {
                        std::string s = recursiveDeleteDirectory(newPath);
                        if(!s.empty())
                            return s;
                    }
                    else {
                        if(unlink(newPath) != 0)
                            return "Erro: não deletou arquivo/pasta.";
                    }
                }
                delete[] newPath;
            }
            drnt = readdir(dir);
        }
        closedir(dir);
    }
    if(rmdir(path))
        return "Erro: não deletou ";
    return "";
}

std::string deleteFileOrDirectory(char** argv) {
    if(argv[1] == NULL)
        return "Qual arquivo/pasta? Tente de novo.";
    else{
        char* path = new char[1000];
        getcwd(path, 1000);
        strcat(path, "/"); strcat(path, argv[1]);
        struct stat st;
        if (!stat(path, &st)) {
            if (S_ISDIR(st.st_mode))
                return recursiveDeleteDirectory(path);
            else {
                if(unlink(path) !=0 )
                    return "Erro: não deletou arquivo/pasta.";
                return "";
            }
        }
        else
            return "Erro no stat";
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
    return "";
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
            d += "<br>";
            drnt = readdir(dir);
        }
    }
    delete [] path;
    closedir(dir);
    return d;
}

double findMemValue(const char* buffer) {
    while((*buffer) && (!isdigit(*buffer)))
        buffer++;
    return isdigit(*buffer) ? atof(buffer) : -1.0;
}

std::string monitoring() {
    std::string s = "";
    FILE * file = popen("/usr/bin/vm_stat", "r");
    if (file) {
        double pagesUsed = 0.0, totalPages = 0.0, totalSwap = 0.0;
        char buffer[512];
        int i = 0;
        while(fgets(buffer, sizeof(buffer), file) != NULL) {
            if (strncmp(buffer, "Pages", 5) == 0 && i < 7) {
                double val = findMemValue(buffer);
                if (val >= 0.0) {
                    if ((strncmp(buffer, "Pages wired", 11) == 0)||(strncmp(buffer, "Pages active", 12) == 0)) {
                        pagesUsed += val;
                    }
                    totalPages += val;
                }
            }
            if (strncmp(buffer, "Swap", 4) == 0) {
                double val = findMemValue(buffer);
                totalSwap += val;
            }
            if (strncmp(buffer, "Swap", 4) == 0) {
                double val = findMemValue(buffer);
                totalSwap += val;
            }
            i++;
        }
        pclose(file);
        if (totalPages > 0.0) {
            s += "RAM utilizada no momento: ";
            s += std::to_string((float)(pagesUsed/totalPages));
            s += "%<br>";
            s += "Total de swaps: ";
            s += std::to_string(totalSwap);
            s += "<br>";
        }
    }
    return s;
}
