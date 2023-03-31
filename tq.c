#include "tq.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int number_of_questions = 0;
int number_of_answers = 0;

/// @brief 
/// @param sentence 
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
    if (node == NULL || (node->yes == NULL && node->no == NULL)){
        return;
    }

    
    for (int i = 0; i < spaces; i++) {
        printf(" ");
    }
    printf("-y-> ");
    if (node->yes->num_answers == 0){
        printf("[");
        TQ_print_branch(node->yes->text);
        printf("]\n");
    }
    else if (node->yes->num_answers == -1){
        printf("\n");
    }
    else{
        printf("|");
        for (int i = 0; i < node->yes->num_answers; i++){
            printf(" ");
            TQ_print_branch(node->yes->answers[i]);
            printf(" |");
        }
        printf("\n");
    }
    TQ_print_tree_helper(node->yes, spaces + 4);

    for (int i = 0; i < spaces; i++) {
        printf(" ");
    }
    printf("-n-> ");
    if (node->no->num_answers == 0){
        printf("[");
        TQ_print_branch(node->no->text);
        printf("]\n");
    }
    else if (node->no->num_answers == -1){
        printf("\n");
    }
    else{
        printf("|");
        for (int i = 0; i < node->no->num_answers; i++){
            printf(" ");
            TQ_print_branch(node->no->answers[i]);
            printf(" |");
        }
        printf("\n");
    }
    TQ_print_tree_helper(node->no, spaces + 4);
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

/// @brief 
/// @param node 
/// @param val 
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

/// @brief 
/// @param dt 
/// @param val 
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

void DT_insert_leafs(TQDecisionTreeNode* node){
    if (node->yes == NULL){
        TQDecisionTreeNode* yes_new_node = calloc(sizeof(TQDecisionTreeNode), 1);
        yes_new_node->num_answers = -1;
        node->yes = yes_new_node;

        TQDecisionTreeNode* no_new_node = calloc(sizeof(TQDecisionTreeNode), 1);
        no_new_node->num_answers = -1;
        node->no = no_new_node;
    }
    else{
        //insert right and left leafs
        DT_insert_leafs(node->yes);
        DT_insert_leafs(node->no);
    }
}

//first
TQDecisionTree* TQ_build_tree(char* file_name)
{
    FILE* file = fopen(file_name, "r");

    //file information
    char** questions = NULL;
    int num_questions = 0;

    //read in question into array
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

    TQDecisionTree* dt = calloc(sizeof(TQDecisionTree), 1);

    //populate tree
    for (int i = 0; i < num_questions; i++){
        DT_insert(dt, questions[i]);
    }
    DT_insert_leafs(dt->root);
    return dt;
}

/// @brief 
/// @param node 
/// @param path 
/// @param item 
/// @param num_questions 
/// @param index 
void DT_insert_answer_helper(TQDecisionTreeNode* node, char* path, char* item, int num_questions, int index, int num_answers){

    if (num_questions == 1){
        if (path[index] == '1'){
            if (node->yes->answers == NULL){
                //create new one, malloc answers, and add item.

                //allocate memory for each line that contains an answer
                char** items = (char**) calloc(num_answers, sizeof(char*));
                //each answer line will not be more than 128 chars
                for (int i = 0; i < num_answers; i++ )
                {
                    items[i] = (char*) calloc(128, sizeof(char));
                }
                strcpy(items[0], item);
                node->yes->num_answers = 1;
                node->yes->answers = items;
                
            }
            else{
                //just add item
                strcpy(node->yes->answers[node->yes->num_answers], item);
                node->yes->num_answers++;
            }
        }
        else{
            if (node->no->answers == NULL){
                //create new one, malloc answers, and add item.

                //allocate memory for each line that contains an answer
                char** items = (char**) calloc(num_answers, sizeof(char*));
                //each answer line will not be more than 128 chars
                for (int i = 0; i < num_answers; i++ )
                {
                    items[i] = (char*) calloc(128, sizeof(char));
                }
                strcpy(items[0], item);
                node->no->num_answers = 1;
                node->no->answers = items;
                
            }
            else{
                //just add item
                strcpy(node->no->answers[node->no->num_answers], item);
                node->no->num_answers++;
            }
        }
    }else{
        if (path[index] == '1'){
            DT_insert_answer_helper(node->yes, path, item, num_questions - 1, index + 2, num_answers);
        }
        else{
            DT_insert_answer_helper(node->no, path, item, num_questions - 1, index + 2, num_answers);
        }
    }
}

void DT_insert_answer(TQDecisionTree* tree, char* answer, int num_questions, int num_answers){
    char copy[128];
    strcpy(copy, answer);
    char* item = strtok(copy, ",");

    char* path = &(strchr(answer, ','))[1];
    DT_insert_answer_helper(tree->root, path, item, num_questions, 0, num_answers);
}

//third
void TQ_populate_tree(TQDecisionTree* tree, char* file_name)
{
    FILE* file = fopen(file_name, "r");

    //file information
    int num_answers = 0;
    char** answers = NULL;
    int num_questions = 0;

    char buffer[128];
    int answers_index = 0;
    int index = 0;
    while(fgets(buffer, 128, file) != NULL){
        if (index == 0){
            num_answers = atoi(buffer);
            number_of_answers = num_answers;
            
            //allocate memory for each line that contains an answer
            answers = (char**) calloc(num_answers, sizeof(char*));
            //each answer line will not be more than 128 chars
            for (int i = 0; i < num_answers; i++ )
            {
                answers[i] = (char*) calloc(128, sizeof(char));
            }
        }
        else if (index == 1){
            num_questions = count_questions(buffer);
            number_of_questions = num_questions;
        }
        else{
            strcpy(answers[answers_index], buffer);
            answers_index++;
        }
        index++;
    }
    fclose(file);

    //print answers array
    // printf("\n");
    // for (int i = 0; i < num_answers; i++){
    //     int j = 0;
    //     while (answers[i][j] != '\0'){
    //         if (answers[i][j] != '\n'){
    //             printf("%c", answers[i][j]);
    //         }
    //         j++;
    //     }
    //     printf("\n");
    // }
    for (int i = 0; i < num_answers; i++){
        DT_insert_answer(tree, answers[i], num_questions, num_answers);
    }

    //free
    for (int i = 0; i < num_answers; i++) {
        free(answers[i]);
    }
    free(answers);
}

void TQ_free_tree_helper(TQDecisionTreeNode* root){
    if (root == NULL){
        return;
    }
    TQ_free_tree_helper(root->no);
    TQ_free_tree_helper(root->yes);
    for (int i = 0; i < root->num_answers; i++) {
        free(root->answers[i]);
    }
    free(root->answers);
    free(root);
}

//fourth
void TQ_free_tree(TQDecisionTree* tree)
{
    if (tree == NULL){
        return;
    }
    TQ_free_tree_helper(tree->root);
}
