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


#define  _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_PWD_LEN 100+1 // maximum length of a password is 100, a buffer for one password contains 2 extra positions for '\n' and '\0'
#define MAX_ARG_COUNT 4
#define help "--help"
#define statsWord "--stats"

enum ERRORS {
    PWD_LEN_ERROR = 1,
    ARG_ERROR = 1,
    ARG_AMOUNT_ERROR = 1,
    UNEXPECTED_ERROR = 1
};

typedef struct args_t {
    int level;
    int parameter;
    int stats;
    int flag;
} Args;

void showHelp(const char *argv){
    printf("Correct execution syntax is:\n%s LEVEL PARAM [--stats]\n",argv);
    printf("Where:\n------------------------------------------------------------------------------------------|\n");
    printf("LEVEL   | is an integer in the interval [1, 4] that specifies the required security level |\n");
    printf("------------------------------------------------------------------------------------------|\n");
    printf("PARAM   | is a positive integer that specifies an additional rule parameter \t\t  |\n");
    printf("------------------------------------------------------------------------------------------|\n");
    printf("--stats | (optional) determines whether summary statistics of the analyzed passwords\t  |\n \t| should be displayed at the end of the program\t\t\t\t\t  |\n");
    printf("------------------------------------------------------------------------------------------|\n");
}

int lengthStr(const char *str) { 
    // A function for calculating the length of a string.
    int n = 0;
    while (*str != '\0' && *str != '\n' && *str != '\r') {
        ++n;
        ++str;
    }
    return n;
}

bool compareStr(char *src, char *dst) {
    // A function for comparing strings.
    while (*src != '\0' || *dst != '\0') {
        if ((*src != *dst) || ((*src == '\0') && (*dst != '\0')) || ((*src != '\0') && (*dst == '\0'))) {
            return false;
        } else if (*src == *dst) {
            src++;
            dst++;
        }
    }
    return true;
}

bool isDigit(char str[MAX_PWD_LEN]) {
    // A function to check if string contains at least one digit 
    for (int i = 0; i < lengthStr(str); i++) {
        if (str[i] >= '0' && str[i] <= '9') {
            return true;
        }
    }
    return false;
}

bool areLetters(char str[MAX_PWD_LEN], int param) {
    /*
        A function to check if string contains either:
        - at least one small letter (param == 1)
        - at least one capital letter (param == 2)
        - at least one capital AND at leats one small (param == 4)
    */    
    int flagB, flagS;
    for (int i = 0; i < lengthStr(str); ++i) {
        if (param == 1 && str[i] >= 'a' && str[i] <= 'z')
            return true;
        else if (param == 2 && str[i] >= 'A' && str[i] <= 'Z')
            return true;
        else if (param == 3) {
            if (str[i] >= 'a' && str[i] <= 'z')
                flagS = 1;
            else if (str[i] >= 'A' && str[i] <= 'Z')
                flagB = 1;
        }
    }
    return flagB == 1 && flagS == 1;
}

int minLength(char str[MAX_PWD_LEN], int seen) {
    // A function to get minimum seen length of password
    int currentMin = lengthStr(str);
    return (currentMin <= seen) ? currentMin : seen;
}

int seenChars() {
    rewind(stdin);
    char password[MAX_PWD_LEN+1];
    int seen[126] = {0};
    int n = 0;
    // A func to collect each unique character into an array 
    while(fgets(password, MAX_PWD_LEN+1, stdin)) {
        for (int i = 0; i < lengthStr(password); ++i){   
            if (password[i] != '\0' && password[i] != '\n' && password[i] != 1) {
                seen[(int)password[i]] = 1;
                // seen[126] contains data about characters
                // for example: if there is a char "G" in password
                // seen[G] = 1
            }
        }
    }
    for (int i = 33; i < 126; ++i) {   
        n += seen[i];
        // Counting all the '1' in seen[]
        // i is in 33-126 cuz supported symbols are only from ASCII 33-126
    }
    rewind(stdin);
    return n;    
}

bool specialChars(char str[MAX_PWD_LEN]) {
    // A function to check if there is at least one special symbol (ASCII 33-126, NOT letters or digits)
    for (int i = 0; i < lengthStr(str); i++) {
        if ((str[i] >= 32 && str[i] <= 47) || (str[i] >= 58 && str[i] <= 64) || (str[i] >= 91 && str[i] <= 96) || (str[i] >= 123 && str[i] <= 126)) {
            return true;
        }
    }
    return false;
}

int argToInt(char argv[]) {
    // A function to make an integer from char argument 
    char *p;
    int argumentInteger = strtol(argv, &p, 10); 
    return argumentInteger;
}

bool firstLevel(char str[MAX_PWD_LEN]) { // Level 1
    return areLetters(str, 3);
}

bool secondLevel(char str[MAX_PWD_LEN], int param) { // Level 2
    if (firstLevel(str)) {
        if (param == 1 || param == 2) {
            return true;
        } else if (param == 3) {
            return isDigit(str) || specialChars(str);
        } else if (param >= 4) {
            return isDigit(str) && specialChars(str);
        } else return false;
    } else return false;
}

