#include "main.h"






int main()
{
    TCPServer server;
    while (true)
    {
        if (server.serverStart())
            server.waitForConnections();
    }
}