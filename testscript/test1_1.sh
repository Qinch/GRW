#########################################################################
# File Name: test1_1.sh
# Author: qinchao 
# mail: 1187620726@qq.com
# Created Time: Date:2014-09-22 Time:11:18:41.
#########################################################################
#!/bin/bash
#{ time ../bin/grw -m ../data/model1_1.in -p ../data/powermap1.in -a -n 500 >m1_1.out;} 2>time1_1.out
{ time ../bin/grw -m ../data/model1_1.in -p ../data/powermap1.in -c [6.5e-3,2.5e-3]\,[7.5e-3,3.5e-3] >m1_1x.out;} 2>time1_1x.out
