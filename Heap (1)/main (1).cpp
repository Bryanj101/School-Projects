#include <iostream>
#include "Heap.h"







int main() {
    Heap heap;
    //Process arr[2] = {{"p1", 1, 2, 3}, {"p2", 2, 2, 3}};
    Schedule({"p1", 2, 0, 3, 1});
    Schedule({"p2", 2, 2, 3, 4});
    heap.add(sched[0]);
    heap.add(sched[0]);
    /*heap.add(50);
    heap.add(30);
    heap.add(12);
    heap.add(9); */
    //heap.buildHeap(sched, sched.size());
    //Process tmp;
    //heap.remove(tmp);
    //heap.remove(tmp);
    /*for (int i = 0; i < 1; i++) {
        std::cout << tmp.name << '\t';
        std::cout << tmp.priority << '\t';
        std::cout << tmp.arrives << '\t';
        std::cout << tmp.length << '\t';
        std::cout << tmp.elapsed_time << '\t';
        std::cout << '\n';
    }*/
    heap.display(std::cout);
    //heap.remove();
    return 0;
}
