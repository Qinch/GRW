#ifndef SOLVE_H_
#define SOLVE_H_

#include "grid.h"
#include "random.h"

void round(double t,int &ret,double prob,int flag);
void cxy2xy(grid* g,double tx,double ty,int pln,int &x,int &y,double &factor);
double grwsolve(Random &rnd,grid* g,int z,int initlayer,double error,double& hops,int &walks,bool args_a,...);
inline double getfactor(grid *g,int x,int y,int pln)//pln:power laynum,即第pln层芯片；该函数用于获取每次随机行走的反馈的分母;
{
	double factor;
	if( (x==g->minx[pln]) || (x==g->maxx[pln]-1) )
	{
		if( (y==g->miny[pln]) || (y==g->maxy[pln]-1) )
			factor=g->angfactor;
		else
			factor=g->facfactor;				
	}
	else if( (y==g->miny[pln]) || (y==g->maxy[pln]-1) )
		factor=g->facfactor;
	else
		factor=g->powerfactor[pln];
	return factor;
}


#endif /* SOLVE_H_ */
