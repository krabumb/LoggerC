#include "../include/logger.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdarg.h>

static void generate_time(char *time_string){
    time_t rawtime;
    struct tm * timeinfo;

    time(&rawtime);
    timeinfo = localtime(&rawtime);

    char *day = "[%d/";
    if (timeinfo->tm_mday < 10)
        day = "[0%d/";
    char *month = "%d/";
    if (timeinfo->tm_mon + 1 < 10)
        month = "0%d/";
    char *year = "%d";
    char *hour = " %d:";
    if (timeinfo->tm_hour < 10)
        hour = " 0%d:";
    char *minutes = "%d:";
    if (timeinfo->tm_min < 10)
        minutes = "0%d:";
    char *seconds = "%d]";
    if (timeinfo->tm_sec < 10)
        seconds = "0%d]";

    char concat[32] = "";
    strcat(concat,day);
    strcat(concat,month);
    strcat(concat,year);
    strcat(concat,hour);
    strcat(concat,minutes);
    strcat(concat,seconds);

    sprintf(time_string, concat, timeinfo->tm_mday,
            timeinfo->tm_mon + 1, timeinfo->tm_year + 1900,
            timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);
}

static void generate_pid(char *pid_string){
    // initiate pid
    pid_string[0] = '[';
    pid_string[8] = ']';
    pid_string[9] = '\0';
    for (int i = 1; i < 8; i++){
        pid_string[i] = '.';
    }
    int i_pid = getpid();
    int number_of_letter;
    if (i_pid < 10){
        number_of_letter = 1;
    } else if (i_pid < 100){
        number_of_letter = 2;
    } else if (i_pid < 1000){
        number_of_letter = 3;
    } else if (i_pid < 10000){
        number_of_letter = 4;
    } else if (i_pid < 100000){
        number_of_letter = 5;
    } else if (i_pid < 1000000){
        number_of_letter = 6;
    } else {
        number_of_letter = 7;
    }
    char str[number_of_letter+1];
    sprintf(str, "%d", i_pid);
    for (int i = 0; i < number_of_letter; i++){
        pid_string[i+1] = str[i];
    }
}

static void generate_card(char *card, int type){
    switch (type) {
        case INFO:
            strcpy(card,"[INFO.....]");
            break;
        case WARNING:
            strcpy(card,"[WARNING..]");
            break;
        case ERROR:
            strcpy(card,"[ERROR....]");
            break;
        case EXCEPTION:
            strcpy(card,"[EXCEPTION]");
            break;
        default:
            strcpy(card,"[INFO.....]");
    }
}

static void logger(const char *string_to_print, const char *card, const char *colorCard, va_list list){
    char * time = (char *) malloc(22*sizeof(time));
    generate_time(time);
    char * pid = (char *) malloc(10*sizeof(pid));
    generate_pid(pid);
    printf(GREEN "%s ", time);
    printf(MAGENTA "%s ", pid);
    printf("%s%s " RESET,colorCard,card);
    vprintf(string_to_print,list);
    printf("%c",'\n');
    free(time);
    free(pid);
}

void logger_info(const char *string_to_print, ...){
    char * card = (char *) malloc(12*sizeof(card));
    generate_card(card, INFO);
    va_list list;
    va_start(list,string_to_print);
    logger(string_to_print,card,CYAN,list);
    va_end(list);
    free(card);
}

void logger_warning(const char *string_to_print, ...){
    char * card = (char *) malloc(12*sizeof(card));
    generate_card(card, WARNING);
    va_list list;
    va_start(list,string_to_print);
    logger(string_to_print,card,YELLOW,list);
    va_end(list);
    free(card);
}

void logger_error(const char *string_to_print, ...){
    char * card = (char *) malloc(12*sizeof(card));
    generate_card(card, ERROR);
    va_list list;
    va_start(list,string_to_print);
    logger(string_to_print,card,RED,list);
    va_end(list);
    free(card);
}

void logger_exception(const char *string_to_print, int error_code, ...){
    char * card = (char *) malloc(12*sizeof(card));
    generate_card(card, EXCEPTION);
    va_list list;
    va_start(list,error_code);
    logger(string_to_print,card,RED,list);
    va_end(list);
    free(card);
    exit(error_code);
}

