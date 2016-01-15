#ifndef _PARA_H_
#define _PARA_H_

#define _MMANT_

#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <vector>
#include <list>
#include <algorithm>
#include <time.h>

#define ALPHA 1.0                   //参数alpha
#define BETA 2.0                    //参数beta
#define ROU 0.5                     //参数rou
#define N_ANT 50                    //蚂蚁数量
#define N_ITER 1000                 //迭代次数

#ifndef _MMANT_
#else
/*for max min ant system*/
#define ROU_MM 0.98                     
#define N_ANT_MM 20
#define N_ITER_MM 10000               
#endif
#define Pbest_MM 0.05

#define N_CITY 51


extern double PHER;                  //总的信息素
extern double DB_MAX;                 //一个标志数，10的9次方               

extern double x_Ary[N_CITY];                   //城市x坐标
extern double y_Ary[N_CITY];                   //城市y坐标
extern double city_distance[N_CITY][N_CITY];   //城市间的距离
extern double city_pher[N_CITY][N_CITY];       //城市间信息素

/*for max min ant system*/
extern double g_prob[N_CITY][N_CITY];
extern double city_distance_BETA[N_CITY][N_CITY];

/*tool functions*/
extern int rnd(int nLow,int nUpper);            //返回指定范围内的随机整数
extern double rnd(double dbLow,double dbUpper); //返回指定范围内的随机浮点数
extern double ROUND(double dbA);                //返回浮点数四舍五入取整后的浮点数

#endif