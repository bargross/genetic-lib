/*
 *      genetic_lib.h
 *
 *     A Library primarily composed of a single GA(Genetic Algorithm) with the purpose of
 *   providing the the community with a solution to sound/image evolution via MIDI
 *
 *   The library focuses on providing a more flexible and memory efficient option to the
 *   Arduino IDE(Integrated Development Environment)
 *
 *      Created on: Mar 28, 2017
 *   Author: Leonardo H. M.
 */

#ifndef GENETIC_LIB_H_
#define GENETIC_LIB_H_

// #include "Arduino.h";
#include <stdint.h>
#include <string>
#include <iostream>
#include <typeinfo>

//
#include "data_structures/genetic_struct.hpp"

//===============================================================================================

// Helper Methods
//================

void stop() { while(1){}; }         // stops all program execution if called

// standard c++ for testing
void error (std::string str) {
    str = "Runtime Error: [ " + str + " ]";

    std::cout << str << std::endl;

    stop();
}

// ARDUINO ERROR() EQUIVALENT 

// void error(String str) {
//         str = "Runtime Error: [ " + str + " ]";

//     printf("%c", str );

//     stop();
// }

//===============================================================================================
template<class T>
class genetic_lib {
    //..
    genetic_struct<T>* chromosome_struct = nullptr;
    int set1A = 1;
    int set1B = 128;
    int set2A = 0;
    int set2B = 100;
    int millis = 1000;

    template<class A, size_t N>
    constexpr size_t size(A (&)[N]) { return N; }

  public:
    genetic_lib (int parameters) { chromosome_struct = new genetic_struct<T>(parameters);    } // main constructor
    genetic_lib ();  // in case the user uses standard Library methods
    ~genetic_lib() { chromosome_struct->dispose(); }  // destructor

    // returns the structure
    genetic_struct<T>* get_genetic_structure() { return chromosome_struct; }

    /****************************************************************************************
                                    Library Methods
    *****************************************************************************************/

    //    Main Methods
    //----------------------------

    // init & write methods
    void swap_strands(int arrayA[], int arrayB[]);
    void begin_population(genetic_struct<T> sequence_builder);
    void begin_population(int mySound[]);
    void add_sound_value(int value, const int index);
    void add_notevals(int note,int cValue, int cNumber);
    void add_parentId(int value,const int index);
    void set_roulette_value(const int index, T value);
    
    // strand manipulation methods
    void swap_sound_aValues();
    void swap_sound_bValues();
    void read_from_AtoB(const int index);
    void evaluate_sound(const int index);
    void evaluate_sound(long index);
    void analize_sounds(long sound, long SliderTot);
    void analize_sounds();
    void read_note(int child[]);
    void read_note(int child[],int noteValues[]);                 // note values must be in order
    genetic_struct<T> read_chms_sound(const int index);
    genetic_struct<T> eval_sound_from(const int index);
    void evaluate_sound(int child[], const int index, int mysound[]);
    void evaluate_sound(int child[], long sound, long SliderTot, const int index, int mysound[], int parentId[]);
    void check_lowerbound(int child[],int strand,int parentId[]);
    void check_upperbound(int child[],int strand, long SliderTot, long sound,int mysound[]);
    void evaluate(int mysound[],int roulette);
    void evaluate(int mysound[],int parentA[], long sound,int roulette);
    void crossover(genetic_struct<T> nStruct);
    void crossover(int parentA[],int parentB[]);
    void average_crossover(T parentA[], T parentB[], int mutate_value);
    void internal_crossover(const T parentA[], const  T parentB[], int co_existance_cpoint, bool set);
    void start_roulette(T sound1, T sound2, T roulette, T roulette2);
    void start_roulette(const int index, const int index2);
    void co_ext_crossover(T parentA[], T parentB[], int co_existance_cpoint);
    int  get_parent(const int index);
    void inter_change(int array[]) {
        if(size(array) > chromosome_struct->get_params() || size(array) < chromosome_struct->get_params() )
            error("Length of argument array and primary sound array dont match");

        else swap_strands(array, chromosome_struct->get_soundsa());
    }

    enum CROSSOVER { INTERNAL, AVERAGE, STANDARD };
    void crossover_selector(const T parentA[], const T parentB[], int co_ext_crossover, CROSSOVER type);
    void crossover_selector(int co_ext_crossover, CROSSOVER type);

    //    Swap & comparator
    //----------------------------

    void swap_sound_aValues(int soundA[],int soundB[]);
    void swap_sound_bValues(int soundA[],int soundB[]);
    bool equality_of(int chromsomeA[],int chromsomeB[]);
    void swap_containers(int array[], int type) {
        chromosome_struct->swap_containers(array, type);
    }

    //    Getters
    //----------------------------
    long* get_sounds() { return chromosome_struct->get_sounds(); }
    int* get_soundsa() { return chromosome_struct->get_soundsa(); }
    int* get_soundsb() { return chromosome_struct->get_soundsb(); }
    int* get_parentIds() { return chromosome_struct->get_parentIds(); }

    //    Setters
    //----------------------------
    void set_sounds(long sounds[]) { chromosome_struct->set_sounds(sounds); }
    void set_soundsa(int array_values[]) { chromosome_struct->set_soundsa(array_values); }
    void set_soundsb(int array_values[]) { chromosome_struct->set_soundsb(array_values); }
    void set_parentIds(int array_values[]) { chromosome_struct->set_parentIds(array_values); }
};

#endif
