/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhenrich <fhenrich@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 12:33:07 by fhenrich          #+#    #+#             */
/*   Updated: 2023/04/06 16:17:46 by fhenrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/socket.h>
#include <sys/event.h>
#include <netinet/in.h>
#include <unistd.h>
#include <fcntl.h>
#include <iostream>
#include <vector>
#include <map>
#include <set>

#include "Server.hpp"
#include "EventQueue.hpp"
#include "Connection.hpp"

int main() {
	sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = INADDR_ANY;
	addr.sin_port = htons(1234);

	Server serv(addr);
	std::map<int, Server> servers;
	servers[serv.getSocketFd()] = serv;
	EventQueue event_queue;
	event_queue.add(serv.getSocketFd());

	std::map<int, Connection> sessions;

	while (true) {
		int nev = event_queue.wait();
		for (int i = 0; i < nev; i++) {
			const struct kevent &event = event_queue.getEventList()[i];
			if (event.flags & EV_ERROR) {
				perror("Error in event_list");
			} else if (event.flags & EV_EOF) {
				std::cout << "Closing connection " << event.ident << std::endl;
				close(event.ident);
				sessions.erase(sessions.find(event.ident));
				event_queue.remove(event.ident);
			} else {
				if (servers.find(event.ident) == servers.end()) {
					std::cout << "Got input for fd " << event.ident << std::endl;
					if (sessions[event.ident].processRequest() == CON_CONNECTION_CLOSED)
						sessions.erase(sessions.find(event.ident));
				} else {
					int tmpfd = servers[event.ident].acceptCon();
					sessions[tmpfd] = Connection(&servers[event.ident], &event_queue, tmpfd);
				}
			}
		}
	}
	return 0;
}
