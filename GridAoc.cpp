#include "GridAoc.h"

GridAoc::GridAoc()
{

}

GridAoc::~GridAoc()
{

}

void GridAoc::init(int start_x,int start_y,int end_x,int end_y)
{
    best_ant.distance = DB_MAX;
    for (int i = 0; i < N_CITY_G; ++i)
    {
        for (int j = 0; j < N_CITY_G; ++j)
        {
            grid_pher[i][j] = 1.0;
        }
    }

    for (int i = 0; i < N_ANT_G; ++i)
    {
        ants[i].init(start_x,start_y,end_x,end_y);
    }
}

void GridAoc::search()
{
    int num = 0;
    char buff[256];
    //外循环，迭代次数
    for(int i = 0; i < N_ITER_G; i++)
    {
        //内循环，蚂蚁数
        num = 0;
        for(int j = 0; j < N_ANT_G; j++)
        {
            ants[j].search();
        }

        for(int k = 0; k < N_ANT_G; k++)
        {
            if(ants[k].direction == GOAL)
            {
                if(best_ant.distance > ants[k].distance)
                {
                    best_ant = ants[k];
                    num++;
                }
            }
        }

        update();
        sprintf(buff,"[%d]:%f\n",i+1,best_ant.distance);
        printf("%s",buff);
        // if(num)
        // {
        //     int i = 0;
        //     for(i = 0; i < best_ant.num_city; i++)
        //     {
        //         printf("[%d,%d]->",DECODE_X(best_ant.road[i]),DECODE_Y(best_ant.road[i]));
        //     }
        //     printf("[%d,%d]\n",DECODE_X(best_ant.road[i]),DECODE_Y(best_ant.road[i]));
        //     exit(0);
        // }
    }
}

void GridAoc::update()
{
    double temp[N_CITY_G][N_CITY_G];
    memset(temp,0.0,sizeof(temp));

    int m = 0;
    int n = 0;
    int count = 0;
    for (int i = 0; i < N_ANT_G; ++i)
    {
         if(ants[i].direction == GOAL)
         {
            // for (int j = 1; j < N_CITY_G; ++j)
            // {
            //     m = ants[i].road[j];
            //     n = ants[i].road[j-1];

            //     temp[n][m] += 1.0/ants[i].distance;
            //     temp[m][n] = temp[n][m];
            // }
             count++;
         }
        for (int j = 1; j < N_CITY_G; ++j)
        {
            m = best_ant.road[j];
            n = best_ant.road[j-1];

            temp[n][m] += 1.0/best_ant.distance;
            temp[m][n] = temp[n][m];
        }
    }
    printf("goal:%d\n", count);
    for (int i = 0; i < N_CITY_G; ++i)
    {
        for (int j = 1; j < N_CITY_G; ++j)
        {
            grid_pher[i][j] = grid_pher[i][j]*ROU_G + temp[i][j];
        }
    }    
}