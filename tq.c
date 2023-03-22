#include "tq.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//second
void TQ_print_tree(TQDecisionTree* root)
{
}

/// @brief 
/// @param str 
/// @return 
int count_questions(char* str){
    int index = 0;
    int count = 0;
    while(str[index] != '\0'){
        if (str[index] == '?'){
            count++;
        }
        index++;
    }
    return count;
}

/*
/// @brief splits a string depending on delimitter
/// @param line 
/// @param splitter 
*/
void split(char* string, char splitter, char** sub_strings, int* number_words){
    int length = 0;
    int start = 0;

    //iterate through string
    for (int i = 0; i <= strlen(string); i++) {
        //look for delimiter or end of string
        if (string[i] == splitter || string[i] == '\0') {
            //size of string before the curr space
            int size = i - start;
            //iterate at the start till the next delimitter
            for (int j = 0; j < size; j++) {
                sub_strings[length][j] = string[start + j];
            }
            //append null string at the end
            sub_strings[length][size] = '\0';
            length++;
            start = i + 1;
        }
    }
    *number_words = length;
}

//first
TQDecisionTree* TQ_build_tree(char* file_name)
{
    FILE* file = fopen(file_name, "r");

    char buffer[128];
    int index = 0;
    while(fgets(buffer, 128, file) != NULL){
        //num items
        if (index == 0){
            int shit = atoi(buffer);
            printf("%d\n", shit);
        }
        //questions
        else if (index == 1){
            int num_questions = count_questions(buffer);
            char **arr = (char**) calloc(num_questions, sizeof(char*));
            for (int i = 0; i < num_questions; i++ )
            {
                arr[i] = (char*) calloc(50, sizeof(char));
            }
            printf("%d\n", num_questions);
            int num_questions2;
            split(buffer, ',', arr, &num_questions2);
            printf("%s\n", *arr);
        }
        index++;
    }
    return NULL;
}

//third
void TQ_populate_tree(TQDecisionTree* tree, char* file_name)
{
}

//fourth
void TQ_free_tree(TQDecisionTree* tree)
{
}
