                                        /*
                                        -----------------------------------
                                        BUT FIT 2021/2022, winter semester 
                                        Introduction to Programming Systems
                                        Project #1 (password check)
                                        
                                        Author: Alina Vinogradova
                                        E-mail: xvinog00@stud.fit.vutbr.cz
                                        -----------------------------------
                                                                         */

// #TODO: доделать функцию concatStr, разобраться с нулевым чаром (71 строка вызывает segfault)

#define  _GNU_SOURCE
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

int lengthStr(char *str){
    int i;
    for (i = 0; str[i] != '\0'; i++);
    return i;
}

char *copyStr(char *src, char *dst){
    int i;
    for (i = 0; src[i] != '\0'; i++)
    {
        dst[i] = src[i];
    }
    dst[i] = '\0';
    return dst;    
}

char *concatStr(char *dst, char *src){
    printf("this is string1: %s\n", dst);
    printf("this is string2 %s\n", src);
    int i;
    //for (i = 0; dst[i] != '\0'; i++);
    i = 10;
    puts("HELLOOOOOOO");
    for (int j = 0; src[j] != '\0'; j++, i++)
    {
        if (src[j] == '\n')
        {
            src[j] = ' ';
            j++;
            dst[i] = src[j];
        } else
        {
            dst[i] = src[j];
        }
    }

    return dst;
}

bool callHelp(int argc, char **argv){
    return ((argc == 2) && compareStr(argv[1], help));
}

bool statsEn(char **argv){
    if (compareStr(stats, argv[3]))
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
        return true;
    } else 
    {
        printf("Argument %s has to be a positive integer!\n", arg);
        return false;
    }
}

bool checkArgs(int argc, char **argv){
    if (argc > 4 || argc < 3) 
    {
        printf("Something went wrong with arguments! Try %s --help for help\n", argv[0]);
        return false;        
    } 
    else if (argc == 4 && checkInt(argv[1]) && checkInt(argv[2]) && statsEn(argv))
        return true; 
    else if (argc == 3 && checkInt(argv[1]) && checkInt(argv[2]))
        return true;
    else 
    { 
        printf("Something went wrong with arguments! Try %s --help for help\n", argv[0]); 
        return false;
    }
    return true;
}

int main(int argc, char **argv){

    if (callHelp(argc, argv))
    {
        showHelp(argv[0]);
    } else if (checkArgs(argc, argv))
    {   
        printf("Everything is working fine yet\n");
    }
    
    //char p1[10] = "hello";
    char *passwords[MAX_PWD_LEN*1000];

    //printf("p1 now is %s", p1);
    printf("passwords now is %s\n", *passwords);
    
    //copyStr(p1, *passwords);


    char str[MAX_PWD_LEN];

    while (fgets(str, MAX_PWD_LEN, stdin))
    {
        concatStr(*passwords, str);
        printf("%s", str);
    }

    // /* remove newline, if present */
    // i = lengthStr(str)-1;
    // if( str[ i ] == '\n')
    // str[i] = '\0';

    //printf("This is your string: %s\n", str);

    return 0;
}