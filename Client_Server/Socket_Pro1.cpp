/*
 * Socket_Pro1.cpp
 *
 *  Created on: 16-Nov-2021
 *      Author: sands
 */

#include <iostream>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>	//inet_addr
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>

#include <sys/types.h> //getifaddrs
#include <ifaddrs.h>   //getifaddrs

#define PORT 8080

using namespace std;

char *getIPAddress();

struct sockaddr_in server , client;

int socket_desc ,new_socket ,c ,valread;

char buffer[1024] = {0};
char *hello = "Hi from server\n";

int main(int argc, char *argv[])
{
	char *IP_Address;

	IP_Address = getIPAddress();

	socket_desc = socket(AF_INET,SOCK_STREAM,0);
	if(socket_desc == -1){
		cout<<"Couldn't create socket" <<endl;
	}

	//Prepare the sockaddr_in structure
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons( PORT );

	//Bind
	if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0){
		cout <<"bind failed"<< endl;
	}
	cout <<"bind done"<< endl;

	//Listen
	listen(socket_desc , 3);

	//Accept and incoming connection
	cout <<"Waiting for incoming connections..."<< endl;
	c = sizeof(struct sockaddr_in);
	new_socket = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c);
	if (new_socket<0){
		cout <<"accept failed"<< endl;
	}

	cout <<"Connection accepted"<< endl;

	valread = read( new_socket , buffer, 1024);
	cout <<buffer<< endl;
	send(new_socket , IP_Address , strlen(IP_Address) , 0 );
	//send(new_socket , hello , strlen(hello) , 0 );
	cout <<"Hello message sent\n"<< endl;

	return 0;
}
char *getIPAddress(){
	char *ipAddress="Unable to get IP Address";
	struct ifaddrs *interfaces = NULL;
	struct ifaddrs *temp_addr = NULL;
	int success = 0;

	// retrieve the current interfaces - returns 0 on success
	success = getifaddrs(&interfaces);
	if (success == 0) {
		// Loop through linked list of interfaces
		temp_addr = interfaces;
		while(temp_addr != NULL) {
			if(temp_addr->ifa_addr->sa_family == AF_INET) {
				// Check if interface is en0 //which is the wifi connection
				if(strcmp(temp_addr->ifa_name, "en")){
					ipAddress=inet_ntoa(((struct sockaddr_in*)temp_addr->ifa_addr)->sin_addr);
				}
			}
			temp_addr = temp_addr->ifa_next;
		}
	}
	// Free memory
	freeifaddrs(interfaces);
	cout <<"e.Address: "<<ipAddress<< endl;
	return ipAddress;
}
