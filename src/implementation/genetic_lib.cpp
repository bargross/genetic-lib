#include "genetic_lib.hpp"
#include <iostream>
#include <random>

/*******************************************************************************
 Roulette Wheel & Crossover Methods
********************************************************************************/

int random(int min, int max) {
  return rand()%(max-min + 1) + min;
}

void populate (int* containerA, int* containerB) {
  for(int iVal; iVal < sizeof(containerB); ++iVal)
    containerA[iVal] = containerB[iVal];
}

// sound value case 0 where
template<class T>
void genetic_lib<T>::check_lowerbound(int child[], int strand, int parentId[]) {
  for(int pin=0; pin < sizeof(*child); ++pin) {
    child[pin] = random(set1A, set1B);
    parentId[strand] = 0;
  }
}

// sound value case 1023 where
template<class T>
void genetic_lib<T>::check_upperbound(int child[], int strand, long SliderTot, long sound, int mysound[]) {
  for(int strand = 0; strand <= sizeof(*child); strand++)
    child[strand] = mysound[strand];

  SliderTot = (SliderTot+sound);
}

template<class T>
bool genetic_lib<T>::equality_of(int chromosomeA[], int chromosomeB[]) {
  for(int index_at = 0; index_at < sizeof(*chromosomeA); ++index_at)
    if (chromosomeA[index_at] == chromosomeB[index_at])
      continue;

    else return false;

  return true;
}

template<class T>
void genetic_lib<T>::evaluate(int mysound[], int roulette) {
  const auto& replacement = chromosome_struct->get_soundsa();

  // we check the roulette value
  if (roulette >= 0 && roulette <= 50)
    // if the roulette value meets the conditions we swap the values in parentA for mysound values
    for(int strand =0; strand <= sizeof(*mysound); ++strand)
      replacement[strand] = mysound[strand];
}

// Overloaded Method - Excludes the use of typedef (GAbuild) and allows the usage of standard data-types/data-type-containers
template<class T>
void genetic_lib<T>::evaluate(int mysound[], int parentA[], long sound, int roulette) {
  if (roulette >= 0 && roulette <= sound)
    for (int i = 0; i < sizeof(*mysound); ++i)
      parentA[i] = mysound[i];
}

// not needed
template<class T>
void genetic_lib<T>::crossover(genetic_struct<T> nStruct) {
  int start = 0;
  int Cpoint = random(start, nStruct.parameters);
  int mutate = 2;

  const auto& a_replacement = nStruct.get_soundsa();
  const auto& b_replacement = nStruct.get_soundsb();
  
  for (int strand = 0; strand <= nStruct.parameters; ++strand) {
    a_replacement[strand] = b_replacement[strand];

    int cosmic = 0;
    for(int strand =0; strand <=  nStruct.parameters; ++strand) {

      cosmic = random(set1A, set1B);
      if(cosmic <= mutate)
        a_replacement[strand] = random(set1A, set1B);
    }
  }
}


// checks genetic_struct mutate probability per generation
template<class T>
void genetic_lib<T>::crossover(int parentA[], int parentB[]) {
  int Cpoint = random(set1A, chromosome_struct->parameters);
  int mutate = random(set1A, set2B);
  const auto& a_replacement = parentA;
  const auto& b_replacement = parentB;

  for(int cut_point = Cpoint; cut_point < chromosome_struct->parameters; ++cut_point){
    // parentA[i] = parentB[i];

    a_replacement[cut_point] = b_replacement[cut_point];

    int cosmic = 0;

    for(int strand = 0; strand < chromosome_struct->parameters; ++strand) {
      cosmic = random(set2A, set2B);
      if(cosmic <= mutate)
        a_replacement[strand] = random(set1A, set1B);
    }
  }
}

