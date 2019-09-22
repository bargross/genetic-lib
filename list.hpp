#ifndef GENETIC_LIB_CONTAINER_LIST_H_
#define GENETIC_LIB_CONTAINER_LIST_H_

#include "./array.hpp"
// #include "../control_flow/tuple.hpp"
#include "types.hpp"

template <class T>
class list {
    int parameters = 0;

    const int roulette[2];
    sound sound;
    parent_a sound_a;
    parent_b sound_b;
    parent_id parent_id;

    bool is_same_container(const T original[], const array<T> n_structure) {
        int original_size = this->size_of(original);
        if (original_size == n_structure.size()) {
            for (int index = 0; index < n_structure.size(); ++index) {
                if (original[index] != n_structure[index])
                    return false;
            }
            return true;
        } 
        return false;
    }

    // a check for array length, checks if the length of both match
    array<T> equalise_containers(const T original[], const array<T> n_structure) {
        int size = sizeof(original);
        if (size > n_structure.size() && is_same_container(original, n_structure)) {
            // if the length of the struct does not match the array, remake it
            remake(size, n_structure, 0);
        }

        return n_structure;
    }
    
    array<T> equalise_containers(const array<T> original, const array<T> n_structure) {
        int size = sizeof(original);
        if (size > n_structure.size() && is_same_container(original, n_structure)) {
            // if the length of the struct does not match the array, remake it
            remake(size, n_structure, 0);
        }

        return n_structure;
    }

    // binds values 
    void bind_values(const T container[], const array<T> original) {
        for (int index = 0; index < this->size_of(container); ++index)
            original.add(original[index], index);
    }

    void error(std::string str) {
        std::cerr << "Runtime Error: [ " + str + " ]" << std::endl;
    }

        // dispose for ~Array() destructor

    int size_of(T container[]) {
        return sizeof(container)/sizeof(*container);
    }

  public:

    void remakeAll(size_t new_size) {
        parent_id.resize(new_size);
        sound.resize(new_size);
        sound_a.resize(new_size);
        sound_b.resize(new_size);
    }

    //////////////////////////////////////////////////////

    //	Getters
    //----------------------------
    int get_sound_a() { return sound_a.get_dynamic_array(); }
    int get_sound_b() { return sound_b.get_dynamic_array(); }
    int get_parent_id() { return parent_id.get_dynamic_array(); }
    long get_sound() { return sound.get_dynamic_array(); }

    int get_roulette_value(int index) {
        if (index >= 0 && index < 2)
            return roulette[index];

        return -1;
    }

    //	Setters
    //----------------------------------------------------------------------
    enum SOUND_TYPE { A, B };
    void set_sound(T sound, int index, SOUND_TYPE type) {
        if(index >= 0 && index <= this->parameters) {
            switch(type) {
                case A:
                    this->sound_a.add(sound, index);
                    break;
                case B:
                    this->sound_b.add(sound, index);
                    break;
            }
        }
    }
    
    int get_sound(T sound, int index, SOUND_TYPE type) {
        if(index >= 0 && index <= this->parameters) {
            switch(type) {
                case A:
                    return this->sound_a.get(index);
                    break;
                case B:
                    return this->sound_b.get(index);
                    break;
            }
        }
        return -1;
    }


    void set_sound_a(const int array_values[]) { this->bind_values(array_values, sound_a); }
    void set_sound_b(const int array_values[]) { this->bind_values(array_values, sound_b); }
    void set_parent_id(const int array_values[]) { this->bind_values(array_values, parent_id); }
    void set_sound_value(const long array_values[]) { this->bind_values(array_values, sound); }


    void set_roulette_value(const int index, int value) {
        if (index >= 0 && index < 2)
            this->roulette[index] = value;

        else
            error("Invalid index");
    }

    //////////////////////////////////////////////////////////////////////////

    // the follwoing function maps data to a specific array, it also
    // facilitates the move of data between these arrays
    enum ArrayType { PID, SNA, SNB, SN };
    void swap_containers(const T array[], const ArrayType type)
    {
        if (type > SNB || type < PID)
            error("Invalid crossover type!!");

        switch (type) {
            case PID: // Arduino equivalent 0
                parent_id = equalise_containers(array, parent_id);

                for (int i = 0; i < this->size_of(array); ++i)
                    parent_id.add(array[i], i);

            case SNA: // Arduino equivalent 1
                sound_a = equalise_containers(array, sound_a);
                for (int i = 0; i < this->size_of(array); ++i)
                    sound_a.add(array[i], i);

            case SNB: // Arduino equivalent 2
                sound_b = equalise_containers(array, sound_b);
                for (int i = 0; i < this->size_of(array); ++i)
                    sound_b.add(array[i], i); //.add(array[i]);

            case SN: // Arduino equivalent 3
                sound = equalise_containers(array, sound);
                for (int i = 0; i < this->size_of(array); ++i)
                    sound.add(array[i], i);
                    // sound.

            default:
                error("Invalid Selection");
        }
    }

    // helps find specific values in a specific array within the genetic sequence
    bool parentA_contains(T value) { return sound_a.contains(value); }
    bool parentB_contains(T value) { return sound_b.contains(value); }
    bool parent_ids_contains(T value) { return sound_b.contains(value); }
    bool sound_contains(T sound) { return sound.contains(sound); }

    //....
    int parentA_indexOf(T value) { return sound_a.contains(value); }
    int parentB_indexOf(T value) { return sound_b.contains(value); }
    int parent_ids_indexOf(T value) { return sound_b.contains(value); }
    int sound_indexOf(T sound) { return sound.contains(sound); }

    void dispose() {
        parent_id.dispose();
        sound_a.dispose();
        sound_b.dispose();
        sound.dispose();
    }

    list() {} // no passing of parameters on init required
    ~list() { this->dispose(); }

};

#endif
