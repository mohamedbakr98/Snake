#include "input.h"
#include "major_functions.h"
#include <string.h>
#include <stdio.h>
char* GetName(char *buffer){
    int flag = 0;
    gets(buffer);
    int i = 0;
    while(buffer[i] != '\0'){
        if(buffer[i] < 65 || buffer[i] >122){
            flag = 1;
        }
        i++;
    }
    if(flag == 0){
        return buffer;
    }
    buffer[0] = '\0';
    return buffer;
}
void printUser(User data){
    printf("\tName: %s \n",data.name);
    printf("\tScore: %d\n",data.score);
}
void saveStudent(User data,FILE *database){
    fprintf(database,"Name: %s\n",data.name);
    fprintf(database,"Score: %d\n",data.score);
    fprintf(database,"----\n");
}
User UserConstructor(){
    User temp;
    char buffer[100];
    buffer[0] = '\0';
    while(buffer[0] == '\0'){
        printf("Enter your Name: \n");
        GetName(buffer);
    }
    strcpy(temp.name,buffer);
    buffer[0] = '\0';
    return temp;
}
