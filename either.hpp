#ifndef GENETIC_LIB_CONTROL_FLOW_MONAD_EITHER_
#define GENETIC_LIB_CONTROL_FLOW_MONAD_EITHER_

// TODO: find out why namespace std fails
// using namespace std; 

#include <iostream>

template <class A, class B>
class either
{
  private:
    const A *element1 = nullptr;
    const B *element2 = nullptr;

    bool is_array = false;

    void stop() {
        while (1) { }
    } // forces the compiler to stop from executing any further
    
    void error(std::string str) {
        str = "Runtime Error: [ " + str + " ]";
        std::cout << str << std::endl;

        stop();
    }

  public: 

    either(A element) {
        element1 = element;
        element2 = nullptr;
    }

    either(B element) {
        element2 = element;
        element1 = nullptr;
    }
    ~either() {
        delete element1;
        delete element2;
    }

    // operators

    void operator=(A element) {
        element1 = element;
        element2 = nullptr;
    }

    void operator=(B element) {
        element2 = element;
        element1 = nullptr;
    }

    // methods

    // template<class T> 
    // T getValue() {

    // }

    // void stream() { // find fist class functions in c++
    //     A temp = this->element1 == nullptr ? this->element2 : this->element1;

    //     if(temp != nullptr) {
    //         // do some operation that does not require the value to be returned
    //     }
    // }

    // template<class T>
    // auto stream() { // find fist class functions in c++
    //     auto temp = this->element1 == nullptr ? this->element2 : this->element1;

    //     if(temp != nullptr) {
    //         // do some operation that does not require the value to be returned
    //     }
    // }

    // TODO: create error codes and error description
    // A getValue()
    // {
    //     if (element1 != nullptr)
    //         return (*element1);
    //     else {
    //         return (A*)::operator new(1);
    //     }
    // }


    // B getValue() {
    //     if (element2 != nullptr)
    //         return (*element2);
    //     else {
    //         return (B*)::operator new(1);
    //     }
    // }
};

#endif