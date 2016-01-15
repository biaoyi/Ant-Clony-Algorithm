#include "MMAoc.h"
int main(int argc,char** argv)
{
    //用当前时间点初始化随机种子，防止每次运行的结果都相同
    time_t tm;
    time(&tm);
    unsigned int nSeed=(unsigned int)tm;
    srand(nSeed);

    Aoc* aoc;
    if(argc == 1)
    {
        printf("0 for ant clony system and 1 for max-min ant clony system:");
        return 0;
    }
    switch(argv[1][0] - '0')
    {
        case 0:aoc = new Aoc();break;
        case 1:aoc = new MMAoc();break;
    }
    aoc->init();
    aoc->search();
    for(int i = 0; i < N_CITY; i++)
    {
        printf("%d-",aoc->best_ant->travel[i]);
    }
    printf("%d\n",aoc->best_ant->travel[0]);
    printf("%f\n", aoc->best_ant->distance);
}