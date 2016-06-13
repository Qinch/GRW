#rm time1.out
#touch time1.out
{ time ../bin/grw -m ../data/model1_1.in -p ../data/powermap1.in  -n 1000 -a  > m1_1.out ; } 2>> time1.out
#{ time ../bin/grw -m ../data/model1_2.in -p ../data/powermap1.in -a -n 1000 > m1_2.out ; } 2>> time1.out
#{ time ../bin/grw -m ../data/model1_3.in -p ../data/powermap1.in -a -n 1000  > m1_3.out ; } 2>> time1.out

