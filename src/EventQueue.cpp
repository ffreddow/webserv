/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   EventQueue.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhenrich <fhenrich@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 16:26:54 by fhenrich          #+#    #+#             */
/*   Updated: 2023/04/05 17:10:51 by fhenrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "EventQueue.hpp"

EventQueue::EventQueue(): kqueuefd(kqueue()) {
	if (kqueuefd == -1)
		throw std::logic_error("ERROR: Could not create kqueue");
}

EventQueue::~EventQueue() {
}

int EventQueue::wait() {
	int nev = kevent(kqueuefd, change_list.data(), change_list.size(), event_list.data(), event_list.size(), 0);
	if (nev == -1)
		throw std::logic_error("ERROR: Error in eventqueue");
	return nev;
}

void EventQueue::add(int fd) {
	change_list.resize(change_list.size() + 1);
	event_list.resize(event_list.size() + 1);
	EV_SET(&change_list[change_list.size() - 1], fd, EVFILT_READ, EV_ADD, 0, 0, 0);
}

void EventQueue::remove(int fd) {
	for (std::vector<struct kevent>::iterator it = change_list.begin(); it < change_list.end(); it++) {
		if (it->ident == static_cast<uintptr_t>(fd)) {
			change_list.erase(it);
			event_list.erase(event_list.begin());
			break;
		}
	}
}

const std::vector<struct kevent> &EventQueue::getEventList() const {
	return event_list;
}
