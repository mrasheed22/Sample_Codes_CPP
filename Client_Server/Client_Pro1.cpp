/*
 * Client_Pro1.cpp
 *
 *  Created on: 16-Nov-2021
 *      Author: sands
 */

#include <cstdio> 		//sprintf()
#include <iostream>
#include <string.h>		//strlen()
#include <unistd.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>	//inet_addr
#define PORT 8080

using namespace std;

struct sockaddr_in server;

int socket_desc;

char *message , server_reply[2000];
char ping_Query[60];

int main(int argc , char *argv[])
{
	//Create socket
	socket_desc = socket(AF_INET , SOCK_STREAM , 0);
	if (socket_desc == -1){
		cout <<"Could not create socket"<< endl;
	}

	sprintf(ping_Query,"ping -c1 -s1 %s  > /dev/null 2>&1",argv[1]);
	int ping_rsp_sts = system(ping_Query);
	if (ping_rsp_sts == 0){
	    cout <<"Ping "<< argv[1] <<" success"<< endl;

	    server.sin_addr.s_addr = inet_addr(argv[1]);
		server.sin_family = AF_INET;
		server.sin_port = htons( PORT );

		//Connect to remote server
		if (connect(socket_desc , (struct sockaddr *)&server , sizeof(server)) < 0){
			cout <<"connect error"<< endl;
			return 1;
		}

		cout <<"Connected"<< endl;

		//Send some data
		message = "Hello from Client\n";
		if( send(socket_desc , message , strlen(message) , 0) < 0){
			cout <<"Send failed"<< endl;
			return 1;
		}
		cout <<"Data Send"<< endl;

		//Receive a reply from the server
		if( recv(socket_desc, server_reply , 2000 , 0) < 0){
			cout <<"Recv failed"<< endl;
		}
		cout <<"Reply received"<< endl;
		cout <<server_reply<< endl;
	}else{
	    cout <<"Ping "<< argv[1] <<" failed"<< endl;
	}

	return 0;
}
