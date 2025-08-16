#include <stdio.h>
#include <time.h> // To use time funtion.
#include <unistd.h> // For the use of sleep function.
#include <stdlib.h> // For using cls cmd inside terminal.

void fill_time(char* buffer, size_t buffer_size,int users_choice);
void fill_date(char* buffer, size_t buffer_size);
int input_choice();
void clear_screen();

int main()
{
    char time[50],date[50];
    int users_choice = input_choice();
    
    while(1){
    fill_time(time, sizeof(time),users_choice);
    fill_date(date, sizeof(date));
    clear_screen();
    printf("Current Time: %s\n", time);
    printf("Date: %s\n", date);
    sleep(1);
    }

    return 0;
}

void clear_screen(){
    system("cls");
}

int input_choice(){
    int input_choice;
    printf("Which Format would you like to see the time in \n1. 24-Hour Format \n2. 12-Hour Format.(default)\nPlease seect your desired format(1/2):");
    scanf("%d",&input_choice);
    return input_choice;

}

void fill_date(char* buffer, size_t buffer_size){
    time_t raw_time;
    struct tm *current_time;

    time(&raw_time);
    current_time = localtime(&raw_time);
    strftime(buffer, buffer_size, "%A, %d %B %Y", current_time);
}

void fill_time(char* buffer, size_t buffer_size ,int users_choice){
    time_t raw_time;
    struct tm *current_time;

    time(&raw_time);
    current_time = localtime(&raw_time);
    if(users_choice == 1){
        strftime(buffer, buffer_size, "%H:%M:%S", current_time);
    }
    else{
        strftime(buffer, buffer_size, "%I:%M:%S %p", current_time);
    }
}