#include "tq.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
    if (argc != 2){
        printf("invalid number of parameters.");
        return 1;
    }
    TQDecisionTree* popo = TQ_build_tree(argv[1]);
    TQ_populate_tree(popo, argv[1]);

    TQ_free_tree(popo);
    return 0;
}