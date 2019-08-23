#ifndef GENETIC_LIB_CONTAINER_ARRAY_H_
#define GENETIC_LIB_CONTAINER_ARRAY_H_

// custom libraries
// #include "../control_flow/tuple.hpp"

// c/c++ standard libraries
#include <stdint.h>
#include <string>
#include <iostream>


/*
    Array class
    this class emulates arrays as lists, to simplify insertion, lookup and storage of bits in arduino microcontrollers
*/
// TODO: fix ambiguous call to array contructor, as it fails to compile at runtime.
template<class T>
class array {
        T* memory_chunk = nullptr;
        int last_value = -1;
        size_t initial_length = 0;

        // void stop() { while(1) {} } // forces and stops the compiler from executing the script 
        void error (std::string message) {
            std::cerr << ("Runtime Error: [ " + (message) + " ]") << std::endl;
        }
        
        // TODO: Sector Search -> Not working so far, will look for solutions to sector split problem
        // Tuple<int, int> split_by_sectors(int length) {
        //     const int total_sectors = length / (length % 10); 
        //     Tuple<int, int> sectors;
        //     Tuple<int, int> current_sectors;
                
        //     for(int iSector = 0; iSector < total_sectors; ++iSector) {
        //         if(iSector == 0) {
        //             sectors.add_param1(0);
        //             sectors.add_param2(iSector + (int)(length % 10));
        //         }
        //         else {
        //             sectors.add_param1(sectors.get_param1(iSector - 1) + 1);
        //             sectors.add_param2(sectors.get_param2(iSector) + (int)(length % 10));
        //         }
        //     }

        //     return sectors;
        // }

        bool isSorted(T array[], T array2[]) {
            if(sizeof(array) < sizeof(array2)) return false;
            else {
                int length = sizeof(array);
                for(int iElem = 0; iElem < length; ++iElem)
                    if(array[iElem] == array2[iElem]) continue;
                    else return false;
            }
            return true;
        }

        bool binary_search(T* container, T value, int min, int max) {
            const int mid = (min + max) / 2;
            const T& sorted_collection = sort(container, container+(sizeof(container)));
            container = !this->isSorted(container, sorted_collection) ? sorted_collection : container;

            if(max < min) return -1;
            else if(value > container[mid]) return binary_search(container, value, min, max );
            else if(value < container[mid]) return binary_search(container, value, mid - 1, max);
            else if(value == container[mid]) return mid;
            else return -1;
        }

    public:
        T get(int index) {
            if(index >= 0 && index < last_value) return memory_chunk[index];
            else {
                error("No such index : [" + std::to_string(index) + "], List length: [" + std::to_string(last_value) +"]");
                return T();
            }
        }

        void add(T value, int index=-1) {
            if(index != -1) {
                memory_chunk[index] = value;
            } else {
                memory_chunk[++last_value] = value;
            }
        }

        void remove(int index) {
            if(index > 0 && index < last_value) {
                // TODO: figure out whether to allocate memory in the stack or the heap
                T* temp = new T[(size_t)last_value];

                // approach below requires manual dealocation of memory in destructor C style
                // e.g.: free(memory_chunk) etc...
                // T* temp = new (std::nothrow [last_value-1);
                
                int count = 0; 
                for(int aIndex = 0; aIndex < last_value; ++aIndex) {
                    if(aIndex == index) continue;
                    else temp[count++] = memory_chunk[aIndex];
                }
                delete[] memory_chunk;
                memory_chunk = temp;
                last_value = count;
            } else error("Invalid index");
        }

        // checks the container for the specific value and indexof looks for the index of the specific value
        // this helps reduce code base if inserted at the root structure
        bool contains(T value) {
            return binary_search(memory_chunk, value, 0, last_value) != -1;
        }
        bool indexof(T value) {
            return binary_search(memory_chunk, value, 0, last_value); 
        }

        void remake(size_t new_size, T memory_chunk[]) {
            // create new array dynamically with new size
            T* new_memory_chunk = new T[new_size];
            
            // copy all elements to the new container
            for(int iValue = 0; iValue < sizeof(memory_chunk); ++iValue) { 
                if(memory_chunk[iValue] == 0 || memory_chunk[iValue] == nullptr)
                    continue;

                else new_memory_chunk[iValue] = memory_chunk[iValue];
            }

            // dispose of the old array
            delete[] memory_chunk;
            
            // point the old to the new array
            memory_chunk = new_memory_chunk;
        }
        
        // ============================================
        //  Operators
        // ============================================
        
        T operator [](int index) {
            if( index > 0 && index < last_value )
                return memory_chunk[index];
            else return nullptr;
        }
        
        //
        static void* operator new(size_t size) {
            return new (std::nothrow) T[size];
        }

        //
        static void* operator new[](size_t size, T container[]) {
            void* ptr = new (std::nothrow) T[size];
            
            if(ptr != NULL) {
                ptr = container;
            }
            return ptr;
        }

        
        // overloaded indexer operator and assignment operator
        void operator [](size_t length) { memory_chunk = new T[length]; }
        // TODO: amend this overloaded version of =, this cannot change the reference of the class for an instance of the same class
        // will have to set the properties manually
        void operator =(const array<T> array) { 
            this->initial_length = array.initial_length;
            this->last_value = array.last_value;
            this->memory_chunk = array.memory_chunk;
         }

        void operator =(T* container) {
            delete[] this->memory_chunk;
            this->memory_chunk = container;
        }
        
        // ============================================
        // Standard Array Methods
        // ============================================
        
        void truncate(bool add_elements, int count=0) {
            if(!add_elements) {
                delete[] memory_chunk;

                this->initial_length = (size_t)5;
                memory_chunk = new T[this->initial_length];
            } else {
                int element_count = 0;
                if(count == 0) {
                    element_count = 4;
                } else {
                    element_count = count;
                }

                T* temp = new (std::nothrow) T[(size_t)count];
                for(int index=0; index < count; ++index) {
                    temp[index] = memory_chunk[index];
                }
                
                delete[] memory_chunk;
                memory_chunk = temp;
            }
        }

        int size() { return last_value+1; }
        void dispose() {
            delete[] memory_chunk;
        }
        
        T* get_dynamic_array() { return memory_chunk; }
        void set_dynamic_array(T* array) { memory_chunk = array; }
        T& get_memory_address() { return &memory_chunk; }

        // Constructors & Destructor
        array() {
            this->initial_length = 5;
            this->memory_chunk = new (std::nothrow) T[this->initial_length];
        }
        array(size_t size) {
            this->initial_length = size; 
        }
        array(const array<T>& array) {
            this->memory_chunk = array.memory_chunk;
            this->last_value = array.last_value;
            this->initial_length = array.initial_length;
        }

        ~array() { this->dispose(); }
};

#endif
