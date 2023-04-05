/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhenrich <fhenrich@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 11:13:29 by fhenrich          #+#    #+#             */
/*   Updated: 2023/04/05 18:38:00 by fhenrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once


#include <sys/socket.h>
#include <sys/event.h>
#include <netinet/in.h>
#include <unistd.h>
#include <fcntl.h>
#include <iostream>
#include <exception>

class Server {
private:
	sockaddr_in address;
	int address_len;
	int socketfd;

public:
	Server();
	Server(const sockaddr_in &);
	Server(const Server &);
	~Server() {}

	Server &operator=(const Server &);

	void handle_request() const;
	int getSocketFd() const;
	int acceptCon() const;
};
