#ifndef _MMAOC_H_
#define _MMAOC_H_

#include "Aoc.h"
#include "MMAnt.h"

class MMAoc : public Aoc
{
public:
    double m_dbRate; //最大信息素和最小信息素的比值

public:
    virtual void init();
    virtual void search();
    virtual void update();

public:
    MMAoc();
    ~MMAoc();   
};

#endif