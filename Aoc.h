#ifndef _AOC_H_
#define _AOC_H_

#include "Ant.h" 

class Aoc
{
public:
    Ant* ants[N_ANT];
    Ant* best_ant;

public:
    virtual void init();
    virtual void search();
    virtual void update();

public:
    Aoc();
    ~Aoc();
    
};

#endif