#!/bin/bash

VM=$1

DATA=$2
SRC=/home/regina/bmstu/bmstu-diploma/src/data/$DATA
DST=/home/user/data

RESET_PATH=/sys/block/zram0/reset
SIZE_PATH=/sys/block/zram0/disksize
STAT_PATH=/sys/block/zram0/mm_stat


ssh user@$VM "rm -rf data && mkdir data"

scp $SRC user@$VM:$DST

ssh root@$VM "echo 1 > $RESET_PATH && echo 1G > $SIZE_PATH"
ssh root@$VM "dd if=$DST/$DATA of=/dev/zram0"
ssh user@$VM "cat $STAT_PATH" > $3
