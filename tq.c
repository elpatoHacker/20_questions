#include "tq.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void TQ_print_branch(char* sentence) {
    if (sentence == NULL){
        return;
    }
    
    int index = 0;
    while (sentence[index] != '\0'){
        if (sentence[index] != '\n'){
            printf("%c", sentence[index]);
        }
        index++;
    }
}

/// @brief 
/// @param node 
/// @param spaces 
void TQ_print_tree_helper(TQDecisionTreeNode* node, int spaces){
    //base case
    if (node == NULL){
        return;
    }

    if (node->text[0] == '\0'){
        for (int i = 0; i < spaces; i++) {
            printf(" "); // Print two spaces for each level of indentation
        }
        printf("-y->\n");
        for (int i = 0; i < spaces; i++) {
            printf(" "); // Print two spaces for each level of indentation
        }
        printf("-n->\n");
    }
    else{
        for (int i = 0; i < spaces; i++) {
            printf(" "); // Print two spaces for each level of indentation
        }
        printf("-y-> [");
        char* perro = node->yes->text;
        TQ_print_branch(perro);
        printf("]\n");
        TQ_print_tree_helper(node->yes, spaces + 4);

        for (int i = 0; i < spaces; i++) {
            printf(" "); // Print two spaces for each level of indentation
        }
        printf("-n-> [");
        TQ_print_branch(node->no->text);
        printf("]\n");
        TQ_print_tree_helper(node->no, spaces + 4);
    }
}

//second
void TQ_print_tree(TQDecisionTree* root)
{
    printf("[%s]\n", root->root->text);
    TQ_print_tree_helper(root->root, 0);
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

void DT_insert_helper(TQDecisionTreeNode* node, char* val) {
    if (node->yes != NULL) {
        DT_insert_helper(node->yes, val);
    } else {
        TQDecisionTreeNode* new_node = calloc(sizeof(TQDecisionTreeNode), 1);
        strcpy(new_node->text, val);
        new_node->num_answers = 0;
        new_node->answers = NULL;

        node->yes = new_node;
    }

    if (node->no != NULL) {
        DT_insert_helper(node->no, val);
    } else {
        TQDecisionTreeNode* new_node = calloc(sizeof(TQDecisionTreeNode), 1);
        strcpy(new_node->text, val);
        new_node->num_answers = 0;
        new_node->answers = NULL;

        node->no = new_node;
    }
    return;
}

void DT_insert(TQDecisionTree* dt, char* val) {
  if (dt->root == NULL) {
    TQDecisionTreeNode* new_node = calloc(sizeof(TQDecisionTreeNode), 1);
    strcpy(new_node->text, val);
    new_node->num_answers = 0;
    new_node->answers = NULL;

    //set root to the first node
    dt->root = new_node;
    return;
  }
  DT_insert_helper(dt->root, val);
}

//first
TQDecisionTree* TQ_build_tree(char* file_name)
{
    FILE* file = fopen(file_name, "r");

    //file information
    char** questions = NULL;
    int num_questions = 0;

    char buffer[128];
    int index = 0;
    while(fgets(buffer, 128, file) != NULL){
        //questions
        if (index == 1){
            questions = split(buffer, ',');
            num_questions = count_questions(buffer);
        }
        //finished reading important info
        else if (index == 2){
            break;
        }
        index++;
    }
    fclose(file);

    TQDecisionTree* dt = DT_create();

    //populate tree
    for (int i = 0; i < num_questions; i++){
        DT_insert(dt, questions[i]);
    }
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
