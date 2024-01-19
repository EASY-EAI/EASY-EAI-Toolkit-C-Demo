/* 2. 报文过滤接收程序 */ 
 #include <stdio.h> 
 #include <stdlib.h> 
 #include <string.h> 
 #include <unistd.h> 
 #include <net/if.h> 
 #include <sys/ioctl.h> 
 #include <sys/socket.h> 
 #include <linux/can.h> 
 #include <linux/can/raw.h> 
 
 /* 将CAN0波特率设置为500000 bps */
#define ip_cmd_set_can_params  "ip link set can0 type can bitrate 500000 triple-sampling on"
 
 /* 打开CAN0 */
#define ip_cmd_open            "ifconfig can0 up"     
 
 /* 关闭CAN0 */    
#define ip_cmd_close           "ifconfig can0 down"   

 int main() 
 { 
	 int fd, nbytes; 
	 struct sockaddr_can addr; 
	 struct ifreq ifr; 
	 struct can_frame frame; 
	 struct can_filter rfilter[1];
	  
	system(ip_cmd_close);               
    system(ip_cmd_set_can_params);
	system(ip_cmd_open);
	
	 fd = socket(PF_CAN, SOCK_RAW, CAN_RAW); //创建套接字 
	 strcpy(ifr.ifr_name, "can0" ); 
	 ioctl(fd, SIOCGIFINDEX, &ifr); //指定 can0 设备 
	 addr.can_family = AF_CAN; 
	 addr.can_ifindex = ifr.ifr_ifindex; 
	 bind(fd, (struct sockaddr *)&addr, sizeof(addr)); //将套接字与 can0 绑定 
	 
	 //定义接收规则，只接收表示符等于 0x11 的报文 
	 rfilter[0].can_id = 0x11; 
	 rfilter[0].can_mask = CAN_SFF_MASK; 
	 //设置过滤规则 
	 setsockopt(fd, SOL_CAN_RAW, CAN_RAW_FILTER, &rfilter, sizeof(rfilter)); 
	 while(1)
	 { 
		 nbytes = read(fd, &frame, sizeof(frame)); //接收报文 
		//显示报文 
		 if(nbytes > 0)
		 {
			 printf("ID=0x%X DLC=%d data[0]=0x%X\n", frame.can_id, frame.can_dlc, frame.data[0]); 
		 } 
	} 
	close(fd); 
	return 0; 
}