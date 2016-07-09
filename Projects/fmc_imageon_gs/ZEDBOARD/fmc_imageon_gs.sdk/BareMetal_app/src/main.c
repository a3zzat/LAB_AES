
#include "video/demo.h"
#include "video/avnet_console.h"
#include "video/avnet_console_serial.h"

#include "audio/audio.h"

#include "net/net_main.h"

demo_t demo;
demo_t *pdemo;

AudioData_t* AudioPuf;

volatile int TxPerfConnMonCntr;
volatile int TcpFastTmrFlag;
volatile int TcpSlowTmrFlag;
struct netif *echo_netif;
struct udp_pcb *udp_1;
struct netif *udp_netif;

struct pbuf  *NetPuf;
int buflen;

void udp_recv_callback(void *arg, struct udp_pcb *pcb, struct pbuf *p, struct ip_addr *addr, u16_t port);

void print_headers();
int start_applications();
int transfer_data();
void platform_enable_interrupts();
void lwip_init(void);
void tcp_fasttmr(void);
void tcp_slowtmr(void);

void print_ip(char *msg, struct ip_addr *ip)
{
    print(msg);
    xil_printf("%d.%d.%d.%d\r\n", ip4_addr1(ip), ip4_addr2(ip),
            ip4_addr3(ip), ip4_addr4(ip));
}

void print_ip_settings(struct ip_addr *ip, struct ip_addr *mask, struct ip_addr *gw)
{
    print_ip("Board IP:       ", ip);
    print_ip("Netmask :       ", mask);
    print_ip("Gateway :       ", gw);
}

