#ifndef TQ_H
#define TQ_H

typedef struct TQDecisionTreeNode {
    char text[50];
    int num_answers;
    char** answers;
    struct TQDecisionTreeNode* yes;
    struct TQDecisionTreeNode* no;
} TQDecisionTreeNode;

typedef struct TQDecisionTree {
    TQDecisionTreeNode* root;
} TQDecisionTree;

void TQ_print_tree(TQDecisionTree* root);

TQDecisionTree* TQ_build_tree(char* file_name);

void TQ_populate_tree(TQDecisionTree* tree, char* file_name);

void TQ_free_tree(TQDecisionTree* tree);

#endif