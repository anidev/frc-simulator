/*----------------------------------------------------------------------------*/
/* Copyright (c) Anirudh B. (anidev) 2012. All Rights Reserved.               */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in this directory.       */
/*----------------------------------------------------------------------------*/

#include "vxWorks.h"
#include <sys/socket.h>
#include <sys/select.h>
#include <fcntl.h>
#include <time.h>
#include "sockLib.h"

// sockLib
STATUS connectWithTimeout(int sock,sockaddr* addr,int addr_len,timeval* time_val) {
	fcntl(sock, F_SETFL, O_NONBLOCK);
	fd_set fdset;
	FD_ZERO(&fdset);
	FD_SET(sock,&fdset);
	connect(sock,addr,sizeof(*addr));
	if (select(sock+1,NULL,&fdset,NULL,time_val) == 1) {
		int sock_error;
		socklen_t len=sizeof(sock_error);
		getsockopt(sock,SOL_SOCKET,SO_ERROR,&sock_error,&len);
		if (sock_error == 0) {
			return OK;
		} else {
			return ERROR;
		}
	} else {
		return ERROR;
	}
}
