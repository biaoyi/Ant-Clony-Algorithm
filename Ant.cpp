#include "Ant.h"


Ant::Ant()
{

}

Ant::~Ant()
{

}

void Ant::init(int init_city)
{                            
    for(int i = 0; i < N_CITY; i++)
    {
        allowed[i] = 1;           //重置蚂蚁可以去的城市
        travel[i] = 0;            //重置蚂蚁禁忌表
    }

    distance = 0.0;                              //距离清0
    if(init_city == -1)                          //如果未设置初始城市
    {
        //随机选择一个起始城市
        cur_city = rnd(0,N_CITY);
    }
    allowed[cur_city] = 0;                      //更新禁忌表
    travel[0] = cur_city;                       //更新可去城市表
    num_city = 1;
}

int Ant::chooseCity()
{
    int selected = -1;

    double total = 0.0;
    double prob[N_CITY];                    //保存各个城市被选中的概率
    /*计算当前城市和没有去过城市信息素总和*/
    for(int i = 0; i < N_CITY; i++)
    {
        if(allowed[i] == 1)                 //如果允许去
        {
            /*计算转移到其它城市概率，公式1*/
            prob[i] = pow(city_pher[cur_city][i],ALPHA)*pow(1.0/city_distance[cur_city][i],BETA);
            total += prob[i];
        }
        else                 //否则
            prob[i] = 0.0;
    }

    /*======================轮盘赌选择算法, 结合上面公式，即为公式1全部内容=========================*/
    double temp = 0.0;
    if(total > 0.0)
    {
        temp = rnd(0.0,total);                  //转动轮盘
        // printf("%f\n", temp);
        for(int i = 0; i < N_CITY; i++)
        {
            if(allowed[i] == 1)                 //如果允许去
            {
                temp -= prob[i];
                if(temp < 0.0)                  //轮盘停止
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

void Ant::move()
{
    int select = chooseCity();
    travel[num_city] = select;
    allowed[select] = 0;
    num_city++;
    cur_city = select;
}

void Ant::search()
{
    init();
    while (num_city < N_CITY) {
        move();
    }
    calLength();
}

void Ant::calLength()
{
    distance = 0.0;
    int m=0;
    int n=0;
    for(int i = 1; i < N_CITY; i++)
    {
        m = travel[i];
        n = travel[i-1];
        distance += city_distance[m][n];
    }

    n = travel[0];
    distance += city_distance[m][n];
}
