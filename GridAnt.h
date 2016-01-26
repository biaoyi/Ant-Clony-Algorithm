#include "Para.h"
#define ENCODE(par1,par2) ((par1)*20 + par2)
#define DECODE_X(par) par/20
#define DECODE_Y(par) par%20

enum DIRECTION
{
    UP = 0,
    DOWN = 1,
    LEFT = 2,
    RIGHT = 3,
    LEFT_UP = 4,
    LEFT_DOWN = 5,
    RIGHT_UP =6,
    RIGHT_DOWN = 7,
    NOROAD = 8,
    GOAL = 9
};

class GridAnt
{
public:
    int cur_x;
    int cur_y;
    int cur_city;
    int start_x;
    int start_y;
    int end_x;
    int end_y;
    double distance;
    bool travel[N_GRID][N_GRID];     //traveled cities
    int road[N_CITY_G];
    enum DIRECTION direction;
    int num_city;
public:
    void init(int x_start,int y_start,int x_end,int y_end);
    void search();
    enum DIRECTION chooseGrid();
    void move();
public:
    GridAnt();
    ~GridAnt();
    
};