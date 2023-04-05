/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhenrich <fhenrich@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 12:33:07 by fhenrich          #+#    #+#             */
/*   Updated: 2023/04/05 18:41:13 by fhenrich         ###   ########.fr       */
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

	while (true) {
		int nev = event_queue.wait();
		for (int i = 0; i < nev; i++) {
			if (event_queue.getEventList()[i].flags & EV_ERROR) {
				perror("Error in event_list");
				exit(EXIT_FAILURE);
			}
			const struct kevent &event = event_queue.getEventList()[i];
			if (servers.find(event.ident) == servers.end()) {
				char buff[256];
				memset(buff, 0, 256);
				int ret = recv(event.ident, buff, 256, 0);
				if (ret == -1)
					perror("recv()");
				else
					std::cout << buff << std::endl;
				close(event.ident);
				event_queue.remove(event.ident);
			} else {
				int tmpfd = servers[event.ident].acceptCon();
				event_queue.add(tmpfd);
			}
		}
	}
	return 0;
}
