/*----------------------------------------------------------------------------*/
/* Copyright (c) Anirudh B. (anidev) 2012. All Rights Reserved.               */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in this directory.       */
/*----------------------------------------------------------------------------*/

#include "vxWorks.h"
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include "hostLib.h"
#include "errnoLib.h"

int hostGetByName(const char* name) {
	if(name==NULL) {
		errnoSet(S_hostLib_INVALID_PARAMETER);
		return ERROR;
	}
	addrinfo* addr_result;
	addrinfo hints;
	memset(&hints,0,sizeof(hints));
	hints.ai_family=AF_INET;
	hints.ai_socktype=SOCK_STREAM;
	int status=getaddrinfo(name,NULL,&hints,&addr_result);
	if(status!=0) {
		errnoSet(S_hostLib_UNKNOWN_HOST);
		return ERROR;
	}
	sockaddr* s_address=addr_result->ai_addr;
	char* c_address=s_address->sa_data;
	in_addr_t i_address=inet_addr(c_address);
	return i_address;
}
