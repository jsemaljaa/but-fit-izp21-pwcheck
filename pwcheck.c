                                        /*
                                        -----------------------------------
                                        BUT FIT 2021/2022, winter semester 
                                        Introduction to Programming Systems
                                        Project #1 (password check)
                                        
                                        Author: Alina Vinogradova
                                        E-mail: xvinog00@stud.fit.vutbr.cz
                                        -----------------------------------
                                                                         */


// #define  _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_PWD_LEN 100
#define empty ""
#define help "--help"
#define stats "--stats"
#define one "1"
#define two "2"

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

bool compareStr(char *src, char *dst){
    while (*src != '\0' || *dst != '\0')
    {
        if ((*src != *dst) || ((*src == '\0') && (*dst != '\0')) || ((*src != '\0') && (*dst == '\0')))
        {
            return false;
        } else if (*src == *dst)
        {
            src++;
            dst++;
        }
    }
    return true;
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

bool areIntegers(char str[MAX_PWD_LEN]){
    for (int i = 0; i < lengthStr(str); i++)
    {
        if (str[i] >= '0' && str[i] <= '9')
        {
            return true;
        }
    }
    return false;
}

bool checkArgs(int argc, char **argv){
    for (int i = 1; i < argc-1; i++)
    {
        if (argc == 4 && areIntegers(argv[i]) && areIntegers(argv[i+1]) && statsEn(argc, argv)) 
            return true;
        else if (argc == 3 && areIntegers(argv[i]) && areIntegers(argv[i+1])) 
            return true;
    }
    return false;
}

bool areLetters(char str[MAX_PWD_LEN], int param){
    int flagB, flagS;
    for (int i = 0; i < lengthStr(str); ++i)
    {
        if (param == 1)
        {
            if (str[i] >= 97 && str[i] <= 122)
            {
                return true;
            }
        } else if (param == 2)
        {
            if (str[i] >= 65 && str[i] <= 90 )
            {
                return true;
            }
        } else if (param == 3)
        {
            if (str[i] >= 97 && str[i] <= 122)
            {
                flagS = 1;
            }
            if (str[i] >= 65 && str[i] <= 90 )
            {
                flagB = 1;
            }
        }
    }
    return (flagB == 1 && flagS == 1) ? true : false;
}

int minLength(char str[MAX_PWD_LEN], int seen){
    int currentMin = lengthStr(str);
    return (currentMin <= seen) ? currentMin : seen;
}

int seenChars(){
    rewind(stdin);
    char password[MAX_PWD_LEN];
    int seen[126] = {0};
    int n = 0;
    while(fgets(password, MAX_PWD_LEN, stdin))
    {
        for (int i = 0; i < lengthStr(password); ++i)
        {   
            if (password[i] != '\0' && password[i] != '\n' && password[i] != 1)
            {
                seen[(int)password[i]] = 1;
            }
        }
    }
    for (int i = 33; i < 126; ++i)
    {   
        n += seen[i];
    }
    return n;    
}

int main(int argc, char **argv){

    char password[MAX_PWD_LEN];
    int min = lengthStr(fgets(password, MAX_PWD_LEN, stdin));
    rewind(stdin);
    float count = 0, avg, sum = 0;
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

            switch (*argv[1])
            {
                case '1':
                    if (areLetters(password, 3))
                    {
                        printf("%s", password);
                    } 
                    break;
                case '2':
                    switch (*argv[2])
                    {
                    case '1':
                        if (areLetters(password, 1))
                        {
                            printf("%s", password);
                        }
                        break;
                    case '2':
                        if (areLetters(password, 3))
                        {
                            /* code */
                        }
                        
                    
                    default:
                        break;
                    }
                    break;
                // case '3':
                //     lv;
                //     break;
                // case '4':
                //     lvl = 4;
                //     break;
                default: 
                    printf("Argument %s has to be an integer int interval [1,4]\n", argv[1]);
                    return 1;
            }     
        }
        
        printf("\n");
        if (statsEn(argc, argv))
        {
            chars = seenChars();
            printf("Statistics:\nUnique chars: %d\nMinimum length: %d\nAverage length: %.1f\n", chars, min, avg);
        }
 
        return 0;
    } else if (!checkArgs(argc, argv))
    {
        printf("Something went wrong with arguments! Try %s --help for help\n", argv[0]); 
        return ARG_ERROR;
    }
    
    return 0;
}