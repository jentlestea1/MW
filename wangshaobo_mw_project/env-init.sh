#!/bin/sh

set -x

sudo service nfs-kernel-server restart
sudo exportfs -av

sudo insmod /lib/modules/`uname -r`/kernel/drivers/net/can/vcan.ko
sudo ip link add type vcan
sudo ip link set vcan0 up

#/home/lewton/work/resource/1553server &
