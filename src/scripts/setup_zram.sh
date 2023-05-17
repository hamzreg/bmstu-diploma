#!/bin/bash

echo $1 > /sys/block/zram0/comp_algorithm
echo $2 > /sys/block/zram0/disksize