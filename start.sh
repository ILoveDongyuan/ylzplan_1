#!/bin/bash
echo 1 > /proc/sys/net/ipv4/ip_forward 
geteway=`route -n  | grep $1 | grep UG | awk '{print $2}'`
echo $geteway
gnome-terminal -x bash -c "./packet_analysis.sh $1; exec bash"
./arp $1 $geteway
