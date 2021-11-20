/*
 * getIP_address.cpp
 *
 *  Created on: 19-Nov-2021
 *      Author: sands
 */


#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <unistd.h> //gethostname()
//#include <errno.h>
#include <netdb.h> //gethostbyname()
//#include <sys/types.h>
//#include <sys/socket.h>
//#include <netinet/in.h>
#include <arpa/inet.h> //inet_ntoa()

#include <sys/types.h> //getifaddrs
#include <ifaddrs.h>   //getifaddrs

using namespace std;

string getIPAddress();

// Returns hostname for the local computer
void checkHostName(int hostname)
{
    if (hostname == -1)
    {
        cout <<"gethostname"<< endl;
        exit(1);
    }
}

// Returns host information corresponding to host name
void checkHostEntry(struct hostent * hostentry)
{
    if (hostentry == NULL)
    {
    	cout <<"gethostbyname"<< endl;
        exit(1);
    }
}

// Converts space-delimited IPv4 addresses
// to dotted-decimal format
void checkIPbuffer(char *IPbuffer)
{
    if (NULL == IPbuffer)
    {
    	cout <<"inet_ntoa"<< endl;
        exit(1);
    }
}

// Driver code
int main()
{
    char hostbuffer[256];
    char *IPbuffer;
    struct hostent *host_entry;
    int hostname;

    // To retrieve hostname
    hostname = gethostname(hostbuffer, sizeof(hostbuffer));
    checkHostName(hostname);

    // To retrieve host information
    host_entry = gethostbyname(hostbuffer);
    checkHostEntry(host_entry);

    // To convert an Internet network
    // address into ASCII string
    IPbuffer = inet_ntoa(*((struct in_addr*)
                           host_entry->h_addr_list[0]));

    cout <<"Hostname: "<<hostbuffer<< endl;
    cout <<" Host IP: "<<IPbuffer<< endl;
    getIPAddress();

	    return 0;
}

string getIPAddress(){
	string ipAddress="Unable to get IP Address";
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
