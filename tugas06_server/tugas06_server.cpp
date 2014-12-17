// tugas06_server.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <string.h>


void client_handle(void* ah) {
	char data[100] = "Welcome :)";

	sf::TcpSocket* client = static_cast<sf::TcpSocket*>(ah);

	// TCP socket:
	if (client->send(data, 100) != sf::Socket::Done)
	{
		// error...
	}

	char buf[2];
	char message[100] = "";
	std::size_t received;

	// TCP socket:
	do {
		client->receive(buf, 1, received);
		buf[1] = '\0';
		strcat(message, buf);
	} while(strstr(message, "\r\n") == NULL);
	//if (client.receive(message, 100, received) != sf::Socket::Done)
	//{
	//	// error...
	//}

	// TCP socket:
	if (client->send((void *)&message, 100) != sf::Socket::Done)
	{
		// error...
	}

}

int _tmain(int argc, _TCHAR* argv[])
{
	sf::TcpListener listener;

	// bind the listener to a port
	if (listener.listen(53000) != sf::Socket::Done)
	{
		// error...
	}

	while (true) {
		// accept a new connection
		sf::TcpSocket client;
		if (listener.accept(client) != sf::Socket::Done)
		{
			// error...
		}
		else
		{
			//sf::TcpSocket client2 = sf::TcpSocket(client);
			// create a thread with func() as entry point
			sf::Thread thread(&client_handle, (void*)&client);
		
			
			// run it
			thread.launch();
		}
	}
	
	return 0;
}

