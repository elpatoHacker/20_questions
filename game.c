#include "tq.h"
#include <stdio.h>
#include <stdlib.h>

int main(){
    printf("hello world\n");
    TQDecisionTree* popo = TQ_build_tree("tq.txt");
    printf("%p", popo);
    return 0;
}