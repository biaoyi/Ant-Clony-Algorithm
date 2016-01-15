#ifndef _ANT_H_
#define _ANT_H_

#include "Para.h"

//定义蚂蚁
class Ant
{
public:
    int travel[N_CITY];                    //蚂蚁走过的路径，即禁忌表
    int allowed[N_CITY];                   //蚂蚁可以去的城市
    double distance;                       //蚂蚁走过的路径长度
    int cur_city;                          //当前蚂蚁所在城市
    int num_city;
    bool greed;
public:
    virtual void init(int init_city = -1);         //初始化
    virtual void move();                           //移动
    virtual void search();                         //路径搜索
    virtual int chooseCity();                      //选择下一个城市
    virtual void calLength();                      //计算总路径长度

public:
    Ant();
    ~Ant();
};

#endif
