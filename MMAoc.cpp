#include "MMAoc.h"

MMAoc::MMAoc()
{

}

MMAoc::~MMAoc()
{

}

void MMAoc::init()
{
    best_ant = new MMAnt();
    best_ant->distance = DB_MAX;
    double tmp = 0.0;
    for (int i = 0; i < N_ANT_MM; ++i)
    {
        ants[i] = new MMAnt();
    }
    for (int i = 0; i < N_CITY; ++i)
    {
        for (int j = 0; j < N_CITY; ++j)
        {
            city_distance[i][j] = ROUND(sqrt(pow(x_Ary[i] - x_Ary[j],2) + pow(y_Ary[i] - y_Ary[j],2)));
            city_distance_BETA[i][j] = pow(1.0/city_distance[i][j],BETA);
        }
    }

    //用贪心算法生成最开始的解
    best_ant->init();
    best_ant->greed = true;
    best_ant->search();

    double Imax = 1.0/(best_ant->distance*(1 - ROU_MM));

    //初始化环境信息素
    for (int i = 0; i < N_CITY; i++)
    {
        for (int j = 0; j < N_CITY; j++)
        {
            city_pher[i][j] = Imax;

            g_prob[i][j] = pow(Imax,ALPHA)*city_distance_BETA[i][j];
        }
    }

    //计算最大和最小信息素之间的比值
    //dbTemp=pow(Pbest,1.0/(double)N_CITY_COUNT); //对Pbest开N_CITY_COUNT次方
    double dbTemp = exp(log(Pbest_MM)/(double)N_CITY); //对Pbest开N_CITY_COUNT次方
    double dbFz = 2.0*(1.0 - dbTemp);
    double dbFm = ((double)N_CITY-2.0)*dbTemp;
    m_dbRate=dbFz/dbFm;
    printf("%f,%f,%f,%f\n", dbFz,dbFm,m_dbRate,best_ant->distance);
}

void MMAoc::search()
{

    char cBuf[256];

    for (int i = 0; i < N_ITER_MM; i++)
    {
        //每只蚂蚁搜索一遍
        for (int j = 0; j < N_ANT_MM; j++)
        {
            ants[j]->search(); 
        }

        //保存最佳结果
        for (int j = 0; j < N_ANT_MM; j++)
        {
            if (ants[j]->distance < best_ant->distance)
            {
                *best_ant = *ants[j];
            }
        }

        //更新环境信息素
        update();

        //输出结果
        sprintf(cBuf,"[%d] L=%.0f\n",i+1,best_ant->distance);
        printf("%s",cBuf);
    }
}

void MMAoc::update()
{
    //临时保存信息素
    double dbTempAry[N_CITY][N_CITY];
    memset(dbTempAry,0,sizeof(dbTempAry)); //先全部设置为0

    //计算新增加的信息素,保存到临时数组里
    int m = 0;
    int n = 0;
    //计算目前最优蚂蚁留下的信息素
    for (int j = 1; j < N_CITY; j++)
    {
        m = best_ant->travel[j];
        n = best_ant->travel[j-1];
        dbTempAry[n][m] = dbTempAry[n][m] + 1.0/best_ant->distance;
        dbTempAry[m][n] = dbTempAry[n][m];
    }

    //最后城市和开始城市之间的信息素
    n = best_ant->travel[0];
    dbTempAry[n][m] = dbTempAry[n][m] + 1.0/best_ant->distance;
    dbTempAry[m][n] = dbTempAry[n][m];


    //==================================================================
    //更新环境信息素
    for (int i = 0; i < N_CITY; i++)
    {
        for (int j = 0; j < N_CITY; j++)
        {
            city_pher[i][j] = city_pher[i][j]*ROU_MM + dbTempAry[i][j];  //最新的环境信息素 = 留存的信息素 + 新留下的信息素
        }
    }

    //==================================================================
    //检查环境信息素，如果在最小和最大值的外面，则将其重新调整
    double Imax = 1.0/(best_ant->distance*(1.0-ROU_MM));
    double Imin = Imax*m_dbRate;

    for (int i = 0; i < N_CITY; i++)
    {
        for (int j = 0; j < N_CITY; j++)
        {
            if (city_pher[i][j] < Imin)
            {
                city_pher[i][j] = Imin;
            }

            if (city_pher[i][j] > Imax)
            {
                city_pher[i][j] = Imax;
            }

        }
    }


    for (int i = 0; i < N_CITY; i++)
    {
        for (int j = 0; j < N_CITY; j++)
        {
            g_prob[i][j] = pow(city_pher[i][j],ALPHA)*city_distance_BETA[i][j];
        }
    }
}