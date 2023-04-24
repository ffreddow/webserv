/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpRequest.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhenrich <fhenrich@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 19:35:56 by fhenrich          #+#    #+#             */
/*   Updated: 2023/04/06 11:22:58 by fhenrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "EventQueue.hpp"
#include "Server.hpp"
#include <map>

class HttpRequest {
private:
	int connection;
	std::string request;
	std::map<std::string, std::string> args;


public:
	HttpRequest();
	HttpRequest(int);
	HttpRequest(const HttpRequest &);
	~HttpRequest();

	HttpRequest &operator=(const HttpRequest &);

	void handle();
};
