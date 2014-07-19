#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>  //包含了Linux C 中的函数getcwd()
#define FILEPATH_MAX (80)
int main(){
    char *file_path_getcwd;
    file_path_getcwd=(char *)malloc(FILEPATH_MAX);
    getcwd(file_path_getcwd,FILEPATH_MAX);
    printf("%s",file_path_getcwd);
}