// Standard average crossover where we average all strands of parentA and parentB
// and swap all values from index 0 to the end of the collection with the averaged values
// of both parents, i.e.: i.e.: f(m, n) = m[0 to end] = (m[b] + n[b]) / 2, ++b
template<class T>
void genetic_lib<T>::average_crossover(T parentA[], T parentB[], int mutate_value) {
  chromosome_struct->parameters = chromosome_struct->parameters == 0 ? sizeof(parentA) : chromosome_struct->parameters;
  int container[sizeof(parentA)]; // = parentA;
  
  populate(container, parentA);
  
  const auto& parent_a_temp = parentA;
  const auto& parent_b_temp = parentB;

  for(int strand=0; strand < chromosome_struct->parameters; ++strand) {
    parent_a_temp[strand] = (parent_a_temp[strand] + parent_b_temp[strand]) / 2;
    int cosmic = random(set2A, set2B),
        rand_strand = random(set2A, chromosome_struct->parameters);

    if(cosmic <= mutate_value)
      parent_a_temp[rand_strand] = random(set1A, set1B);
  }

  if(equality_of(container, parentA) || equality_of(parentA, parentB)) {
    bool is_equal = true;
    while(!is_equal) {
      is_equal = true;

      int rand_strand = random(set1A, chromosome_struct->parameters);
      parent_a_temp[rand_strand] = random(set2A, set2B);

      is_equal = equality_of(container, parentA) && equality_of(parentA, parentB);
    }
  }
}

/*
   Non-standard crossover operator, where strands are averaged
   the operator swaps strands by avereging interval values of the chromosome
   i.e:

      Array A -> [1,2,4,5,6,7]

      A[i] = (1 + 2) / 2 => i = 0
      A[i] = (2 + 3) / 2 => i = 1

      and so on....

   Drawbacks of this technique involves mutation and output solutions,
   the operator reaches a cap at which the chromosome/s cannot evolve further and therefore the
   ranking mechanism will deem all incapable or will deem all capable (still fixing this issue),
   To avoid such measure a random strand swap has been added to avoid premature convergeance and/or
   prevent termination of the evolutionary process
*/
template<class T>
void genetic_lib<T>::internal_crossover(const T parentA[], const T parentB[], int coexistance_cpoint, bool set) {
  int Cpoint = random(coexistance_cpoint, chromosome_struct->parameters),
      internal = coexistance_cpoint - 1,
      strandIndex = 0,
      mutate = random(set1A, 20);

  int    random_cpoint = random(set1A, set1B);
  int container[chromosome_struct->parameters];

  const auto& parent_a_temp = parentA;
  const auto& parent_b_temp = parentB;

  for(int strand=0; strand < coexistance_cpoint && internal >= 0; ++strand) {
    int reverse_distance = coexistance_cpoint - (coexistance_cpoint / 2),
        linear_distance = coexistance_cpoint / 2;

    if(strand <= linear_distance && internal >= reverse_distance) {
      int sumA = 0, sumB = 0;
      if(set) sumA = parentB[strand] + parentB[internal];
      else {
        sumA = parentA[strand] + parentA[internal],
        sumB = parentB[strand] + parentB[internal];
      }

      container[strand] = sumB == 0 ? sumA / 2 : (sumA + sumB) / 2;
    }
  }

  if(!equality_of(container, parentA))
    parentA = container;

  else {
    bool is_equal = false;

    while (!is_equal) {
      is_equal = false;
      for(int gene_pool=0; gene_pool < chromosome_struct->parameters; ++gene_pool)
        parentA[gene_pool] = (parentA[gene_pool] + parentB[gene_pool]) / 2;

      is_equal = equality_of(parentA, container);
    }
  }

  for(int gene_pool = Cpoint; gene_pool < chromosome_struct->parameters; ++gene_pool) {
    parentA[gene_pool] = parentB[gene_pool];

    int chance = 0;
    for(int gene=0; gene < chromosome_struct->parameters; ++gene) {
      chance = random(set1A, set1B);

      if(chance <= mutate)
        parentA[gene] = random(set2A, set2B);
    }
  }
}

