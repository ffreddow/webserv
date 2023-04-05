/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   EventQueue.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhenrich <fhenrich@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 16:00:19 by fhenrich          #+#    #+#             */
/*   Updated: 2023/04/05 17:01:05 by fhenrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <sys/event.h>
#include <exception>
#include <vector>

class EventQueue {
private:
	std::vector<struct kevent> change_list;
	std::vector<struct kevent> event_list;
	int kqueuefd;

	EventQueue(const EventQueue &old) {(void)old;}
	EventQueue &operator=(const EventQueue &old) {(void)old; return *this;}
public:
	EventQueue();
	~EventQueue();

	int wait();
	void add(int);
	void remove(int);
	const std::vector<struct kevent> &getEventList() const;
};
