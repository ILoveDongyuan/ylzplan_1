
/*************************************************************************
	> File Name: arp.c
	> Author: zhangxiaofei
	> Mail: 876008816@qq.com
	> Created Time: 2017年12月09日 星期六 12时39分12秒
 ************************************************************************/

    #include <stdio.h>  
    #include <libnet.h>  
    #include <string.h>
   // #define 
    int main(int argc, char *argv[])
    //argv[1]:eth0 or wlan0
    //argv[2]:src_ip_str
    {  
        if(argc != 3)
        {
            printf("Error: not set device and src_ip_str.\n");
            return 0;
        }
        int res;  
        /*********init paras*****************/  
        libnet_t *l;/*****libnet handler*/  
        libnet_ptag_t p_tag;  
        //char *device=(char*)"eth0";
        char device[5];
        strcpy(device, argv[1]);
        char err_buff[LIBNET_ERRBUF_SIZE];  
        //char *src_ip_str="192.168.199.250";  
        char src_ip_str[15];
        strcpy(src_ip_str, argv[2]);
        char *dest_ip_str=(char*)"0.0.0.0";  
        //char *temp_ip[4];
        //u_char src_mac[6]={0x90,0x2e,0x1c,0xbb,0x11,0x33};  
        u_char src_mac[6]={0xec,0xaa,0xa0,0x1b,0x54,0x21};  
        u_char dest_mac[6]={0xff,0xff,0xff,0xff,0xff,0xff};  
        u_long src_ip;  
        u_long dest_ip;
        src_ip=libnet_name2addr4(l,src_ip_str,LIBNET_RESOLVE);  
        dest_ip=libnet_name2addr4(l,dest_ip_str,LIBNET_RESOLVE);  
        /**********init libnet*****************/  
        l=libnet_init(  
            LIBNET_LINK_ADV,  
            device,  
            err_buff  
        ); 
     //   printf("%s\n",libnet_addr2name4(libnet_get_ipaddr4(l),LIBNET_DONT_RESOLVE));
     //   temp_ip[0] = strtok(libnet_addr2name4(libnet_get_ipaddr4(l)),".");
     //   temp_ip[1] = strtok(libnet_addr2name4(libnet_get_ipaddr4(l)),".");
     //   temp_ip[2] = strtok(libnet_addr2name4(libnet_get_ipaddr4(l)),".");
     //   temp_ip[3] = "1";

     //   printf("%u\n",libnet_get_ipaddr4(l));
        if(l==NULL)  
        {  
            printf("libnet_init err!/n");  
            fprintf(stderr,"%s",err_buff);  
            exit(0);  
        }  
        /**********build arp packet************/  
        p_tag=libnet_build_arp(  
            ARPHRD_ETHER,/*hardware type ethernet*/  
            ETHERTYPE_IP,/*protocol type*/  
            6,/*length of mac*/  
            4,/*length of IP*/  
            ARPOP_REPLY,/*ARP operation type*/  
            src_mac,  
            (u_int8_t*) &src_ip,  
            dest_mac,  
            (u_int8_t*) &dest_ip,  
            NULL,/*payload*/  
            0,/*payload size*/  
            l,/*libnet handler*/  
            0/*'0' stands out building a new packet*/  
        );  
        if(p_tag==-1)  
        {  
            printf("libnet_build_arp err!/n");  
            exit(0);  
        }  
        /***********build ethernet packet header*************/  
        p_tag=libnet_build_ethernet(  
            dest_mac,  
            src_mac,  
            ETHERTYPE_ARP,  
            NULL,  
            0,  
            l,  
            0  
        );  
        if(p_tag==-1)  
        {  
            printf("libnet_build_ethernet err!/n");  
            exit(0);  
        }  
        /*********send packets*******************************/  
        for(;;)  
        {  
            if((res=libnet_write(l))==-1)  
            {  
                printf("libnet_write err!/n");  
                exit(0);  
            }  
            printf("arp packet has been sent/n");  
            sleep(1);  
        }  
        /*********over and destroy**************************/  
        libnet_destroy(l);  
        return 0;  
    }  