/* Loop from index 0 to co-existance cut point and average values at each index from both parents
   i.e.: f(m, n, c) = m[0 to c] = (m[b] + n[b]) / 2, inc b and m[c to end] = (m[b] = n[b]), inc b
   mutation chance(probability): 0.0%, 0.1%, 0.2%, 0.4% -> all posses equal chance of being selected per iteration
   from co-existance cut-point to end of index it swaps strands i.e.: (standard crossover) 

   Crossover intended for the union or co-existance of two crossover methodologies in a simplistic function.
   crossover happens once the genetic encoding is broken in two sectors where we take sector A of
   chromosome A and chromosome B, average it and then use standard genome crossover, i.e.:

   ChromsomeA -> [ 1 , 2 | 3 , 4 , 5 , 6 ]
         |SectorA| >> 1,2 |  Sector-B | >> 3,4,5,6

   ChromsomeB -> [ 2 , 3 | 1 , 6 , 5 , 4 ]
         |SectorA| >> 2,3 |  Sector-B | >> 1,6,5,4

   chromsomeA[Sector A] = (chromsomeA[Sector A at index b] + chromsomeB[Sector A at index b]) / total_strands
   chromsomeA[Sector B] = genetic_structB[Sector B at index b]

   Sector-B always starts from the cut point generated at random from the co-existance cut point and the total amount
   of chromosome_struct->parameters   template<class T> bool type_check(T value) {
*/

template<class T>
void genetic_lib<T>::co_ext_crossover(T parentA[], T parentB[], int co_existance_cpoint) {
  chromosome_struct->parameters = sizeof(parentA);

  // cut point randomly created between the cut point for co-existance and chromosome_struct->parameters (strands)
  int cut_point = random(co_existance_cpoint, chromosome_struct->parameters);

  // random genetic mutate variation
  unsigned int _mutate_between = 1;
  unsigned int _and = 4;

  // chose to keep mutate random
  int mutate_rate = random(_mutate_between, _and);

  for(int strand=0; strand < co_existance_cpoint; ++strand)
    parentA[strand] = (parentA[strand] + parentB[strand]) / 2;

  for(int strand= cut_point; strand < chromosome_struct->parameters; ++strand) {
    parentA[strand] = parentB[strand];

    int cosmic = 0;
    for(int _strand = 0; _strand < chromosome_struct->parameters; ++_strand) {
      cosmic = random(set2A, set2B);
      if(cosmic <= mutate_rate)
        parentA[_strand] = random(set1A, set1B);
    }
  }
}

template<class T>
void genetic_lib<T>::crossover_selector(const T parentA[], const T parentB[], int co_ext_crossover, CROSSOVER type) {
  switch(type) {
    case INTERNAL:
      if(co_ext_crossover > 0)
        this->ininternal_crossover(parentA, parentB, co_ext_crossover, false);
      else error("Co-Existance Crossover Cannot be Empty!!");

    case AVERAGE:
      this->average_crossover(parentA, parentB, random(2, 9));

    case STANDARD:
      this->crossover(parentA, parentB);

    default: error("invalid value");
  }
}

// in Arunido IDE values are from 0-2
template<class T>
void genetic_lib<T>::crossover_selector(int co_ext_crossover, CROSSOVER type) {
  const auto& parent_a_temp = chromosome_struct->get_soundsa();
  const auto& parent_b_temp = chromosome_struct->get_soundsb();

  switch(type) {
    case INTERNAL:   // Arduino equivalent = 0
      if(co_ext_crossover > 0)
        internal_crossover(parent_a_temp, parent_b_temp, co_ext_crossover, false);
      else error("Co-Existance Crossover Cannot be Empty!!");

    case AVERAGE:   // Arduino equivalent = 1
      average_crossover(parent_a_temp, parent_b_temp, random(2, 9));

    case STANDARD:  // Arduino equivalent = 2
      crossover(parent_a_temp, parent_b_temp);

    default:  error("invalid value");
  }
}

/*******************************************************************************
  IO Methods ------ Begin
********************************************************************************/

// analyze sound note for values of 50 or lower and 970 or higher
// so f(x) = x <= 50 = round to 0 || f(x) = x >= 970 = round to 1023
template<class T>
void genetic_lib<T>::read_from_AtoB(int index) {
  const auto& sound_temp = chromosome_struct->get_sounds();
  const auto sound_value = sound_temp[index];
  
  if(sound_value <= 50)
    sound_temp[index] = 0;

  else if(sound_value >= 970)
    sound_temp[index] = 1023;
}

