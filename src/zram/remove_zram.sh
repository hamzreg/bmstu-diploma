#!/bin/bash

echo $1 > /sys/class/zram-control/hot_remove
