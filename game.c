#include "tq.h"
#include <stdio.h>
#include <stdlib.h>

int main(){
    TQDecisionTree* popo = TQ_build_tree("tq.txt");
    TQ_print_tree(popo);
    printf("\n");
    TQ_populate_tree(popo, "tq.txt");
    TQ_print_tree(popo);
    TQ_free_tree(popo);
    return 0;
}