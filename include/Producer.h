#pragma once

#include "Helper.h"

class Producer {

	// static, internal globals 
	static Lockers _lockers;

	// globals (by reference) 
	std::list<std::tuple<thread::id, double, bool>>& _global_list;

	bool _is_last_message = false;
	thread::id _thread_id;
	int _millisecondsToWait;

public:
	Producer(std::list<std::tuple<thread::id, double, bool>>& global_list, thread::id thread_id, int millisecondsToWait);

	void operator() ();

	thread::id get_thread_id() const;
};