bool thirdLevel(char* str, int param) { // Level 3
    if (param == 1) return false;
    int counter = 1;
    if (secondLevel(str, param)) {
        while (*str != '\0') {
            char* curr = str;
            char* next = str+1;
            if (*curr == *next) {
                ++counter;
                if (counter == param) return false;
            }
            str++;
        }
        return true;
    } else return false;
}

bool fourthLevel(char* str, int param) { // Level 4
    if (thirdLevel(str, param)) {
        int counter = 0;
        while(*str != '\0') {
            char* curr = str;
            char* next = str+1;
            while(*next != '\0') {
                if(*curr == *next){
                    counter++;
                    curr++;
                } else {
                    counter = 0;
                }
                if(counter >= param)
                return false;
                next++;
            }
            str++;
        } return true;
    } else return false;
}

bool newLineCheck(const char *str) { // Checking if there is a new line symbol (using for output pwds)
    while (*str != '\0'){
        if (*str == '\n') return true;
        ++str;
    }
    return false;
}

void outPasswords(char* str) { // Deciding, should I print with \n or no (better looking output)
    if (newLineCheck(str)){
        printf("%s", str);
    } else printf("%s\n", str);
}

void selectPasswords(char str[MAX_PWD_LEN], int level, int param) { // 
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

Args collectArgs(int argc, char *argv[]){
    Args args;
    args.flag = 1, args.stats = 0;
    
    for (int i = 1; i < argc && args.flag != 0; ++i) { // argc is either 3 or 4, argv[0] is ./pwcheck
        if (argv[i][1] != 0 && argv[i][1] == '-' ) {
            if (compareStr(argv[i], statsWord)){
                args.stats = 1;
            } else args.stats = 2; // a case when argument "--stats" is incorrect
        } else {
            int j = 0;
            while (argv[i][j] != '\0'){
                if (argv[i][j] > '9' || argv[i][j] < '0') { // each symbol of param and level has to be an integer
                    args.flag = 0; 
                    break;
                }
                ++j;    
            }
        }
    }
    bool validLevel = argToInt(argv[1]) > 0 && argToInt(argv[1]) <= 4;
    bool validParameter = argToInt(argv[2]) > 0;
    if (validLevel && validParameter) {
        args.level = argToInt(argv[1]);
        args.parameter = argToInt(argv[2]);
    } else {
        args.flag = 0;
    }
    
    return args;
}

bool checkInput(char str[MAX_PWD_LEN]){
    return lengthStr(str) < MAX_PWD_LEN;
}

bool pwdProcessing(Args args){
    char password[MAX_PWD_LEN];
    int chars, min = 100;
    float count = 0, avg, sum = 0;

    if (args.stats == 1){
        while (fgets(password, MAX_PWD_LEN+1, stdin)){ // In fgets() MAX_PWD_LEN+1 to check if length of password is >100
            if (checkInput(password)) { // Collecting stats
                ++count;
                min = minLength(password, min);
                sum += lengthStr(password);
                avg = sum/count;
                selectPasswords(password, args.level, args.parameter);
            } else return false;
        }
        chars = seenChars();
        // printf("Statistika:\nRuznych znaku: %d\nMinimalni delka: %d\nPrumerna delka: %.1f\n", chars, min, avg);
        printf("Statistics:\nUnique chars: %d\nMinimum length: %d\nAverage length: %.1f\n", chars, min, avg);
    } else if (args.stats == 0){
        while(fgets(password, MAX_PWD_LEN+1, stdin)){
            if (checkInput(password)){
                selectPasswords(password, args.level, args.parameter);
            } else return false;
        }
    }
    return true;
}

int main(int argc, char *argv[]){
    int helpEnable = argc == 2 && compareStr(argv[1], help);
    if (argc == 1 || (argc == 2 && !helpEnable)){ 
        fprintf(stderr, "Wrong argument amount! Try %s --help for help\n", argv[0]);
        return ARG_AMOUNT_ERROR;
    } else if (helpEnable){ // A case to show help message
        showHelp(argv[0]);
        return EXIT_SUCCESS;
    } else {
        Args args = collectArgs(argc, argv); // Collecting and processing arguments, returning needed args.flag and args.stats
        int statsEnable = argc == 4 && args.stats == 1;
        if (args.flag == 0 || args.stats == 2){ // args.stats = 2 is the case when there is an argument that is simillar with "--stats" but is wrong
            fprintf(stderr, "Something went wrong with arguments! Try %s --help for help\n", argv[0]);
            return ARG_ERROR;
        } else if (statsEnable || argc == 3){
            if (!pwdProcessing(args)){ // pwdProcessing() can return false ONLY in case when password is too long
                fprintf(stderr, "Password is too long! Try %s --help for help\n", argv[0]);
                return PWD_LEN_ERROR;
            }
        } else if (argc < 3 || argc >= MAX_ARG_COUNT){
            fprintf(stderr, "Wrong argument amount! Try %s --help for help\n", argv[0]);
            return ARG_AMOUNT_ERROR;
        } else {
            fprintf(stderr, "Unexpected error! Try %s --help for help\n", argv[0]);
            return UNEXPECTED_ERROR;
        }
    }
    return EXIT_SUCCESS;
}