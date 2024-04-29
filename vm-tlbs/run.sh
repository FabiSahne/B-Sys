#!/bin/bash
make

rm times.csv

for i in {1,2,4,8,16,32,64,128,256,512,1024}
do ./tlb -p $i -n 1000000 >> times.csv;
    echo "Done with $i";
done
echo "Done"

./plot.py