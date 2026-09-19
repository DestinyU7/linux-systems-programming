#!/bin/sh

RESULTDIR=result/

if [ ! -e .passed_static ];
then
    echo "You must pass all test before submitting"
    mkdir ${RESULTDIR}
fi

if [ ! -d ${RESULTDIR} ];
then
    mkdir ${RESULTDIR}
fi
    

# $INTENSITIES and $NSPLOT
. ./params.sh
SYNCS="iteration thread"

# debugging statments 
echo before starting time is $(date)

for THREAD in $THREADS;
do 
    echo running Thread Number=${THREAD} Case
    for intensity in $INTENSITIES;
    do
        for n in $NSPLOT;
        do
            for sync in ${SYNCS};
            do
              ./static_sched 1 0 10 ${n} ${intensity} ${THREAD} ${sync} 2>${RESULTDIR}/static_${n}_${intensity}_${THREAD}_${sync}  >/dev/null 
            done
        done
    done
done

echo after ending time is $(date)
