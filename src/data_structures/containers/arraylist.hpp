#ifndef GENETIC_LIB_CONTAINER_GENETIC_LIST_H_
#define GENETIC_LIB_CONTAINER_GENETIC_LIST_H_

#include "./array.hpp"
// #include "../control_flow/tuple.hpp"
#include "types.hpp"

template <class T>
class arraylist {
    int parameters = 0;

    const int roulette[2];
    Sounds sound;
    ParentA soundA;
    ParentB soundB;
    ParentId parentId;

    bool is_same_container(const T original[], const array<T> n_structure)
    {
        int original_size = this->size_of(original);
        if (original_size == n_structure.size())
        {
            for (int index = 0; index < n_structure.size(); ++index)
            {
                if (original[index] != n_structure[index])
                    return false;
            }
            return true;
        } 
        return false;
    }

    // a check for array length, checks if the length of both match
    array<T> equalise_containers(const T original[], const array<T> n_structure)
    {
        int size = sizeof(original);
        if (size > n_structure.size() && is_same_container(original, n_structure))
        {
            // if the length of the struct does not match the array, remake it
            remake(size, n_structure, 0);
        }

        return n_structure;
    }

    // binds values 
    void bind_values(const T container[], const array<T> original)
    {
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

    void remakeAll(size_t new_size)
    {
        parentId(new_size);
        sound(new_size);
        soundA(new_size);
        soundB(new_size);
    }

    //////////////////////////////////////////////////////

    //	Getters
    //----------------------------
    int *get_soundsa() { return soundA.get_array(); }
    int *get_soundsb() { return soundB.get_array(); }
    int *get_parentIds() { return parentId.get_array(); }
    long *get_sounds() { return sound.get_array(); }

    int get_roulette_value(int index)
    {
        if (index >= 0 && index < 2)
            return roulette[index];

        return -1;
    }

    //	Setters
    //----------------------------------------------------------------------
    void set_soundsa(const int array_values[]) { bind_values(array_values, soundA); }
    void set_soundsb(const int array_values[]) { bind_values(array_values, soundB); }
    void set_parentIds(const int array_values[]) { bind_values(array_values, parentId); }
    void set_sounds(const long array_values[]) { bind_values(array_values, sound); }
    void set_roulette_value(const int index, int value)
    {
        if (index >= 0 && index < 2)
            roulette[index] = value;

        else
            error("Invalid index");
    }

    //////////////////////////////////////////////////////////////////////////

    // the follwoing function maps data to a specific array, it also
    // facilitates the move of data between these arrays
    enum ArrayType
    {
        PID,
        SNA,
        SNB,
        SN
    };
    void swap_containers(const T array[], const ArrayType type)
    {
        if (type > SNB || type < PID)
            error("Invalid crossover type!!");

        switch (type)
        {
            case PID: // Arduino equivalent 0
                parentId = equalise_containers(array, parentId);

                for (int i = 0; i < this->size_of(array); ++i)
                    parentId.add(array[i], i);

            case SNA: // Arduino equivalent 1
                soundA = equalise_containers(array, soundA);
                for (int i = 0; i < this->size_of(array); ++i)
                    soundA.add(array[i], i);

            case SNB: // Arduino equivalent 2
                soundB = equalise_containers(array, soundB);
                for (int i = 0; i < this->size_of(array); ++i)
                    soundB.add(array[i], i); //.add(array[i]);

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
    bool parentA_contains(T value) { return soundA.contains(value); }
    bool parentB_contains(T value) { return soundB.contains(value); }
    bool parentIds_contains(T value) { return soundB.contains(value); }
    bool sound_contains(T sound) { return sound.contains(sound); }

    //....
    int parentA_indexOf(T value) { return soundA.contains(value); }
    int parentB_indexOf(T value) { return soundB.contains(value); }
    int parentIds_indexOf(T value) { return soundB.contains(value); }
    int sound_indexOf(T sound) { return sound.contains(sound); }

    void dispose()
    {
        parentId.dispose();
        soundA.dispose();
        soundB.dispose();
        sound.dispose();
    }

    arraylist() {} // no passing of parameters on init required
    ~arraylist() { this->dispose(); }
    
};

#endif
