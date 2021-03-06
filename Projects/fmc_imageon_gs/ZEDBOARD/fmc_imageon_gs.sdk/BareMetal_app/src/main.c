
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
	pdemo = &demo;
	demo_init( pdemo );

	// Init reference design
	demo_init_frame_buffer(pdemo);

	// Try CAM first
	pdemo->cam_alpha = 0xFF;
	pdemo->hdmi_alpha = 0x00;
	if ( !demo_start_cam_in(pdemo) )
	{
		// Then try HDMI
		pdemo->cam_alpha = 0x00;
		pdemo->hdmi_alpha = 0xFF;
		demo_start_hdmi_in(pdemo);
	}
	demo_start_frame_buffer(pdemo);

	// Start serial console
	print_avnet_console_serial_app_header();
	start_avnet_console_serial_application();


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

//xemacif_input(udp_netif);
	if (!(AudioPuf=malloc(sizeof(AudioData_t)))) {
		xil_printf("error allocating AudioPuf\r\n");
 	}
// 	 buflen = sizeof(AudioPuf);
//
// 	if (!(NetPuf= pbuf_alloc(PBUF_TRANSPORT, buflen, PBUF_POOL))) {
// 		xil_printf("error allocating NetPuf\r\n");
//	}
//      NetPuf->payload = (void *) AudioPuf;
      
      //create a new udp for sending. The other udp already created is used for receiving
//      struct udp_pcb *send_udp = udp_new();
      
      //port for sending udp packets
//        u16_t  fwd_port = 5001;
        
        //ip address for sending packets. It should be the same as the IP address of the remote board we are 
        //receiving from
//       struct ip_addr forward_ip;
//       IP4_ADDR(&forward_ip,  192, 168,   1, 11);
      
      	while (1)
 	{
 		//read audio packets
 		read_play(AudioPuf);
 		//receiving
// 		udp_recv(udp_1, udp_recv_callback, NULL);
 		//sending
//         	udp_sendto(send_udp, NetPuf, &forward_ip, fwd_port); //dest port
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

