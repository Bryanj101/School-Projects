#include <iostream>
#include "Heap.h"


int main() {

    Heap prior;
    int priority[5] = {1, 2, 4, 9, 7,};
    //std::vector<int> v{1, 2, 3, 4, 5, 6, 7, 8 , 9, 10};
   /* heap.add(20);
    heap.add(50);
    heap.add(30);
    heap.add(12);
    heap.add(9); */
    prior.buildHeap(priority, 5);
    prior.display(std::cout);
    //heap.remove();
    return 0;
}
