#ifndef GENETIC_LIB_CONTAINER_TUPLE
#define GENETIC_LIB_CONTAINER_TUPLE

#include <string>
#include <iostream>

// template<typename T>
// class Type {
    
// }

template<class A> 
class elem_filter {
            A* param1 = nullptr;
        size_t length = 1;

        bool is_null(A elem) { return elem != NULL || elem != 0; }
        bool are_elems_null(A elem1, A elem2) { return is_null(elem1) && is_null(elem2); }
        int find_next_index() {
            if(param1 != sizeof(param1) > 1) {
                for(int iParam= 0; iParam < sizeof(param1); ++iParam) {
                    if(param1[iParam] < 0) {
                        return iParam;
                    }
                }
            }
            else return -1;
        }

        int binary_search(A array, A elem, int32_t min, int32_t max, bool is_sorted) {
            int32_t mid = ((min+max) / 2);
            if(!is_sorted) sort(array, array+sizeof(array));
            if(max < min) return -1;
            else if (array[mid] < elem) return binary_search(array, elem, mid - 1, max, true);
            else if (array[mid] > elem) return binary_search(array, elem, min, mid + 1, true);
            else return mid;
        }

        void stop() { while(1) {} }

    public:
        elem_filter() {}
        elem_filter(A param) { 
            if(!is_null(param)) {
                param1 = &param;
            } else {
                //
                A* temp = (A*):: operator new(4);
                // assign it as the first element
                temp[0] = param1;
                // 
                delete param1;
                //
                param1 = temp;
                length = 4;
            }
        }

        ~elem_filter() {
            this->dispose();
        }

        // Functions
        //=========================================================
        
        void error (std::string str) {
            str = "Runtime Error: [ " + str + " ]";

            std::cout << str << std::endl;

            stop();
        }
        
        void print( std::string msg ) { // String[] message ) { 
            int length = sizeof(param1);
            if(length > 1) {
                for(int index = 0; index < length; ++index) {
                    prinf("Parameter1: %c", param1[index]);
                }
            } 
            
            else if( (length > 0) && !(length < 1) ) prinf("Parameter1: %c", param1);
            else print("NULLParameterException: [ %c", (msg != "" ? msg : "There are no item/s wihin this container") + " ]" );
        }

        void add(A item) {
            if(!is_null(item) && sizeof(param1) > 1) {
                const int allocate_at = find_next_index();
                if(allocate_at != -1)
                    param1[allocate_at] = item;
                    param1 = item;
                    this->length++;
             } else error("AllocationException: The element is not an Array!");
        }

        void replace(A item) {
            if(!is_null(item) && sizeof(param1) == 1) {
                param1 = &item;
            }
        }

        A get_param() { return *(param1); }
        
        bool contains_value(A value) {
            if(this->length > 1)
                return binary_search(param1, value, 0, this->length) != -1;
            else return value == param1;
        }

        int index_of(A value) {
            return binary_search(param1, value, 0, this->length);
        }
        // Operator/s
        //=========================================================

        void operator =(A* value) { param1 = value; }
        void dispose() {
            delete param1;
        }
};

template<class A, class B> 
class tuple {
        elem_filter<A> param1;
        elem_filter<B> param2;
    public:
        void add_param1(A param) { 
            param1.add(param); 
        }    
        void add_param2(B param) { 
            param2.add(param); 
        }

        // value extraction
        //=====================================================
        A get_param1(int index) {
            if(index == -1) return param1;
            else return param1.get_param(index);    
        }

        A get_param2(int index) {
            if(index == -1) return param2;
            else return param2.get_param(index);
        }

        void print() { 
            param1.print();
            param2.print(); 
        }

        void operator =(A param) { param1 = param; }
        void operator =(B param) { param2 = param; } 

        A operator [](bool param) { 
            return param ? param1.get_param1(0) : param2.get_param2(0); 
        }
        B operator [](int index) { 
            return param2.get_param2(index); 
        }

};

#endif