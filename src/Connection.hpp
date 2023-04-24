/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Connection.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhenrich <fhenrich@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 11:21:25 by fhenrich          #+#    #+#             */
/*   Updated: 2023/04/06 11:56:03 by fhenrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "HttpRequest.hpp"

#define CON_CONNECTION_CLOSED 1
#define CON_SUCCESS 0

class Connection {
private:
	Server *server;
	EventQueue *queue;
	int connection_fd;
	HttpRequest request;


public:
	Connection();
	Connection(Server *, EventQueue *, int);
	Connection(const Connection &);
	~Connection();

	Connection &operator=(const Connection &);

	int processRequest();
};
