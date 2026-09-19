#!/bin/sh

RESULTDIR=result/

if [ ! -d ${RESULTDIR} ];
then
    mkdir ${RESULTDIR}
fi
    

. ./params.sh

echo seq: starting bench at $(date)

for intensity in $INTENSITIES;
do
    for n in $NSPLOT;
    do
	./sequential 1 0 10 ${n} ${intensity} 2>${RESULTDIR}/sequential_${n}_${intensity}  >/dev/null
    done
done

echo seq: ending bench at $(date)
