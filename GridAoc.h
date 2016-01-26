#include "GridAnt.h"

class GridAoc
{
public:
    GridAnt ants[N_ANT_G];
    GridAnt goal_ants[N_ANT_G];
    GridAnt best_ant;

public:
    void init(int start_x,int start_y,int end_x,int end_y);
    void search();
    void update();

public:
    GridAoc();
    ~GridAoc();
    
};