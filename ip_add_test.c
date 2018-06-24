/*************************************************************************
	> File Name: ip_add_test.c
	> Author: 
	> Mail: 
	> Created Time: 2018年06月20日 星期三 15时49分46秒
 ************************************************************************/
#include <stdio.h>
#include <string.h>
int main(int argc, char *argv[]){
    char *src_ip_str=(char*)"192.168.199.250";
    char tmp[15];
    strcpy(tmp,argv[1]);
    printf("%s\n",src_ip_str);
    printf("%s\n",tmp);
}
