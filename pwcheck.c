                                        /*
                                        -----------------------------------
                                        BUT FIT 2021/2022, winter semester 
                                        Introduction to Programming Systems
                                        Project #1 (password check)
                                        
                                        Author: Alina Vinogradova
                                        E-mail: xvinog00@stud.fit.vutbr.cz
                                        -----------------------------------
                                                                         */

// gcc -std=c99 -Wall -Wextra -Werror pwcheck.c -o pwcheck


// #define  _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_PWD_LEN 100
#define MAX_ARG_COUNT 4 // including  argv[0] == ./filename
#define help "--help"
#define stats "--stats"

enum ERRORS {
    PWD_LEN_ERROR = 1,
    ARG_ERROR = 1,
    WRONG_LEVEL_VALUE = 1,
    WRONG_PARAM_VALUE = 1
};

void showHelp(const char *argv){
    printf("Correct execution syntax is:\n%s --help\nor\n%s LEVEL PARAM [--stats]\nor\n%s [-l LEVEL] [-p PARAM] [--stats]\n",argv,argv,argv);
    printf("Where:\n--------\nLEVEL is an integer in the interval [1, 4] that specifies the required security level\n--------\n");
    printf("PARAM is a positive integer that specifies an additional rule parameter\n--------\n");
    printf("--stats (optional) determines whether summary statistics of the analyzed passwords should be displayed at the end of the program\n--------\n");
}

int lengthStr(const char *str){
    int n = 0;
    while (*str != '\0' && *str != '\n' && *str != '\r'){
        ++n;
        ++str;
    }
    return n;
}

bool compareStr(char *src, char *dst){
    while (*src != '\0' || *dst != '\0'){
        if ((*src != *dst) || ((*src == '\0') && (*dst != '\0')) || ((*src != '\0') && (*dst == '\0'))){
            return false;
        } else if (*src == *dst){
            src++;
            dst++;
        }
    }
    return true;
}

bool statsEn(int argc, char **argv){
    for (int i = 0; i < argc; ++i){
        if (compareStr(argv[i], stats)){
            return true;
        }
    }
    return false;
}

bool isDigit(char str[MAX_PWD_LEN]){
    for (int i = 0; i < lengthStr(str); i++){
        if (str[i] >= '0' && str[i] <= '9'){
            return true;
        }
    }
    return false;
}

bool isArgDigit(char argv[]){
    int i = 0;
    for (; argv[i] != 0; ++i){
        if (argv[i] > '9' || argv[i] < '0') return false;
    }
    return true;
}

