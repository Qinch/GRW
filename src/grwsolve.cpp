#include<stdarg.h>
#include "grid.h"
#include "grwsolve.h"
#include "grwstep.h"

#define LONGWALK 29999999

inline void round(double t,int &ret,double prob,int flag, Random &rnd)
{
	if(rnd.getrand()<prob)
	{
		ret=(int)t+flag;
	//	fprintf(stderr,"prob=%lf  %d  %d\n",prob,ret,ret-flag);
	}	
	else
		ret=(int)t;
		//fprintf(stderr,"%d\n",ret);
	return;
}

inline void cxy2xy(grid* g,double tx,double ty,int pln,int &x,int &y,double &factor,Random &rnd)
{
		double pm;
		if( ((g->minx[pln]+0.5)>tx) || ((g->maxx[pln]-0.5)<tx) )
		{
			if( (ty<(g->miny[pln]+0.5)) || (ty>(g->maxy[pln]-0.5)) )//位于四个角;
			{
				x=(int)tx;
				y=(int)ty;
			}
			else
			{
				x=(int)tx;
				if( ty< ((int)ty+0.5) )
				{
					pm=0.5-(ty-(int)ty);
					round(ty,y,pm,-1,rnd);
				}
				else
				{
					pm=(ty-(int)ty-0.5);
					round(ty,y,pm,1,rnd);
				}
			}
		}
		else if( (ty<(g->miny[pln]+0.5)) || (ty>(g->maxy[pln]-0.5)) )
		{
			if( tx< ((int)tx+0.5) )
			{
				pm=0.5-(tx-(int)tx);
				round(tx,x,pm,-1,rnd);
			}
			else
			{
				pm=(tx-(int)tx-0.5);
				round(tx,x,pm,1,rnd);
			}
			y=(int)ty;
		}
		else
		{
				if( tx< ((int)tx+0.5) )
				{
					pm=0.5-(tx-(int)tx);
					round(tx,x,pm,-1,rnd);
				}
				else
				{
					pm=(tx-(int)tx-0.5);
					round(tx,x,pm,1,rnd);
				}
		
				if( ty<((int)ty+0.5) )
				{
					pm=0.5-(ty-(int)ty);
					round(ty,y,pm,-1,rnd);
				}
				else
				{
					pm=(ty-(int)ty-0.5);
					round(ty,y,pm,1,rnd);
				}
		}
		factor=getfactor(g,x,y,pln);
		return ;
}

double grwsolve(Random &rnd,grid* g,int z,int initlayer,double error,double& hops,int &walks,bool args_a,...)//采用变长参数实现;
{
    		//随机行走终止条件；
		//sqrt((sum(t^2)-sum(t)^2/n)/n)/sqrt(n)<err  
		//	sum(t^2)-sum(t)^2/n<n^2*err^2
		//	sum(t)^2/n>sum(t^2)-n^2*err^2
		//  To:sum(t)^2>n(sum(t^2)-n^2*err^2)
		//err=error*sum(t)/n
		//Thus, sum(t)^2>n(sum(t^2)-error^2*t^2)

		walks=0;
		hops=0;
		double factor;		
		double t=0;
		double tsquare=0;
		
		int x,y;
		double tx,ty;
		va_list args;
		va_start(args,args_a);
		if(args_a)//随机生成待测点，自动计算;
		{
			x=va_arg(args,int);
			y=va_arg(args,int);
			factor=va_arg(args,double);
		}
		else//手工输入待测点xy坐标;
		{
			tx=va_arg(args,double);
			ty=va_arg(args,double);
		}
		va_end(args);

		while( (walks<50) || (t*t)< walks*(tsquare-t*t*error*error) )
		{
				if(!args_a)//将手工输入的xy坐标点转换为体积元个数计数;
				{
					cxy2xy(g,tx,ty,initlayer,x,y,factor,rnd);
				}
				int step=0;
				int walkx=x,walky=y,walkz=z;
				double patht=0;//该次随机行走计算得到的温度;
				int layer=initlayer;

				while(walkz<g->maxz)
				{
					if (g->power[walkz]!=NULL)
					{
						if (g->power[walkz][walkx]!=NULL)
						{
							patht+=g->power[walkz][walkx][walky];
						}
					}
					step++;
					if (step>=LONGWALK)
						break;
					grwstep(g,walkx,walky,walkz,layer,rnd);
				
				}//一次随机行走结束;
				hops+=step;
				if (step>=LONGWALK)
						continue;
				patht=patht/factor;	
				patht+=g->m.tout;//加上环境温度;
				walks++;
				t+=patht;
				tsquare+=patht*patht;
    		}
			hops/=walks;
    		return t/walks;

}
