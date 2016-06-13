#ifndef GRWSTEP_H_
#define GRWSTEP_H_

#include "grid.h"
#include"random.h"

unsigned short setBits(unsigned short st[],int n);
bool changePos(unsigned short sh,grid *g,int &x,int &y,int &z,int &layer);


//xyz分别表示第x，y,z个体积元的中心点，而非体积元中心点坐标;
void grwstep(grid* g,int& x,int& y,int& z,int& layer,Random &rnd);


#endif /* GRWSTEP_H_ */
