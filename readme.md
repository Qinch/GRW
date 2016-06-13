### 用于IC芯片热分析的随机行走算法
###  the Generic Random Walk(GRW) method for 3-D thermal analysis of IC
written :  qinchao;     
created :  2014-09-22 21:17:58;    
modified:  2014-10-01 13:07:17;    
modified:  2014-10-03 10:11:49;

关键数据结构：    
	1,grid.cpp:computeprob()函数,用于提前计算每层芯片的概率。     
	2,grwstep.cpp（设计思路见: ../backup/ParaseBits.cpp）。     
	3,堆内存释放函数model.cpp:freemem(),grid.cpp:freemem()。     
	4,支持输入待测点的xy坐标值（相对于该层芯片自身，而非全局坐标系）进行计算功能。     

注意：     
	1,输入文件model1_x.in和powermap1.in对应，model2_x.in和powermap2.in对应。     
	2,输入文件必须是linux系统下生成的文件，如为windows下生成的文件,会发生输入文件读取错误（解决办法:可用dos2unix进行转换）。      
	3,"./bin/grw -h"查看参数设置帮助。     
