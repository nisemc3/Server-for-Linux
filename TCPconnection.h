#pragma once

#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <thread>
#include <chrono>
#include <unistd.h>

#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>

class TCPclient;

class TCPServer
{
private:
	int m_sock;
	sockaddr_in m_address;
	bool m_clientConnected = false;

public:
	TCPServer();
	void waitForConnections();
	bool serverStart();
};

class TCPclient
{
private:
	int m_sock;
	sockaddr_in m_address;

public:
	TCPclient(int clientSocket, sockaddr_in& clientAddress);
};