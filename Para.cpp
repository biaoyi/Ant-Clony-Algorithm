#include "Para.h"

double x_Ary[N_CITY]=
{
    37,49,52,20,40,21,17,31,52,51,
    42,31,5,12,36,52,27,17,13,57,
    62,42,16,8,7,27,30,43,58,58,
    37,38,46,61,62,63,32,45,59,5,
    10,21,5,30,39,32,25,25,48,56,
    30
};    

double y_Ary[N_CITY]=
{
    52,49,64,26,30,47,63,62,33,21,
    41,32,25,42,16,41,23,33,13,58,
    42,57,57,52,38,68,48,67,48,27,
    69,46,10,33,63,69,22,35,15,6,
    17,10,64,15,10,39,32,55,28,37,
    40
};

double PHER = 100.0;
double DB_MAX = 10e9; 

double city_distance[N_CITY][N_CITY];   
double city_pher[N_CITY][N_CITY];  

double g_prob[N_CITY][N_CITY];
double city_distance_BETA[N_CITY][N_CITY];     


int rnd(int nLow,int nUpper)
{
    return nLow + rand()%(nUpper - nLow);
    //return nLow+(nUpper-nLow)*rand()/((int)RAND_MAX+1);
}

double rnd(double dbLow,double dbUpper)
{
    double dbTemp=rand()/((double)RAND_MAX+1.0);
    return dbLow+dbTemp*(dbUpper-dbLow);
}

double ROUND(double dbA)
{
    return (double)((int)(dbA+0.5));
}