#ifndef RNG_H
#define RNG_H

#ifdef __cplusplus
extern "C" {
#endif

// Declare the functions and variables
void set_seeds(int x, int y, int z, int w);
int rng();

#ifdef __cplusplus
}
#endif

#endif // RNG_H