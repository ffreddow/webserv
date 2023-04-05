/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhenrich <fhenrich@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 11:33:02 by fhenrich          #+#    #+#             */
/*   Updated: 2023/04/05 18:38:46 by fhenrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

Server::Server() {
}

Server::Server(const Server &old): address(old.address), address_len(old.address_len), socketfd(old.socketfd) {

}

Server::Server(const sockaddr_in &addr): address(addr), address_len(sizeof(sockaddr_in)), socketfd(socket(AF_INET, SOCK_STREAM, 0)) {
	if (socketfd == -1) {
		perror("socket()");
		exit(EXIT_FAILURE);
	}
	address_len = sizeof(sockaddr_in);

	if (bind(socketfd, (sockaddr *)&address, address_len)) {
		perror("bind()");
		exit(EXIT_FAILURE);
	}

	fcntl(socketfd, F_SETFL, O_NONBLOCK);
	listen(socketfd, 3);
	std::cout << "Listening on port " << ntohs(address.sin_port) << std::endl;
}

Server &Server::operator=(const Server &old) {
	if (this == &old)
		return *this;

	address = old.address;
	address_len = old.address_len;
	socketfd = old.socketfd;
	return *this;
}

int Server::acceptCon() const {
	int tmpfd = accept(socketfd, (sockaddr *)&address, (socklen_t *)&address_len);
	if (tmpfd == -1)
		throw std::logic_error("ERROR: could not accept connection");
	return tmpfd;
}

int Server::getSocketFd() const {
	return socketfd;
}

void Server::handle_request() const {
	try {
		int connection = acceptCon();
		// usleep(1000);
		// std::string input;
		char buff[256];
		memset(buff, 0, 256);
		int ret = recv(connection, buff, 256, MSG_DONTWAIT);
		if (ret == -1)
			perror("recv()");
		else
			std::cout << buff << std::endl;
		close(connection);
	} catch (const std::exception &e) {
		throw e;
	}
}
