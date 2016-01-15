#include "MMAnt.h"

MMAnt::MMAnt()
{
    greed = false;
}

void MMAnt::init(int init_city)
{
    Ant::init();
    //greed = false;
}

void MMAnt::move()
{
    int select = 0;

    if(greed)
        select = greedChooseCity();
    else
        select = chooseCity();

    travel[num_city] = select;
    allowed[select] = 0;
    num_city++;
    cur_city = select;
}

void MMAnt::search()
{
    init();
    while(num_city < N_CITY)
    {
        move();
    }
    calLength();
}

int MMAnt::chooseCity()
{
    int selected = -1;

    double total = 0.0;
    double prob[N_CITY];      //保存各个城市被选中的概率
    /*计算当前城市和没有去过城市信息素总和*/
    for(int i = 0; i < N_CITY; i++)
    {
        if(allowed[i] == 1)                 //如果允许去
        {
            /*计算转移到其它城市概率，公式1*/
            //prob[i] = pow(city_pher[cur_city][i],ALPHA)*pow(1.0/city_distance[cur_city][i],BETA);
            prob[i] = g_prob[cur_city][i];
            total += prob[i];
        }
        else                 //否则
            prob[i] = 0.0;
    }

    /*======================轮盘赌选择算法, 结合上面公式，即为公式1全部内容=========================*/
    double temp = 0.0;
    if(total > 0.0)
    {
        temp = rnd(0.0,total);               //转动轮盘
        for(int i = 0; i < N_CITY; i++)
        {
            if(allowed[i] == 1)                 //如果允许去
            {
                temp -= prob[i];
                if(temp < 0.0)                     //轮盘停止
                {
                    selected = i;
                    break;
                }
            }
        }
    }

    //==============================================================================
    /*如果城市间的信息素非常小 ( 小到比double能够表示的最小的数字还要小 )
   那么由于浮点运算的误差原因，上面计算的概率总和可能为0
   会出现经过上述操作，没有城市被选择出来
   出现这种情况，就把第一个没去过的城市作为返回结果*/
    if(selected == -1)
    {
        printf("NO selected\n");
        for(int i = 0; i < N_CITY; i++)
        {
            if(allowed[i] == 1)
            {
                selected = i;
                break;
            }
        }
    }

    return selected;
}

void MMAnt::calLength()
{
    Ant::calLength();
}

int MMAnt::greedChooseCity()
{
    int select = -1;
    double len = DB_MAX;

    for (int i = 0; i < N_CITY; ++i)
    {
        if (allowed[i] == 1 && city_distance[cur_city][i] < len)
        {
            select = i;
            len = city_distance[cur_city][i];
        }
    }

    return select;
}