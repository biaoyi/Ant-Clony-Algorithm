#ifndef _MMANT_H_
#define _MMANT_H_

#include "Ant.h"

class MMAnt : public Ant{
public:
//    bool greed;                           //是否使用贪心原则选择下一城市

public:
    MMAnt();
    virtual void init(int init_city = -1);         //初始化
    virtual void move();                           //移动
    virtual void search();                         //路径搜索
    virtual int chooseCity();                      //选择下一个城市
    virtual void calLength();                      //计算总路径长度

    virtual int greedChooseCity();                //使用贪心原则选择下一城市
};

#endif
