/*
 * Copyright (c) 2007 Xilinx, Inc.  All rights reserved.
 *
 * Xilinx, Inc.
 * XILINX IS PROVIDING THIS DESIGN, CODE, OR INFORMATION "AS IS" AS A
 * COURTESY TO YOU.  BY PROVIDING THIS DESIGN, CODE, OR INFORMATION AS
 * ONE POSSIBLE   IMPLEMENTATION OF THIS FEATURE, APPLICATION OR
 * STANDARD, XILINX IS MAKING NO REPRESENTATION THAT THIS IMPLEMENTATION
 * IS FREE FROM ANY CLAIMS OF INFRINGEMENT, AND YOU ARE RESPONSIBLE
 * FOR OBTAINING ANY RIGHTS YOU MAY REQUIRE FOR YOUR IMPLEMENTATION.
 * XILINX EXPRESSLY DISCLAIMS ANY WARRANTY WHATSOEVER WITH RESPECT TO
 * THE ADEQUACY OF THE IMPLEMENTATION, INCLUDING BUT NOT LIMITED TO
 * ANY WARRANTIES OR REPRESENTATIONS THAT THIS IMPLEMENTATION IS FREE
 * FROM CLAIMS OF INFRINGEMENT, IMPLIED WARRANTIES OF MERCHANTABILITY
 * AND FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

#include <stdio.h>
#include <string.h>
#include "lwip/udp.h"
#include "xparameters.h"
#include "netif/xadapter.h"
#include "platform.h"
#include "platform_config.h"
#include "lwipopts.h"
#ifndef __PPC__
#include "xil_printf.h"
#endif

void print_headers();
int start_applications();
int transfer_data();
void platform_enable_interrupts();
void lwip_init(void);
void tcp_fasttmr(void);
void tcp_slowtmr(void);

#if LWIP_DHCP==1
extern volatile int dhcp_timoutcntr;
err_t dhcp_start(struct netif *netif);
#endif
extern volatile int TxPerfConnMonCntr;
extern volatile int TcpFastTmrFlag;
extern volatile int TcpSlowTmrFlag;
struct netif *echo_netif;

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
    struct netif *netif, server_netif;
    struct ip_addr ipaddr, netmask, gw;

    // Added stuff for the creation of a basic UDP
    err_t error;
    struct ip_addr ip_remote;
    struct udp_pcb *udp_1;
    struct pbuf  *p;
    char data[8] = "01234567";
    u16_t  Port = 12;
    int buflen = 8;
    int count = 0;

    /* the mac address of the board. this should be unique per board */
    unsigned char mac_ethernet_address[] = { 0x00, 0x0a, 0x35, 0x00, 0x01, 0x02 };

    netif = &server_netif;

//    if (init_platform() < 0) {
//        xil_printf("ERROR initializing platform.\r\n");
//        return -1;
//    }

    xil_printf("\r\n\r\n");
    xil_printf("-----lwIP RAW Mode Application ------\r\n");
    /* initliaze IP addresses to be used */
#if (LWIP_DHCP==0)
    IP4_ADDR(&ipaddr,  192, 168,   1, 10);
    IP4_ADDR(&netmask, 255, 255, 255,  0);
    IP4_ADDR(&gw,      192, 168,   1,  1);
    print_ip_settings(&ipaddr, &netmask, &gw);
#endif
    lwip_init();

#if (LWIP_DHCP==1)
    ipaddr.addr = 0;
    gw.addr = 0;
    netmask.addr = 0;
#endif

    /* Add network interface to the netif_list, and set it as default */
    if (!xemac_add(netif, &ipaddr, &netmask, &gw, mac_ethernet_address, PLATFORM_EMAC_BASEADDR)) {
        xil_printf("Error adding N/W interface\r\n");
        return -1;
    }
    netif_set_default(netif);

    /* specify that the network if is up */
    netif_set_up(netif);

    /* now enable interrupts */
//    platform_enable_interrupts();

#if (LWIP_DHCP==1)
    /* Create a new DHCP client for this interface.
     * Note: you must call dhcp_fine_tmr() and dhcp_coarse_tmr() at
     * the predefined regular intervals after starting the client.
     */
    dhcp_start(netif);
    dhcp_timoutcntr = 24;
    TxPerfConnMonCntr = 0;
    while(((netif->ip_addr.addr) == 0) && (dhcp_timoutcntr > 0)) {
        xemacif_input(netif);
        if (TcpFastTmrFlag) {
            tcp_fasttmr();
            TcpFastTmrFlag = 0;
        }
        if (TcpSlowTmrFlag) {
            tcp_slowtmr();
            TcpSlowTmrFlag = 0;
        }
    }
    if (dhcp_timoutcntr <= 0) {
        if ((netif->ip_addr.addr) == 0) {
            xil_printf("DHCP Timeout\r\n");
            xil_printf("Configuring default IP of 192.168.1.10\r\n");
            IP4_ADDR(&(netif->ip_addr),  192, 168,   1, 10);
            IP4_ADDR(&(netif->netmask), 255, 255, 255,  0);
            IP4_ADDR(&(netif->gw),      192, 168,   1,  1);
        }
    }
    /* receive and process packets */
    print_ip_settings(&(netif->ip_addr), &(netif->netmask), &(netif->gw));
#endif

    /* start the application (web server, rxtest, txtest, etc..) */
   xil_printf("Setup Done");
    IP4_ADDR(&ip_remote,  192, 168,  1, 11);

    udp_1 = udp_new();

    error = udp_bind(udp_1, IP_ADDR_ANY, Port);

    if (error != 0)
    {
        xil_printf("Failed %d\r\n", error);
    }
    else if (error == 0)
    {
        xil_printf("Success\r\n");
    }
    error = udp_connect(udp_1, &ip_remote, Port);
    if (error != 0)
    {
        xil_printf("Failed %d\r\n", error);
    }
    else if (error == 0)
    {
        xil_printf("Success\r\n");
    }


   while (1)
   {
        xemacif_input(netif);
        count++;
        if (count == 80000)
        {
            p = pbuf_alloc(PBUF_TRANSPORT, buflen, PBUF_POOL);
            if (!p) {
                xil_printf("error allocating pbuf\r\n");
                return ERR_MEM;
            }
            memcpy(p->payload, data, buflen);
            udp_send(udp_1, p);
            xil_printf(" SEND DATA \r\n");
            count = 0;
            pbuf_free(p);
        }

    }

    /* never reached */
    cleanup_platform();

    return 0;
}
