# ***Genetic Lib (genetic-lib)***

### ***Description***

A Library primarily composed of a single GA(Genetic Algorithm) with the purpose of providing the the community with a solution to sound/image evolution via MIDI.

The library focuses on providing a more flexible and memory efficient option to the Arduino IDE(Integrated Development Environment).

### Exposed Methods & Types (Whatever you want to call them, same thing)

#### Enumerated Types

```cpp 
enum CROSSTYPE { Internal, Average, Standard }
```

#### Main Methods

```cpp 
swap_strands(int arrayA[], int arrayB[])
```

```cpp 
begin_population(genetic_struct<T> sequence_builder)
```

```cpp 
begin_population(int mySound[])
```

```cpp 
add_sound_value(int value, int index)
```

```cpp 
add_notevals(int note,int cValue, int cNumber)
```

```cpp 
add_parentId(int value,int index)
```

```cpp 
swap_sound_aValues()
```

```cpp 
swap_sound_bValues()
```

```cpp 
read_from_AtoB(int index)
```

```cpp 
evaluate_sound(int index)
```

```cpp 
evaluate_sound(long index)
```

```cpp 
analize_sounds(long sound, long SliderTot)
```

```cpp
analize_sounds()
```

```cpp 
read_note(int child[])
```

```cpp 
read_note(int child[],int noteValues[])
```

```cpp 
genetic_struct<T> read_chms_sound(int index)
```

```cpp 
genetic_struct<T> eval_sound_from(int index)
```

```cpp 
evaluate_sound(int child[], int index, int mysound[])
```

```cpp 
evaluate_sound(int child[], long sound, long SliderTot, int index, int mysound[], int parentId[]);
```

```cpp 
check_lowerbound(int child[],int strand,int parentId[])
```

```cpp 
check_upperbound(int child[],int strand, long SliderTot, long sound,int mysound[])
```

```cpp 
evaluate(int mysound[],int roulette)
```

```cpp 
evaluate(int mysound[],int parentA[], long sound,int roulette)
```

```cpp 
crossover(genetic_struct<T> nStruct)
```

```cpp 
crossover(int parentA[],int parentB[])
```

```cpp 
average_crossover(T parentA[], T parentB[], int mutate_value);
```

```cpp 
internal_crossover(T parentA[], T parentB[], int co_existance_cpoint, bool set)
```

```cpp 
start_roulette(T sound1, T sound2, T roulette, T roulette2)
```

```cpp 
start_roulette(int index, int index2);
```

```cpp 
co_ext_crossover(T parentA[], T parentB[], int co_existance_cpoint);
```

```cpp 
set_roulette_value(int index, T value);
```

```cpp 
get_parent(int index);
```

```cpp 
inter_change(int array[])
```

```cpp 
crossover_selector(T parentA[],T parentB[],int co_ext_crossover, CROSSTYPE type)
```

```cpp 
crossover_selector(int co_ext_crossover, CROSSTYPE type)
```

### ***Swap & comparator***

```cpp 
swap_sound_aValues(int soundA[],int soundB[])
```

```cpp 
swap_sound_bValues(int soundA[],int soundB[])
```

```cpp 
equality_of(int chromsomeA[],int chromsomeB[])
```

```cpp 
swap_containers(int array[], int type)
```



###	***Getters***

```cpp 
get_sounds()
```

```cpp 
get_soundsa()
```

```cpp 
get_soundsb()
```

```cpp 
get_parentIds()
```


###	***Setters***

```cpp 
set_sounds(long sounds[])
```

```cpp 
set_soundsa(int array_values[])
```

```cpp 
set_soundsb(int array_values[])
```

```cpp 
set_parentIds(int array_values[]);
```
