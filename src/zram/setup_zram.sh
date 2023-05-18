#!/bin/bash

echo $1 > /sys/block/zram$3/comp_algorithm
echo $2 > /sys/block/zram$3/disksize
