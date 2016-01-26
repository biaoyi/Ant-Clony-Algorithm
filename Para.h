#ifndef _PARA_H_
#define _PARA_H_

#define _MMANT_
#define _GRID_

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
#define N_CITY 51

#ifndef _MMANT_
#else
/*for max min ant system*/
#define ROU_MM 0.98                     
#define N_ANT_MM 20
#define N_ITER_MM 10000               
#endif
#define Pbest_MM 0.05

#ifndef _GRID_
#else
/*for grid environment*/
#define N_ANT_G 1000
#define N_ITER_G 200
#define ROU_G 0.5
#endif
#define N_GRID 20              // 栅格数目       

extern double PHER;            //总的信息素
extern double DB_MAX;          //一个标志数，10的9次方               

extern const double x_Ary[N_CITY];             //城市x坐标
extern const double y_Ary[N_CITY];             //城市y坐标
extern double city_distance[N_CITY][N_CITY];   //城市间的距离
extern double city_pher[N_CITY][N_CITY];       //城市间信息素

/*for max min ant system*/
extern double g_prob[N_CITY][N_CITY];
extern double city_distance_BETA[N_CITY][N_CITY];

/*for grid environment*/
#define PIX 100.0
#define ANG_PIX 141.42
#define N_CITY_G N_GRID*N_GRID
extern bool g_grid[N_GRID][N_GRID];             //环境模型0代表没有障碍物，1代表有障碍物
extern double grid_pher[N_CITY_G][N_CITY_G];    //城市间信息素

/*tool functions*/
extern int rnd(int nLow,int nUpper);            //返回指定范围内的随机整数
extern double rnd(double dbLow,double dbUpper); //返回指定范围内的随机浮点数
extern double ROUND(double dbA);                //返回浮点数四舍五入取整后的浮点数

#endif