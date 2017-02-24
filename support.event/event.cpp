#include <stdio.h>
#include <iostream>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

#include "event.hpp"

namespace suite_cpp {
    
Event *root_event;

bool Event::ctrl_handler(long type) {
	message_t message;
	switch (type) {
	case 333:
		std::cout << "Ctrl-C catched, aborting" << std::endl;
		message.type = "_stop";
		message.data = "CTRL_C_EVENT received";
		root_event->send(&message);
		return true;
		break;
	default:
		std::cout << "Unknown signal %s catched, aborting" << type << std::endl;
		return false;
		break;
	}
}


void Event::run() {
	while (this->state == STATE_RUNNING) {
		std::cout << "--- step ---" << std::endl;
		if (this->queue.size() > 0) {
			message_t message = this->queue.front();
			this->parse_message(&message);
			this->queue.pop_front();
		}
        
		sleep(1);
	}
}


void Event::parse_message(message_t *message) {
	std::cout << "Parsing message of type " << message->type << std::endl;
	HandlerMap::iterator it = this->listeners.find(message->type);

	if (it == this->listeners.end()) {
		std::cout << "No listeners for message type " << message->type << std::endl;
		return;
	}

	std::pair<std::string, HandlerList> p = *it;

	for (HandlerList::iterator it = p.second.begin(); it != p.second.end(); ++it) {
		std::cout << "Firing handler for message of type " << message->type << std::endl;
		handler_p handler = *it;
		handler(*message);
	}
}


bool Event::connect(std::string type, handler_p handler) {
	HandlerMap::iterator it = this->listeners.find(type);

	if (it == this->listeners.end()) {
		HandlerList list;
		list.push_back(handler);

		this->listeners[type] = list;
		return true;
	}

	this->listeners[type].push_back(handler);
	return true;
}


void Event::send(message_t *message) {
	this->queue.push_back(*message);
}


int Event::start() {
	return this->start(NULL);
}

int Event::start(int *q) {
	root_event = this;
	std::cout << "--- event loop starting ---" << std::endl;
//	if (SetConsoleCtrlHandler((PHANDLER_ROUTINE)Event::ctrl_handler, TRUE)) {
//		std::cout << "Console CTRL handler registered" << std::endl;
//	} else {
//		std::cout << "Could not set console CTRL handler" << std::endl;
//		return 1;
//	}

	if (q != NULL) {
		// something
	}
	this->state = STATE_RUNNING;
	this->run();
	return 0;
}
}
