#/bin/bash

v=`ls *.o`
for i in $v;do
    size $v >> log
done
