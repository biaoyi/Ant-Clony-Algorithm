#include "GridAoc.h"
int main(int argc,char** argv)
{
    //用当前时间点初始化随机种子，防止每次运行的结果都相同
    time_t tm;
    time(&tm);
    unsigned int nSeed=(unsigned int)tm;
    srand(nSeed);

    GridAoc aoc;
    aoc.init(1,1,18,18);
    aoc.search();
    int i = 0;
    for(i = 0; i < aoc.best_ant.num_city; i++)
    {
        printf("[%d,%d]->",DECODE_X(aoc.best_ant.road[i]),DECODE_Y(aoc.best_ant.road[i]));
    }
    printf("[%d,%d]\n",DECODE_X(aoc.best_ant.road[i]),DECODE_Y(aoc.best_ant.road[i]));
    // printf("%d\n",aoc->best_ant->travel[0]);
    // printf("%f\n", aoc->best_ant->distance);
}