// Overloaded method
template<class T>
genetic_struct<T> genetic_lib<T>::read_chms_sound(int index) {
  const auto& sound_temp = chromosome_struct->get_sounds();
  if(sound_temp[index] <= 50)
    sound_temp[index] = 0;

  else if(sound_temp[index] >= 970)
    sound_temp[index] = 1023;

  long temporary_container[sizeof(sound_temp)];

  for(int iVal = 0; iVal < sizeof(sound_temp); ++iVal)
    temporary_container[iVal] = sound_temp[iVal];

  chromosome_struct->set_sounds( temporary_container );

  return *chromosome_struct;
}


template<class T>
genetic_struct<T> genetic_lib<T>::eval_sound_from(int index) {
  const auto& pId_temp =  chromosome_struct->get_parentIds();
  if(pId_temp[index] != 0)
    pId_temp[index] = ((pId_temp[index] * 100) / chromosome_struct->SliderTot);

  return *chromosome_struct;
}

template<class T>
void genetic_lib<T>::evaluate_sound(int index) {
  const auto& pId_temp =  chromosome_struct->get_parentIds();
  if(pId_temp[index] != 0)
    pId_temp[index] = ((pId_temp[index] * 100) / chromosome_struct->SliderTot);

  delete pId_temp;
}

template<class T>
void genetic_lib<T>::analize_sounds(long sound, long SliderTot) { if (sound != 0) sound = ((sound*100) / SliderTot); }
template<class T>
void genetic_lib<T>::analize_sounds() {
  const auto& sound_temp =  chromosome_struct->get_sounds();
  for(int iSound = 0; iSound < chromosome_struct->parameters; iSound++) {
    if (sound_temp[iSound] != 0)
        sound_temp[iSound] = ((sound_temp[iSound] * 100) / chromosome_struct->SliderTot);

    if(iSound > 0)
        sound_temp[iSound] += sound_temp[iSound - 1];
  }
}

//
// template<class T>
// void genetic_lib<T>::read_note(int child[]) {
//   for(int index = 0; index <= sizeof(child); index++) {
//     chromosome_struct->control_value = child[index];
//     chromosome_struct->control_number = index + 4;

//     Serial.write(0xB0);
//     Serial.write(chromosome_struct->control_number);
//     Serial.write(chromosome_struct->control_value);
//   }

//   delay(millis);

//   Serial.write(0x90);
//   Serial.write(chromosome_struct->note);
//   Serial.write(0x45);
//     delay(1000);
//   Serial.write(0x90);
//   Serial.write(chromosome_struct->note);
//   Serial.write(0x0);
// }

// template<class T>
// void genetic_lib<T>::read_note(int child[], int values[]) {
//   auto& control_value = values[1];
//   auto& control_number = values[2];
//   auto& note = values[0];

//   for (int i=0; i<= sizeof(child); ++i) {
//     control_value = child[i];
//     control_number = i+4;     //check this value from ctl map

//     Serial.write(0xB0);
//     Serial.write(control_value);
//     Serial.write(control_number);
//   }

//   delay(millis);

//   Serial.write(0x90);
//   Serial.write(note);
//   Serial.write(0x45);

//   delay(1000);

//   Serial.write(0x90);
//   Serial.write(note);
//   Serial.write(0x0);
// }


/*******************************************************************************
    IO Methods ------ End
********************************************************************************/


/******************************************************************************
    Helper Methods --- Begin
*******************************************************************************/

void swap_values(int arrayA[], int arrayB[]) {
    for(int i=0; i< sizeof(*arrayA); ++i) arrayA[i] = arrayB[i];
}

// populate child arrays with values stored in the Gene sequence
template<class T>
void genetic_lib<T>::begin_population(genetic_struct<T> chromosome_struct) {
    // chromosome_struct->parameters are fetched from arrays within a struct (type synonym)
    for(int pin = 0; pin < chromosome_struct.parameters; pin++) {
    const auto& parent_a_temp =  chromosome_struct.get_soundsa();
      parent_a_temp[pin] = random(set1A, set1B);
    }
}

// populates sound collections with random values with range 0-127(1-128)
template<class T>
void genetic_lib<T>::begin_population(int mySound[]) {
    for(int pin =0; pin < chromosome_struct->parameters; pin++)
      mySound[pin] = random (set1A, set1B);
}

//
template<class T>
void genetic_lib<T>::add_sound_value(int value, int index) {
  const auto& sound_temp = chromosome_struct->get_sounds(); //get_sounds();
  sound_temp[index] = value;
}

