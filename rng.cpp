#include "rng.h"

#define X 0
#define Y 1
#define Z 2
#define W 3

int seeds[4] = {X, Y, Z, W};
void set_seeds(int x, int y, int z, int w)
{
    seeds[X] = x;
    seeds[Y] = y;
    seeds[Z] = z;
    seeds[W] = w;
}
int rng()
{
    //http://www.jstatsoft.org/v08/i14/paper
    int tmp  = (seeds[X]^(seeds[X]<<15));
    seeds[X] = seeds[Y];
    seeds[Y] = seeds[Z];
    seeds[Z] = seeds[W];
    seeds[W] = (seeds[W]^(seeds[W]^(seeds[W]>>21)) ^ (tmp^(tmp>>4)));
    return seeds[W];
}