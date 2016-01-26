#include "GridAnt.h"

GridAnt::GridAnt()
{

}

GridAnt::~GridAnt()
{

}

void GridAnt::init(int x_start,int y_start,int x_end,int y_end)
{
    for (int i = 0; i < N_GRID; ++i)
    {
        for (int j = 0; j < N_GRID; ++j)
        {
            travel[i][j] = 0;           //0代表可以走1代表不可以走
        }
    }
    memset(road,0,sizeof(road));
    start_x = cur_x = x_start;
    start_y = cur_y = y_start;
    end_x = x_end;
    end_y = y_end;
    cur_city = ENCODE(cur_x,cur_y);
    distance = 0.0;
    direction = RIGHT;
    travel[cur_x][cur_y] = 1;
    num_city = 0;
    road[num_city] = cur_city;
}

enum DIRECTION GridAnt::chooseGrid()
{
    double tmp_prob[8] = {0,0,0,0,0,0,0,0};
    bool flag[8] = {false,false,false,false,false,false,false,false};
    int flag_res = 0;
    double total = 0.0;

    if(abs(cur_x - end_x) <= 1 && abs(cur_y - end_y) <= 1)
    {
        direction = GOAL;
        return GOAL;
    }

    if (cur_x - 1 >= 0 && g_grid[cur_x - 1][cur_y] == 0 && travel[cur_x - 1][cur_y] == 0)      //up
    {
        /*计算转移到其它城市概率，公式1*/
        tmp_prob[0] = pow(grid_pher[cur_city][ENCODE(cur_x - 1,cur_y)],ALPHA)*pow(1.0/PIX,BETA);
        flag[0] = true;
    }
    if (cur_x + 1 < N_GRID && g_grid[cur_x + 1][cur_y] == 0 && travel[cur_x + 1][cur_y] == 0)      //down
    {
        tmp_prob[1] = pow(grid_pher[cur_city][ENCODE(cur_x + 1,cur_y)],ALPHA)*pow(1.0/PIX,BETA);
        flag[1] = true;
    }
    if (cur_y - 1 >= 0 && g_grid[cur_x][cur_y - 1] == 0 && travel[cur_x][cur_y - 1] == 0)      //left
    {
        tmp_prob[2] = pow(grid_pher[cur_city][ENCODE(cur_x,cur_y - 1)],ALPHA)*pow(1.0/PIX,BETA);
        flag[2] = true;
    }
    if (cur_y + 1 < N_GRID && g_grid[cur_x][cur_y + 1] == 0 && travel[cur_x][cur_y + 1] == 0)      //right
    {
        tmp_prob[3] = pow(grid_pher[cur_city][ENCODE(cur_x,cur_y + 1)],ALPHA)*pow(1.0/PIX,BETA);
        flag[3] = true;
    }
    if (cur_x - 1 >= 0 && cur_y - 1 >= 0 && g_grid[cur_x - 1][cur_y - 1] == 0 && travel[cur_x - 1][cur_y - 1] == 0)         //left-up
    {
        tmp_prob[4] = pow(grid_pher[cur_city][ENCODE(cur_x - 1,cur_y - 1)],ALPHA)*pow(1.0/ANG_PIX,BETA);
        flag[4] = true;
    }
    if (cur_x + 1 < N_GRID && cur_y - 1 >= 0 && g_grid[cur_x + 1][cur_y - 1] == 0 && travel[cur_x + 1][cur_y - 1] == 0)      //left-down
    {
        tmp_prob[5] = pow(grid_pher[cur_city][ENCODE(cur_x + 1,cur_y - 1)],ALPHA)*pow(1.0/ANG_PIX,BETA);
        flag[5] = true;
    }
    if (cur_x - 1 >= 0 && cur_y + 1 < N_GRID && g_grid[cur_x - 1][cur_y + 1] == 0 && travel[cur_x - 1][cur_y + 1] == 0)      //right-up
    {
        tmp_prob[6] = pow(grid_pher[cur_city][ENCODE(cur_x - 1,cur_y + 1)],ALPHA)*pow(1.0/ANG_PIX,BETA);
        flag[6] = true;
    }
    if (cur_x + 1 < N_GRID && cur_y + 1 < N_GRID && g_grid[cur_x + 1][cur_y + 1] == 0 && travel[cur_x + 1][cur_y + 1] == 0)   //right-down
    {
        tmp_prob[7] = pow(grid_pher[cur_city][ENCODE(cur_x + 1,cur_y + 1)],ALPHA)*pow(1.0/ANG_PIX,BETA);
        flag[7] = true;
    }

    for (int i = 0; i < 8; ++i)
    {
        total += tmp_prob[i];
        flag_res += flag[i];
    }

    if(flag_res == 0)
    {
        direction = NOROAD;
        return NOROAD;
    }

    double rand_num = rnd(0.0,total);

    if (total > 0.0)
    {
        for (int i = 0; i < 8; ++i)
        {
            rand_num -= tmp_prob[i];
            if (rand_num < 0.0)
            {
                direction = (DIRECTION)i;
                return (DIRECTION)i;
            }
        }
    }
    printf("total is too little!\n");
    /*如果城市间的信息素非常小 ( 小到比double能够表示的最小的数字还要小 )
    那么由于浮点运算的误差原因，上面计算的概率总和可能为0
    会出现经过上述操作，没有城市被选择出来
    出现这种情况，就把第一个没去过的城市作为返回结果*/
    int greed_choose = -1;
    for (int i = 0; i < 8; ++i)
    {
        if (tmp_prob[i] > greed_choose)
        {
            greed_choose = i;
        }
    }

    direction = (DIRECTION)greed_choose;
    return (DIRECTION)greed_choose;
}

void GridAnt::move()
{
    DIRECTION dir = chooseGrid();
    switch(dir)
    {
        case UP:cur_x--;distance += PIX;break;
        case DOWN:cur_x++;distance += PIX;break;
        case LEFT:cur_y--;distance += PIX;break;
        case RIGHT:cur_y++;distance += PIX;break;
        case LEFT_UP:cur_x--;cur_y--;distance += ANG_PIX;break;
        case LEFT_DOWN:cur_y--;cur_x++;distance += ANG_PIX;break;
        case RIGHT_UP:cur_y++;cur_x--;distance += ANG_PIX;break;
        case RIGHT_DOWN:cur_y++;cur_x++;distance += ANG_PIX;break;
        case NOROAD:return;
        case GOAL:distance += sqrt(pow(end_x - cur_x,2) + pow(end_y - cur_y,2))*100.0;cur_x = end_x;cur_y = end_y;break;
    }
    cur_city = ENCODE(cur_x,cur_y);
    num_city++;
    travel[cur_x][cur_y] = 1;
    road[num_city] = cur_city;
}

void GridAnt::search()
{
    init(start_x,start_y,end_x,end_y);
    while(direction != NOROAD && direction != GOAL)
    {
        move();
    }
}
