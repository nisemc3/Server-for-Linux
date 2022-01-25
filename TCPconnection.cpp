#include "TCPconnection.h"

TCPServer::TCPServer()
{
	m_address.sin_family = AF_INET;
	m_address.sin_port = uint16_t(4444);
	m_address.sin_addr.s_addr = INADDR_ANY;	
}

bool TCPServer::serverStart()
{
    m_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (m_sock < 0)
	{
		//std::cout<<"Socket created error\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        return false;
	}
    if (bind(m_sock, (struct sockaddr *) &m_address, sizeof(m_address)) < 0)
    {
       //std::cout << "Socket bind error\n"; 
       close(m_sock);
       std::this_thread::sleep_for(std::chrono::milliseconds(100));
       return false;
    }
    if (listen(m_sock, 1) < 0)
    {
       //std::cout << "Listen start error \n"; 
       close(m_sock);
       std::this_thread::sleep_for(std::chrono::milliseconds(100));
       return false;
    }
    return true;
}

void TCPServer::waitForConnections()
{
    int clientSocket;
	sockaddr_in clientAddress;
    uint adrlen = sizeof(clientAddress);
    while (true)
	{
        if((clientSocket = accept(m_sock,(struct sockaddr *) &clientAddress, &adrlen)) != -1)
        {
            //std::cout << "\nNew client!\n";
            TCPclient client(clientSocket, clientAddress);
        }
        //std::cout << "\nClient ended!\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
}


TCPclient::TCPclient(int clientSocket, sockaddr_in& clientAddress)
: m_address(clientAddress), m_sock(clientSocket)
{
	std::string str{};
    str.reserve(1024);
    char buffer[1024];
    while (true)
    {
        int data = recv(m_sock, buffer, sizeof(str), 0);
        if (data > 0)
        {
            for (int i = 0; i < 1024; i++)
            {
                if (std::isdigit(buffer[i]))
                    str.push_back(buffer[i]);
                else break;
            }
            if (str.size() >= 2 && std::stoi(str.c_str()) % 32 == 0)
                std::cout << str << '\n';
            else if (str.size() >= 2)
                std::cout << "not % 32\n";
            else std::cout << "less than 2 digits\n";
            str.clear();
        }
        else 
        {
            //std::cout << "recv < 0\n";
            break;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
    shutdown(m_sock, SHUT_RDWR);
}