//
template<class T>
void genetic_lib<T>::add_notevals(int note, int cValue, int cNumber) {
    chromosome_struct->note = note;
    chromosome_struct->control_value = cValue;
    chromosome_struct->control_number = cNumber;
}

//
template<class T>
void genetic_lib<T>::add_parentId(int value, int index) {
   const auto& pId_replacement =  chromosome_struct->get_parentIds();
   pId_replacement[index] = value;
}

template<class T>
void genetic_lib<T>::swap_sound_aValues() {
  const auto& a_replacement =  chromosome_struct->get_soundsa();
  const auto& b_replacement =  chromosome_struct->get_soundsb();

   swap_sound_aValues(a_replacement, b_replacement);
}

template<class T>
void genetic_lib<T>::swap_sound_aValues(int my_soundA[], int my_soundB[]) {
   swap_values(my_soundA, my_soundB);
}

template<class T>
void genetic_lib<T>::swap_sound_bValues() {
  const auto& a_replacement =  chromosome_struct->get_soundsa();
  const auto& b_replacement =  chromosome_struct->get_soundsb();

   swap_values(a_replacement, b_replacement);
}

template<class T>
void genetic_lib<T>::swap_sound_bValues(int my_soundA[], int my_soundB[]) {
   swap_values(my_soundA, my_soundB);
}

/******************************************************************************
    Helper Methods --- End
*******************************************************************************/


/******************************************************************************
    Evaluation  ------ Begin
*******************************************************************************/
//
template<class T>
void genetic_lib<T>::evaluate_sound(int child[], int index, int mysound[]) {
  const auto& pId_temp = chromosome_struct->get_parentIds();
  const auto& sound_temp = chromosome_struct->get_sounds();

    switch(sound_temp[index]) {
        case 0: check_lowerbound(child, index, pId_temp); break;
        case 1023: check_upperbound(child, index, chromosome_struct->SliderTot, sound_temp[index], mysound); break;
        default:
            chromosome_struct->SliderTot = (chromosome_struct->SliderTot+sound_temp[index]);
            pId_temp[index] = 2;
    }
}

template<class T>
void genetic_lib<T>::evaluate_sound(int child[], long sound, long SliderTot, int index, int mysound[], int parentId[]) {
    switch(sound) {
        case 0: check_lowerbound(child, index, parentId); break;
        case 1023: check_upperbound(child, index, SliderTot, sound, mysound); break;
    default:
            SliderTot = (SliderTot+sound);
            parentId[index] = 2;
    }
}

template<class T>
void genetic_lib<T>::start_roulette(T sound1, T sound2, T roulette, T roulette2) {
    while ((roulette >= sound1 && roulette <= sound2) && (roulette2 >= sound1 && roulette2 <= sound2))
        roulette2 = random(set2A, set2B);
}

template<class T>
void genetic_lib<T>::start_roulette(int index, int index2) {
  const auto& sound_temp = chromosome_struct->get_sounds();
  bool isEqual = (chromosome_struct->get_roulette_value(0) >= sound_temp[index]
                 && chromosome_struct->get_roulette_value(0) <= sound_temp[index2])
                 && (chromosome_struct->get_roulette_value(1) >= sound_temp[index]
                 && chromosome_struct->get_roulette_value(1) <= sound_temp[index2]);

  while(isEqual) {
        chromosome_struct->set_roulette_value(1, random(set2A, set2B));
      isEqual = (chromosome_struct->get_roulette_value(0) >= sound_temp[index]
                && chromosome_struct->get_roulette_value(0) <= sound_temp[index2])
                && (chromosome_struct->get_roulette_value(1) >= sound_temp[index]
                && chromosome_struct->get_roulette_value(1) <= sound_temp[index2]);
 }
}

template<class T>
void genetic_lib<T>::set_roulette_value(int index, T value) {
  chromosome_struct->set_roulette_value(index, value);
}

template<class T>
int genetic_lib<T>::get_parent(int index) {
  const auto& pId_temp = chromosome_struct->get_parentIds();
  return pId_temp[index];
}
/******************************************************************************
  Evaluation  ------ End
*******************************************************************************/
