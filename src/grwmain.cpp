#include "argsparase.h"
#include "model.h"
#include "grid.h"
#include "random.h"
#include "grwsolve.h"

int main(int argc,char** argv)
{
	struct grid g;
	args_parase(argc,argv);//参数解析;
	Random rand;
	read(&(g.m),args_model);//读取model文件;
	buildgrid(&g);
	readpowermap(&g,args_powermap);//读取powermap文件;

	int z=0;
	for (int i=0; i<g.maxz; i++)
		if(g.power[i])
		{
			z=i;//第几层体积元;
			break;
		}
	int pln=0;
	for (int i=0; i<g.m.laynum; i++)
	{
		//powerplayer层体积元属于第几层芯片;
		if (g.zval[i]>z)
		{
			pln=i;
			break;
		}
	}
	int x,y;
	int walks;
	double top=0;
	double temp,hops;
	int tp;
	double factor;//待测点位于power层的哪个位置，facotor=g.powerfacotr[1],表示内部，\
			factor=g.facfactor表示位于侧面（非两个侧面的夹角）,scale=g.angfactor表示位于两个侧面的夹角；
	if(args_a)//-a,--auto,表示自动计算;
	{
		tp=args_points;//待测点的个数;
	}
	else
		tp=cx.size();
	
	for (int i=0; i<tp; i++)
	{
		walks=0;
		temp=0;
		hops=0;
		if(args_a)//生成随机计算的体积元;
		{
			x=rand.getrand()*(g.maxx[pln]-g.minx[pln])+g.minx[pln];
			y=rand.getrand()*(g.maxy[pln]-g.miny[pln])+g.miny[pln];
			/*{
					if(i%4==0)
					{
							x=36;
							y=32;
					}
					else if(i%4==1)
					{
							x=36;
							y=33;
					}
					else if(i%4==2)
					{
							x=37;
							y=32;
					}
					else
					{
							x=37;
							y=33;
					}	

			}*/
			factor=getfactor(&g,x,y,pln);
			temp=grwsolve(rand,&g,z,pln,0.01,hops,walks,true,x,y,factor);
			top=temp>top?temp:top;
			printf("(%d,%d) T=%lf,avg.hops=%lf,walks=%d\n",x,y,temp,hops,walks);
		}
		else//计算手工输入的坐标点;
		{
			double tx=0,ty=0;
			tx=cx[i]+g.m.x1[pln];//相对与全局坐标系的xy值;
			ty=cy[i]+g.m.y1[pln];

			tx=tx/g.m.dxy;
			ty=ty/g.m.dxy;
			temp=grwsolve(rand,&g,z,pln,0.01,hops,walks,false,tx,ty);//z为体积元的层数;
			top=temp>top?temp:top;
			printf("(%lf,%lf) T=%lf,avg.hops=%lf,walks=%d\n",cx[i],cy[i],temp,hops,walks);
		}
	}
	printf("Top:%lf\n",top);
	freemem(&g);
	return 0;
}

