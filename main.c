/*
 * Copyright (C) 2008, 2009, 2010 Kaspar Schleiser <kaspar@schleiser.de>
 * Copyright (C) 2013 INRIA
 * Copyright (C) 2013 Ludwig Knüpfer <ludwig.knuepfer@fu-berlin.de>
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @ingroup     examples
 * @{
 *
 * @file
 * @brief       Default application that shows a lot of functionality of RIOT
 *
 * @author      Kaspar Schleiser <kaspar@schleiser.de>
 * @author      Oliver Hahm <oliver.hahm@inria.fr>
 * @author      Ludwig Knüpfer <ludwig.knuepfer@fu-berlin.de>
 *
 * @}
 */

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "thread.h"
#include "shell.h"
#include "shell_commands.h"
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>

int main(void)
{

    (void) puts("Welcome to RIOT!");

		/* UDP echo server Task*/
	struct sockaddr_in servaddr,cliaddr;
	char buffer[256];

	//UDP create socket
	int s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if(s<0)
	{
		(void) puts("Error in socket creation");
		return -1;
	}
	
	(void) puts("socket created");
	memset(&servaddr,0, sizeof(servaddr));
	memset(&cliaddr,0, sizeof(cliaddr));
	//Filling server information
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = INADDR_ANY;
	servaddr.sin_port = htons(4369);
	
	//bind the socket to receive message from all IPs
	if(bind(s,(const struct sockaddr*)&servaddr,sizeof(servaddr))<0)
	{
		(void) puts("Error in socket binding");
		return -1;
	}
	
	(void) puts("binding successful");
	int n;
	socklen_t len = sizeof(cliaddr);
	while(1)
	{
		n = recvfrom(s, (char*)buffer,sizeof(buffer),0,(struct sockaddr *)&cliaddr,&len);
		if(n<0)
		{
			(void) puts("Error in receiving");
			return -1;		
		}
		buffer[n] = '\0'; 
		//Delay of 1 second
		sleep(1);
		int err= sendto(s,(char*)buffer, n,0,(const struct sockaddr *) &cliaddr,len);
		if(err<0)
		{
			(void) puts("Error in sending");
		}
	}



    return 0;
}
