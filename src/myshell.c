#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "ls_command.h"

#define MAX_LINE 80
#define MAX_ARGS 10

int main()
{
    char input[MAX_LINE];
    char *token;
    char *argv[MAX_ARGS];

    while(1){

        //prompt
        printf("myshell> ");

        //read command
        fgets(input, MAX_LINE, stdin);
        // printf("%s\n", input);

        // tokenize input
        token = strtok(input, " \n\t");
        int i = 0;
        while (token != NULL){
            argv[i++]=token;
            token = strtok(NULL, " \n\t");
        }
        argv[i] = NULL; // 제일 끝에는 더 이상 값이 없음을 표현하기 위해 NULL로 표시.

        if(argv[0] == NULL){ // empty command
            continue;
        }

        if(strcmp(argv[0], "exit") == 0){
            printf("Goodbye~\n");
            exit(0);
        }else if (strcmp(argv[0], "cd") == 0){
            chdir(argv[1]);
        }else if (strcmp(argv[0], "pwd") == 0){
            getcwd(input, MAX_LINE);
            printf("%s\n", input);
        }else if(strcmp(argv[0], "ls") == 0){
            my_ls();
        } else if(strcmp(argv[0], "cat") == 0){
            // your code comes here...
            if (argv[1] == NULL) {
                printf("cat: missing operand\n");
            } else {
                FILE *file = fopen(argv[1], "r");
                if (file == NULL) {
                    perror("cat");
                } else {
                    char line[MAX_LINE];
                    while (fgets(line, sizeof(line), file) != NULL) {
                        printf("%s", line);
                    }
                    fclose(file);
                }
            }
        } else {
            if(access(argv[0], X_OK) == 0){
                printf("execute %s\n", argv[0]);
            }else{
                printf("command not found: %s\n", argv[0]);
            }
        }

    }

    return 0;
}