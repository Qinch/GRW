#ifndef GRWSTEP_H_
#define GRWSTEP_H_

#include "grid.h"
#include"random.h"

unsigned short setBits(unsigned short st[],int n);
bool changePos(unsigned short sh,grid *g,int &x,int &y,int &z,int &layer);


//xyz�ֱ��ʾ��x��y,z�����Ԫ�����ĵ㣬�������Ԫ���ĵ�����;
void grwstep(grid* g,int& x,int& y,int& z,int& layer,Random &rnd);


#endif /* GRWSTEP_H_ */
