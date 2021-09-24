                                        /*
                                        -----------------------------------
                                        BUT FIT 2021/2022, winter semester 
                                        Introduction to Programming Systems
                                        Project #1 (password check)
                                        
                                        Author: Alina Vinogradova
                                        E-mail: xvinog00@stud.fit.vutbr.cz
                                        -----------------------------------
                                                                         */

// #TODO: дописать обработку уникальных символов

// #define  _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_PWD_LEN 100
#define MAX_UNIQUE_SYMBOLS 94 //ASCII TABLE 33-126
#define empty ""
#define help "--help"
#define stats "--stats"

enum ERRORS {
    PWD_LEN_ERROR = 1,
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

int lengthStr(char str[MAX_PWD_LEN]){
    int i = 0;
    for (i = 0; str[i] != '\0' && str[i] != '\n'; ++i);
    for (int n = 0; str[n] != '\0'; n++)
    {
        if (str[n] == '\n')
        {
            i--;
        }
    }
    return i;
}

bool helpEn(int argc, char **argv){
    return ((argc == 2) && compareStr(argv[1], help));
}

bool statsEn(int argc, char **argv){
    for (int i = 0; i < argc; ++i)
    {
        if (compareStr(argv[i], stats))
        {
            return true;
        }
    }
    return false;
}


bool checkInt(char *arg){
    return (*arg >= '0' && *arg <= '9') ? true : false;
}

bool checkArgs(int argc, char **argv){
    for (int i = 1; i < argc-1; i++)
    {
        if (argc == 4 && checkInt(argv[i]) && checkInt(argv[i+1]) && statsEn(argc, argv)) 
            return true;
        else if (argc == 3 && checkInt(argv[i]) && checkInt(argv[i+1])) 
            return true;
    }
    return false;
}

bool areLetters(char str[MAX_PWD_LEN]){
    int flagB, flagS;
    for (int i = 0; i < lengthStr(str); ++i)
    {
        if (str[i] >= 65 && str[i] <= 90 )
        {
            flagB = 1;
        }
        else if (str[i] >= 97 && str[i] <= 122)
        {
            flagS = 1;
        }
    }
    
    return (flagB == 1 && flagS == 1) ? true : false;
}

int minLength(char str[MAX_PWD_LEN], int seen){
    int currentMin = lengthStr(str);
    return (currentMin <= seen) ? currentMin : seen;
}

int charsCount(char str[MAX_PWD_LEN]){
    int seen[MAX_UNIQUE_SYMBOLS] = {0};
    int n = 0;

    for (int i = 0; i < lengthStr(str); ++i)
    {   
        if (str[i] != '\0' && str[i] != '\n' && str[i] != 1)
        {
            printf("str[i] is %d ", str[i]);
            seen[(int)str[i]] = 1;
            printf("seen[(int)str[i]] is %d\n", seen[(int)str[i]]);
        }
    }

    
    for (int i = 0; i < MAX_UNIQUE_SYMBOLS; ++i)
    {   
        //char letter = seen[i];
        // printf("seen[i] is '%d' ", seen[i]);
        // printf("n is '%d'\n", seen[i]);
        n += seen[i];
    }

    printf("n after password %s is %d\n", str, n);    
    return n;
}

// void showStats(int chars, int min, int avg){

// }

// void inputProcessing(){

// }

int main(int argc, char **argv){

    char password[MAX_PWD_LEN];
    int min = lengthStr(fgets(password, MAX_PWD_LEN, stdin));
    rewind(stdin);
    float count = 0;
    float avg;
    float sum = 0;
    int chars;

    if (helpEn(argc, argv))
    {
        showHelp(argv[0]);
        return 0;
    } else if (checkArgs(argc, argv))
    {   
        while(fgets(password, MAX_PWD_LEN, stdin))
        {
            ++count;
            min = minLength(password, min);
            sum += lengthStr(password);
            avg = sum/count;
            chars = charsCount(password);
            printf("%s", password);
        }
        printf("\n");
        
        if (statsEn(argc, argv))
        {
            
            printf("Count: %.1f\n", count);
            printf("Sum: %.1f\n", sum);
            printf("Unique chars: %d\n", chars);
            printf("Minimum length: %d\n", min);
            printf("Average length: %.1f\n", avg);
        }
 
        return 0;
    } else if (!checkArgs(argc, argv))
    {
        printf("Something went wrong with arguments! Try %s --help for help\n", argv[0]); 
        return ARG_ERROR;
    }
    
    return 0;
}