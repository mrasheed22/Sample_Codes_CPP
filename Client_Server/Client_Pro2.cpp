/*
 * Client_Pro2.cpp
 *
 *  Created on: 19-Nov-2021
 *      Author: sands
 */


#include <iostream>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h> 	//struct sockaddr_in & inet_addr
#include <sys/types.h> 	//getifaddrs
#include <ifaddrs.h>   	//getifaddrs
#include <unistd.h> 	//close()


#define PORT 8080

using namespace std;

char *getIPAddress();

int main()
{
	int socket_desc, c_sd;
	struct sockaddr_in server;

	char *message, server_reply[2000];
	char *IP_Address;

	IP_Address = getIPAddress();
	socket_desc = socket(AF_INET, SOCK_STREAM, 0); //Allocate socket descriptor

	server.sin_addr.s_addr = inet_addr(IP_Address);
	server.sin_family = AF_INET;
	server.sin_port = htons(PORT);

	if(connect(socket_desc, (struct sockaddr *)&server, sizeof(server))<0){
		cout <<"Connect Error"<< endl;
	}

	message = "Hello Server....\n";
	if(send(socket_desc, message, strlen(message), 0)<0){
		cout <<"Send failed"<< endl;
	}

	//Receive a reply from the server
	if( recv(socket_desc, server_reply , 13, 0) < 0){
		cout <<"Recv failed"<< endl;
	}
	cout <<"Connected:"<<server_reply<< endl;

	c_sd = close(socket_desc);
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

