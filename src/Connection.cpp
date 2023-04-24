/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Connection.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhenrich <fhenrich@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 11:45:59 by fhenrich          #+#    #+#             */
/*   Updated: 2023/04/06 16:21:42 by fhenrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Connection.hpp"

Connection::Connection(): server(0), queue(0), connection_fd(-1) {
	std::cout << "Empty connection created\n";
}

Connection::Connection(Server *serv, EventQueue *q, int fd): server(serv), queue(q), connection_fd(fd) {
	std::cout << "Connection created on " << connection_fd << std::endl;
	queue->add(connection_fd);
}

Connection::Connection(const Connection &old): server(old.server), queue(old.queue), connection_fd(old.connection_fd), request(old.request) {
	std::cout << "Copy created connection " << old.connection_fd << " into " << connection_fd << std::endl;
}

Connection::~Connection() {
	std::cout << "Destroyed connection " << connection_fd << std::endl;
}

Connection &Connection::operator=(const Connection &old) {
	if (this == &old)
		return *this;
	server = old.server;
	queue = old.queue;
	connection_fd = old.connection_fd;
	request = old.request;

	std::cout << "Copied connection " << old.connection_fd << " into " << connection_fd << std::endl;
	return *this;
}

int Connection::processRequest() {
	
	return CON_SUCCESS;
}
