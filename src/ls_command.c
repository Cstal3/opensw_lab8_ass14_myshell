#include <dirent.h>
#include <stdio.h>
#include <sys/types.h>

#include "ls_command.h"

void my_ls(void){
    DIR *dir;
    struct dirent *entry;

    dir = opendir("."); // 현재 디렉토리만 보기위해.
    if(dir==NULL){
        perror("opendir");
        return;
    } else{
        while((entry = readdir(dir)) != NULL){ // 파일 이름을 계속 받아옴.
            if(entry->d_type == DT_DIR){
                printf("%s/\n", entry->d_name);
            } else{
                printf("%s\n", entry->d_name);
            }
        }
    }
    closedir(dir);

}