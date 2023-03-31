#include "tq.h"
#include <stdio.h>
#include <stdlib.h>

int main(){
    TQDecisionTree* popo = TQ_build_tree("tq.txt");
    TQ_print_tree(popo);
    TQ_populate_tree(popo, "tq.txt");
    TQ_print_tree(popo);

    
    // printf("\n[%s]\n", (popo->root->text));
    // printf("-y-> [%s]\n", (popo->root->yes->text));
    // printf("    -y-> [%s]\n", (popo->root->yes->yes->text));
    // printf("        -y-> [%s", (popo->root->yes->yes->yes->text));
    // printf("        -n-> [%s", (popo->root->yes->yes->no->text));
    // printf("    -n-> [%s]\n", (popo->root->yes->no->text));
    // printf("        -y-> [%s", (popo->root->yes->no->yes->text));
    // printf("        -n-> [%s", (popo->root->yes->no->no->text));

    // printf("-n-> [%s]\n", (popo->root->no->text));
    // printf("    -y-> [%s]\n", (popo->root->no->yes->text));
    // printf("        -y-> [%s", (popo->root->no->yes->yes->text));
    // printf("        -n-> [%s", (popo->root->no->yes->no->text));
    // printf("    -n-> [%s]\n", (popo->root->no->no->text));
    return 0;
}