                                        /*
                                        -----------------------------------
                                        BUT FIT 2021/2022, winter semester 
                                        Introduction to Programming Systems
                                        Project #1 (password check)
                                        
                                        Author: Alina Vinogradova
                                        E-mail: xvinog00@stud.fit.vutbr.cz
                                        -----------------------------------
                                                                         */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_PWD_LEN 100

void showHelp(const char *argv){
    printf("Correct execution syntax is:\n%s --help\nor\n%s LEVEL PARAM [--stats]\n",argv,argv);
    printf("Where:\n--------\nLEVEL is an integer in the interval [1, 4] that specifies the required security level\n--------\n");
    printf("PARAM is a positive integer that specifies an additional rule parameter\n--------\n");
    printf("--stats (optional) determines whether summary statistics of the analyzed passwords should be displayed at the end of the program\n--------\n");
}

int compareStr(char *str, char *arg){
    int rescmp = 1;
    while(*str != '\0' || *arg != '\0'){
        if((*str != *arg) || ((*str == '\0') && (*arg != '\0')) || ((*str != '\0') && (*arg == '\0'))){
            rescmp = 0;
            break;
        } else if(*str == *arg){
            str++;
            arg++;
            rescmp = 1;
        }
    }
    return rescmp;
}

int main(int argc, char **argv){
    char help[] = "--help";
    if((argc == 1) || (compareStr(argv[1], help) == 1)){
        showHelp(argv[0]);
    }
    return 0;
}