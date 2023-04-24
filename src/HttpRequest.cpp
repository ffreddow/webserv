/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpRequest.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhenrich <fhenrich@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 12:16:28 by fhenrich          #+#    #+#             */
/*   Updated: 2023/04/06 12:19:40 by fhenrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HttpRequest.hpp"

HttpRequest::HttpRequest(): connection(-1) {

}

HttpRequest::HttpRequest(int fd): connection(fd) {

}

HttpRequest::HttpRequest(const HttpRequest &old): connection(old.connection), request(old.request), args(old.args) {

}

HttpRequest::~HttpRequest() {

}

HttpRequest &HttpRequest::operator=(const HttpRequest &old) {
	if (this == &old)
		return *this;

	connection = old.connection;
	request = old.request;
	args = old.args;
	return *this;
}

void HttpRequest::handle() {

}
