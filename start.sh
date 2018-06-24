#!/bin/bash
echo 1 > /proc/sys/net/ipv4/ip_forward 
geteway=`route -n  | grep $1 | grep UG | awk '{print $2}'`
./arp $1 $geteway
