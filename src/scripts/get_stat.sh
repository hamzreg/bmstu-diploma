#!/bin/bash

VM1=$1
VM2=$2

DATA=$3
SRC=/home/regina/bmstu/bmstu-diploma/src/scripts/data/$DATA
DST=/home/user/data

RESET_PATH=/sys/block/zram0/reset
SIZE_PATH=/sys/block/zram0/disksize
STAT_PATH=/sys/block/zram0/mm_stat

VM1_STAT=/home/regina/bmstu/bmstu-diploma/src/scripts/stat/vm1
VM2_STAT=/home/regina/bmstu/bmstu-diploma/src/scripts/stat/vm2


ssh user@$VM1 "rm -rf data && mkdir data"

scp $SRC user@$VM1:$DST

ssh root@$VM1 "echo 1 > $RESET_PATH && echo 1G > $SIZE_PATH"
ssh root@$VM1 "dmesg -c"
ssh root@$VM1 "dd if=$DST/$DATA of=/dev/zram0"

ssh user@$VM1 "cat $STAT_PATH" > $VM1_STAT/mm_stat.txt
ssh root@$VM1 "dmesg | grep zram" > $VM1_STAT/logfile.txt

python3 table.py n $VM1_STAT/logfile.txt csv


ssh user@$VM2 "rm -rf data && mkdir data"

scp $SRC user@$VM2:$DST

ssh root@$VM2 "echo 1 > $RESET_PATH && echo 1G > $SIZE_PATH"
ssh root@$VM2 "dmesg -c"
ssh root@$VM2 "dd if=$DST/$DATA of=/dev/zram0"

ssh user@$VM2 "cat $STAT_PATH" > $VM2_STAT/mm_stat.txt
ssh root@$VM2 "dmesg | grep zram:" > $VM2_STAT/logfile.txt

python3 table.py y $VM2_STAT/logfile.txt csv
