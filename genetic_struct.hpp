#ifndef GENETIC_LIB_GENETIC_STRUCT_H_
#define GENETIC_LIB_GENETIC_STRUCT_H_

#include "./control_flow/tuple.hpp"
#include "./containers/array.hpp"
#include "./containers/list.hpp"

template<class T>
class genetic_struct {
        // sound values to populate with sounds instead of assigning a single variable
        // per sound
        list<T> genetic_list;
        int parameters = -1;
  public:
        // constructor
        genetic_struct(int parameters=0) {
            this->parameters = parameters;
            genetic_list.remakeAll(parameters);
        }
        genetic_struct() { 
       //     paramters = -1; 
        };
        ~genetic_struct() { genetic_list.dispose(); }

        //
        long SliderTot;

        // note values to write to the iGA(interactive Genetic Algorithm) via MIDI
        int note;
        int control_value;
        int control_number;
        
        // set
        void set_params(int parameters) { 
            this->parameters = parameters; 
            genetic_list.remakeAll(this->parameters); 
        }

        int get_params() { return this->parameters; }

        // swap
        void swap_containers(const T array[], const list<T>::ArrayType type) { genetic_list.swap_containers(array, type); }

        // getters
        int*  get_sound_a() { return genetic_list.get_sound_a(); }
        int*  get_sound_b() { return genetic_list.get_sound_b(); }
        int*  get_parent_id() { return genetic_list.get_parent_id(); }
        long* get_sound() { return genetic_list.get_sound(); }
        int   get_roulette_value(int index) { return genetic_list.get_roulette_value(index);	}

        // ---

        long get_sound(int index) {
            // return this->genetic_list.
        }

        // setters
        void set_sounds(const long sounds[]) { genetic_list.set_sounds(sounds); };
        void set_soundsa(const int array_values[]) { genetic_list.set_soundsa(array_values); }
        void set_soundsb(const int array_values[]) { genetic_list.set_soundsb(array_values); }
        void set_parentIds(const int array_values[]) { genetic_list.set_parentIds(array_values); }
        void set_roulette_value(int index, int value) { genetic_list.set_roulette_value(index, value); }

        // disposal
        void dispose() { genetic_list.dispose(); }
};

#endif