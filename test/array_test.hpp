#ifndef TEST
#define TEST

// #include <src/data_structures/containers/array.hpp>
#include "../array.hpp"

int main() {

    array<int> container;
    container.add(1);
    container.add(2);
    container.add(3);

    for(int i=0; i < container.size(); i++) {
        std::cout << std::to_string(container.get(i)) << std::endl;
    }
    return 0;
}


#endif