bool areLetters(char str[MAX_PWD_LEN], int param){
    int flagB, flagS;
    for (int i = 0; i < lengthStr(str); ++i){
        if (param == 1 && str[i] >= 'a' && str[i] <= 'z')
            return true;
        else if (param == 2 && str[i] >= 'A' && str[i] <= 'Z')
            return true;
        else if (param == 3){
            if (str[i] >= 'a' && str[i] <= 'z')
                flagS = 1;
            else if (str[i] >= 'A' && str[i] <= 'Z')
                flagB = 1;
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
    char password[MAX_PWD_LEN+1];
    int seen[126] = {0};
    int n = 0;
    while(fgets(password, MAX_PWD_LEN+1, stdin)){
        for (int i = 0; i < lengthStr(password); ++i){   
            if (password[i] != '\0' && password[i] != '\n' && password[i] != 1){
                seen[(int)password[i]] = 1;
            }
        }
    }
    for (int i = 33; i < 126; ++i){   
        n += seen[i];
    }
    return n;    
}

bool specialChars(char str[MAX_PWD_LEN]){
    for (int i = 0; i < lengthStr(str); i++){
        if ((str[i] >= 32 && str[i] <= 47) || (str[i] >= 58 && str[i] <= 64) || (str[i] >= 91 && str[i] <= 96) || (str[i] >= 123 && str[i] <= 126)){
            return true;
        }
    }
    return false;
}

int argToInt(char argv[1]){
    char *p;
    int argumentInteger = strtol(argv, &p, 10); 
    return argumentInteger;
}

bool checkArgs(int argc, char **argv){
    int lvlInt, paramInt;
    
    if (!isDigit(argv[1])){
        int opid;
        for (opid = 1; opid < argc && argv[opid][0] == '-'; ++opid){
            switch (argv[opid][1]){
            case 'l':
                if (argv[opid+1] == 0 || !isArgDigit(argv[opid+1])){
                    return false;
                } else {
                    lvlInt = argToInt(argv[opid+1]);
                    if (lvlInt <= 0 || lvlInt > 4){
                        return false;
                    }
                    ++opid;
                    break;
                }
            case 'p':
                if(argv[opid+1] == 0 || !isArgDigit(argv[opid+1])){
                    return false;
                } else {
                    paramInt = argToInt(argv[opid+1]);
                    if (paramInt < 0)
                    {
                        return false;
                    }
                    ++opid;
                    break;
                }
            default:
                if (compareStr(argv[opid], stats)){
                    continue;
                } else {
                    return false;
                }
                break;
            }
        }
    } else if (argc == 4) {
        if (statsEn(argc, argv))
        {
            lvlInt = argToInt(argv[1]);
            paramInt = argToInt(argv[2]);
        } else {
            for (int i = 1; i < argc && argv[i][0] == '-'; ++i){
                if (argv[i][1] == '-')
                {
                    return (compareStr(argv[i], stats)) ? true : false;
                }
            }
            return true;
        }
    } else {
        lvlInt = argToInt(argv[1]);
        paramInt = argToInt(argv[2]);
    }

    if ((lvlInt > 4 || lvlInt <= 0) || (paramInt < 0)) return false;
    else return true;   
}

bool firstLevel(char str[MAX_PWD_LEN]){
    if (areLetters(str, 3)){
        return true;
    }
    return false;
}

bool secondLevel(char str[MAX_PWD_LEN], int param){
    if (firstLevel(str)){
        if (param == 1 || param == 2){
            return true;
        } else if (param == 3){
            if(isDigit(str) || specialChars(str)) return true;
            else return false;
        } else if (param == 4){
            if (isDigit(str) && specialChars(str)) return true;
            else return false;
        } else return false;
    } else return false;
}

bool thirdLevel(char* str, int param){
    int counter = 1;
    if (secondLevel(str, param)){
        while (*str != '\0'){
            char* curr = str;
            char* next = str+1;
            if (*curr == *next){
                ++counter;
                if (counter == param) return false;
            }
            str++;
        }
        return true;
    } else return false;
}

bool fourthLevel(char* str, int param){    
    if (thirdLevel(str, param)){
        int counter = 0;
        while(*str != '\0'){

            char* curr = str;
            char* equals = str+1;

            while(*equals != '\0'){
                if(*curr == *equals){
                    counter++;
                    curr++;
                } else{
                    counter = 0;
                }

                if(counter >= param)
                return false;
                equals++;
            }
            str++;
        } return true;
    } else return false;
}

bool newLineCheck(const char *str){
    while (*str != '\0'){
        if (*str == '\n') return true;
        ++str;
    }
    return false;
}

void outPasswords(char* str){
    if (newLineCheck(str)){
        printf("%s", str);
    } else printf("%s\n", str);
}

void selectPasswords(char str[MAX_PWD_LEN], int level, int param){
    switch (level){
        case 1:
            if (firstLevel(str)){
                outPasswords(str);
            } 
            break;
        case 2:
            if (secondLevel(str, param)){
                outPasswords(str);
            }
            break;
        case 3:
            if (thirdLevel(str, param)){
                outPasswords(str);
            }
            break;
        case 4:
            if (fourthLevel(str, param)){
                outPasswords(str);
            }
            break;
    }
}

int pwdProcessing(int argc, char *argv[]){
    char password[MAX_PWD_LEN];
    int chars, intLevel = 0, intParameter = 0;
    float count = 0, avg, sum = 0;

    if (argc == 1)
    {
        intLevel = 1;
        intParameter = 1;
    }

    if (!isDigit(argv[1])){
        // int opid;
        for (int opid = 1; opid < argc && argv[opid][0] == '-'; ++opid){
            switch (argv[opid][1]){
            case 'l':
                intLevel = argToInt(argv[opid+1]);
                ++opid;
                break;
            case 'p':
                intParameter = argToInt(argv[opid+1]);
                ++opid;
                break;
            case '-':
                if (compareStr(argv[opid], stats)) //++opid;
                break;
            default:
                break;
            }
        }

        if (intLevel == 0 && intParameter == 0)
        {
            intLevel = 1;
            intParameter = 1;
        } else if (intLevel == 0){
            intLevel = 1;
        } else if (intParameter == 0){
            intParameter = 1;
        }
        
    } else {
        intLevel = argToInt(argv[1]);
        intParameter = argToInt(argv[2]);
    }
    
    int min = lengthStr(fgets(password, MAX_PWD_LEN, stdin));
    rewind(stdin);
    while(fgets(password, MAX_PWD_LEN+1, stdin)){
        if (lengthStr(password) > MAX_PWD_LEN)
        {
            fprintf(stderr, "Error! Max length of password has to be 100\n");
        }
        
        ++count;
        min = minLength(password, min);
        sum += lengthStr(password);
        avg = sum/count;
        selectPasswords(password, intLevel, intParameter);     
    }
    if (statsEn(argc, argv)){
        chars = seenChars();
        printf("Statistika:\nRuznych znaku: %d\nMinimalni delka: %d\nPrumerna delka: %.1f\n", chars, min, avg);
        // printf("Statistics:\nUnique chars: %d\nMinimum length: %d\nAverage length: %.1f\n", chars, min, avg);
    }

    return 0;
}

int main(int argc, char *argv[]){
    if ((argc == 2) && compareStr(argv[1], help)){
        showHelp(argv[0]);
        return 0;
    } else if (!checkArgs(argc, argv)) {
        fprintf(stderr, "Something went wrong with arguments! Try %s --help for help\n", argv[0]);
        return 1;
    } 
    else if (checkArgs(argc, argv)){
        pwdProcessing(argc, argv);
    }
    
    return 0;
}