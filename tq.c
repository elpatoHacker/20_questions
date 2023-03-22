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
char** split(char* string, char splitter){
    //allocate space
    int number_questions = count_questions(string);
    char** sub_strings = (char**) calloc(number_questions, sizeof(char*));

    //each question will not be more than 50
    for (int i = 0; i < number_questions; i++ )
    {
        sub_strings[i] = (char*) calloc(50, sizeof(char));
    }
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
    return sub_strings;
}

TQDecisionTree* DT_create() { 
  TQDecisionTree* dt = calloc(sizeof(TQDecisionTree), 1);
  return dt;
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
            printf("number of items: %d\n", shit);
        }
        //questions
        else if (index == 1){
            char** questions = split(buffer, ',');
            int num_questions = strlen(buffer);
            printf("number of questions: %d\n", num_questions);
            printf("first question: %s\n", questions[0]);
        }
        //finished reading important info
        else if (index == 2){
            break;
        }
        index++;
    }
    fclose(file);

    TQDecisionTree* dt = DT_create();
    //for elemnts in questions, create a new node, insert
    return dt;
}

//third
void TQ_populate_tree(TQDecisionTree* tree, char* file_name)
{
}

//fourth
void TQ_free_tree(TQDecisionTree* tree)
{
}