int main()
{

	xil_printf("--              AudioChip(ADAU1761)                 --\n\r");
	Audio_init();

	xil_printf("--                Gigabit-Ethernet                  --\n\r");
//	net_init(udp_1,udp_netif);
	//register the function recv_callback as the call back for incoming functions
	//this function will be called to process incoming package
//	udp_recv(udp, udp_recv_callback, NULL );

	
	xil_printf("--                    FMC-IMAGEON                   --\n\r");
//	pdemo = &demo;
//	demo_init( pdemo );
//
//	// Init reference design
	demo_init_frame_buffer(pdemo);
//
//	// Try CAM first
//	pdemo->cam_alpha = 0xFF;
//	pdemo->hdmi_alpha = 0x00;
//	if ( !demo_start_cam_in(pdemo) )
//	{
//		// Then try HDMI
//		pdemo->cam_alpha = 0x00;
//		pdemo->hdmi_alpha = 0xFF;
//		demo_start_hdmi_in(pdemo);
//	}
//	demo_start_frame_buffer(pdemo);
//
//	// Start serial console
//	print_avnet_console_serial_app_header();
//	start_avnet_console_serial_application();


//-------------------------------------------------
// 	 buflen = sizeof(AudioPuf);

// 	xemacif_input(udp_netif);
// 	AudioPuf = malloc(sizeof(AudioData_t));
// 	if (!AudioPuf) {
// 		xil_printf("error allocating AudioPuf\r\n");
// 	}
// 	NetPuf = pbuf_alloc(PBUF_TRANSPORT, buflen, PBUF_POOL);
// 	if (!NetPuf) {
// 		xil_printf("error allocating NetPuf\r\n");
// 	}
// 	NetPuf->payload = (void *) AudioPuf;

// 	while (1)
// 	{
// 		read_play(AudioPuf);
// //		memcpy(NetPuf->payload, AudioPuf , buflen);
// 		udp_send(udp_1, NetPuf);
		
// 		// needs delay before sending again  think
// 		if (transfer_avnet_console_serial_data()) {
// 			break;
// 		}


// 	}
//-----------------------------------------------
//My own version of sending and receiving

//	xemacif_input(udp_netif);
	if (!(AudioPuf=malloc(sizeof(AudioData_t)))) {
		xil_printf("error allocating AudioPuf\r\n");
 	}
 	 buflen = sizeof(AudioPuf);

// 	if (!(NetPuf= pbuf_alloc(PBUF_TRANSPORT, buflen, PBUF_POOL))) {
// 		xil_printf("error allocating NetPuf\r\n");
//	}
 	/*
      NetPuf->payload = (void *) AudioPuf;
      
      //create a new udp for sending. The other udp already created is used for receiving
      struct udp_pcb *send_udp = udp_new();
      
      //port for sending udp packets
        u16_t  fwd_port = 5001;
        
        //ip address for sending packets. It should be the same as the IP address of the remote board we are 
        //receiving from
       struct ip_addr forward_ip;
       IP4_ADDR(&forward_ip,  192, 168,   1, 11);
      
      	while (1)
 	{
      		xil_printf("in loop");
 		//read audio packets
 		read_play(AudioPuf);
 		//receiving
 		xil_printf("before send");
// 		udp_recv(udp_1, udp_recv_callback, NULL);
 		xil_printf("after recieve");
 		//sending
         	udp_sendto(send_udp, NetPuf, &forward_ip, fwd_port); //dest port
     		udp_send(udp_1, NetPuf);

         	xil_printf("after send");
 	}
      	*/

//////////////////////////////////////////////////////////////
// 	net init function
//
// 	//////////////////////////////////////
//
//    struct netif server_netif;
//    struct ip_addr ipaddr, netmask, gw;
//
//    // Added stuff for the creation of a basic UDP
//    err_t error;
//    struct ip_addr ip_remote;
////    struct udp_pcb *udp_1;
////    struct pbuf  *p;
////    char data[8] = "01234567";
//    u16_t  Port = 12;
////    int buflen = 8;
////    int count = 0;
//
//    /* the mac address of the board. this should be unique per board */
//    unsigned char mac_ethernet_address[] = { 0x00, 0x0a, 0x35, 0x00, 0x01, 0x02 };
//
//    udp_netif = &server_netif;
//
////    if (init_platform() < 0) {
////        xil_printf("ERROR initializing platform.\r\n");
////        return -1;
////    }
//
//    xil_printf("\r\n\r\n");
//    xil_printf("-----lwIP RAW mode init start ------\r\n");
//    /* initliaze IP addresses to be used */
//#if (LWIP_DHCP==0)
//    IP4_ADDR(&ipaddr,  192, 168,   1, 10);
//    IP4_ADDR(&netmask, 255, 255, 255,  0);
//    IP4_ADDR(&gw,      192, 168,   1,  1);
//    print_ip_settings(&ipaddr, &netmask, &gw);
//#endif
//    lwip_init();
//
//#if (LWIP_DHCP==1)
//    ipaddr.addr = 0;
//    gw.addr = 0;
//    netmask.addr = 0;
//#endif
//
//    /* Add network interface to the netif_list, and set it as default */
//    if (!xemac_add(udp_netif, &ipaddr, &netmask, &gw, mac_ethernet_address, PLATFORM_EMAC_BASEADDR)) {
//        xil_printf("Error adding N/W interface\r\n");
//        return -1;
//    }
//    netif_set_default(udp_netif);
//
//    /* specify that the network if is up */
//    netif_set_up(udp_netif);
//
//    /* now enable interrupts */
////    platform_enable_interrupts();
//
//#if (LWIP_DHCP==1)
//    /* Create a new DHCP client for this interface.
//     * Note: you must call dhcp_fine_tmr() and dhcp_coarse_tmr() at
//     * the predefined regular intervals after starting the client.
//     */
//    dhcp_start(netif);
//    dhcp_timoutcntr = 24;
//    TxPerfConnMonCntr = 0;
//    while(((netif->ip_addr.addr) == 0) && (dhcp_timoutcntr > 0)) {
//        xemacif_input(netif);
//        if (TcpFastTmrFlag) {
//            tcp_fasttmr();
//            TcpFastTmrFlag = 0;
//        }
//        if (TcpSlowTmrFlag) {
//            tcp_slowtmr();
//            TcpSlowTmrFlag = 0;
//        }
//    }
//    if (dhcp_timoutcntr <= 0) {
//        if ((netif->ip_addr.addr) == 0) {
//            xil_printf("DHCP Timeout\r\n");
//            xil_printf("Configuring default IP of 192.168.1.10\r\n");
//            IP4_ADDR(&(netif->ip_addr),  192, 168,   1, 10);
//            IP4_ADDR(&(netif->netmask), 255, 255, 255,  0);
//            IP4_ADDR(&(netif->gw),      192, 168,   1,  1);
//        }
//    }
//    /* receive and process packets */
//    print_ip_settings(&(netif->ip_addr), &(netif->netmask), &(netif->gw));
//#endif
//
//    /* start the application (web server, rxtest, txtest, etc..) */
//   xil_printf("Setup Done \n");
//    IP4_ADDR(&ip_remote,  192, 168,   1, 11);
//
//    udp_1 = udp_new();
//
//    error = udp_bind(udp_1, IP_ADDR_ANY, Port);
//
//    if (error != 0)
//    {
//        xil_printf("Failed %d\r\n", error);
//    }
//    else if (error == 0)
//    {
//        xil_printf("udp_bind() completed successfully\r\n");
//    }
//    error = udp_connect(udp_1, &ip_remote, Port);
//    if (error != 0)
//    {
//        xil_printf("Failed %d\r\n", error);
//    }
//    else if (error == 0)
//    {
//        xil_printf("udp_connect() completed successfully\r\n");
//    }
//
	while (1){
//  		xil_printf("in loop");
		//read audio packets
		read_play(AudioPuf);
//		memcpy(NetPuf->payload, AudioPuf, buflen);
//		xil_printf("before send");
//		xemacif_input(udp_netif);
//		udp_send(udp_1, NetPuf);
//		xil_printf("after recieve");
	}
       //Free the buffer
       pbuf_free(NetPuf);
	return 0;

}

void udp_recv_callback(void *arg, struct udp_pcb *pcb, struct pbuf *p, struct ip_addr *addr, u16_t port){

	xil_printf("received  bytes at port  %d\n",pcb->local_port);
      if (p != NULL) {
      	  printf("Received %d bytes: ", (*p).len);
      	  
      //Send the audio bytes to the line out
      	AudioData_t* AudioOut;
      	AudioOut = p->payload;
      	play_audio(AudioOut);

      	//Send the video bytes to the HDMI output


      	//------------------------------
        pbuf_free(p);
      }
}

