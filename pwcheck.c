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
#define help "--help"
#define stats "--stats"

enum ERRORS {
    PWD_LEN_ERROR = 1,
    ARGS_NUM_ERROR = 1,
    ARG_ERROR = 1
};

void showHelp(const char *argv){
    printf("Correct execution syntax is:\n%s --help\nor\n%s LEVEL PARAM [--stats]\n",argv,argv);
    printf("Where:\n--------\nLEVEL is an integer in the interval [1, 4] that specifies the required security level\n--------\n");
    printf("PARAM is a positive integer that specifies an additional rule parameter\n--------\n");
    printf("--stats (optional) determines whether summary statistics of the analyzed passwords should be displayed at the end of the program\n--------\n");
}

bool compareStr(char *str, char *arg){
    while (*str != '\0' || *arg != '\0')
    {
        if ((*str != *arg) || ((*str == '\0') && (*arg != '\0')) || ((*str != '\0') && (*arg == '\0')))
        {
            return false;
        } else if (*str == *arg)
        {
            str++;
            arg++;
        }
    }
    return true;
}

bool callHelp(int argc, char **argv){
    return ((argc == 2) && compareStr(argv[1], help));
}

bool statsEn(char **argv){
    if (compareStr(stats, argv[3]) == 1)
    {
        return true;
    } else 
    { 
        return false; 
    }
}

bool checkInt(char *arg){
    if (*arg >= '0' && *arg <= '9')
    {
        printf("Argument %s is fine\n", arg);
        return true;
    } else 
    {
        printf("Argument %s has to be a positive integer\n", arg);
        return false;
    }
}

bool checkArgs(int argc, char **argv){
    if (argc > 4 || argc < 3) 
    {
        printf("Something went wrong with arguments! Type %s --help for help\n", argv[0]);
        return false;        
    } else if (argc == 4 && checkInt(argv[1]) && checkInt(argv[2]) && statsEn(argv))
    {
        return true;        
    } else if (argc == 3 && checkInt(argv[1]) && checkInt(argv[2]))
    {
        return true;
    }
    return true;
}



int main(int argc, char **argv){

    printf("number of arguments: %d\n", argc);

    if (callHelp(argc, argv))
    {
        showHelp(argv[0]);
    } else if (checkArgs(argc, argv))
    {
        return 0;
    }
       
    return 0;

}