#include "Aoc.h"

Aoc::Aoc()
{

}

Aoc::~Aoc()
{

}

void Aoc::init()
{
    best_ant = new Ant();
    best_ant->distance = DB_MAX;
    double tmp = 0.0;
    for (int i = 0; i < N_ANT; ++i)
    {
        ants[i] = new Ant();
    }
    for(int i = 0; i < N_CITY; i++)
    {
        for(int j = 0; j < N_CITY; j++)
        {
            //计算两城市间距离
            city_distance[i][j] = ROUND(sqrt(pow(x_Ary[i] - x_Ary[j],2) + pow(y_Ary[i] - y_Ary[j],2)));
            //初始化环境信息素，先把城市间的信息素设置成一样
            //这里设置成1.0，设置成多少对结果影响不是太大，对算法收敛速度有些影响
            city_pher[i][j] = 1.0;
        }
    }

    for(int i = 1; i < N_CITY; i++)
    {
        tmp += sqrt(pow(x_Ary[i] - x_Ary[i-1],2) + pow(y_Ary[i] - y_Ary[i-1],2));
    }
    printf("%f\n",tmp);
}

void Aoc::update()
{
    //计算新增信息素
    double tmp_pher[N_CITY][N_CITY];     //为的而他啕i，j的集合数组
    memset(tmp_pher,0,sizeof(tmp_pher));

    int m = 0;
    int n = 0;

    for(int i = 0; i < N_ANT; i++)
    {
        for(int j = 1; j < N_CITY; j++)
        {
            m = ants[i]->travel[j];
            n = ants[i]->travel[j-1];
            /*计算信息素，公式2*/
            tmp_pher[n][m] += PHER/ants[i]->distance;
            tmp_pher[m][n] = tmp_pher[n][m];
        }
        n = ants[i]->travel[0];
        tmp_pher[n][m] += PHER/ants[i]->distance;
        tmp_pher[m][n] = tmp_pher[n][m];
    }

    //==================================================================
    for(int i = 0; i < N_CITY; i++)
    {
        for(int j = 0; j < N_CITY; j++)
        {
            //更新环境信息素，公式3，新的环境信息素 = 挥发后信息素 + 新添加信息素
            city_pher[i][j] = city_pher[i][j]*ROU  + tmp_pher[i][j];
        }
    }

}
void Aoc::search()
{
    char buff[256];

    //外循环，迭代次数
    for(int i = 0; i < N_ITER; i++)
    {
        //内循环，蚂蚁数
        for(int j = 0; j < N_ANT; j++)
        {
            ants[j]->search();
        }

        for(int k = 0; k < N_ANT; k++)
        {
            if(best_ant->distance > ants[k]->distance)
            {
                *best_ant = *ants[k];
            }
        }

        update();

        sprintf(buff,"[%d]:%f\n",i+1,best_ant->distance);
        printf("%s",buff);
    }
}