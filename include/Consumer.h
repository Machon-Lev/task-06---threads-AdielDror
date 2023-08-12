#pragma once

#include "Helper.h"

class Consumer {
	// static, internal globals 
	static Lockers _lockers;

	// globals (by reference) 
	std::list<std::tuple<thread::id, double, bool>>& _global_list;

	int _millisecondsToWait;

public:
	Consumer(std::list<std::tuple<thread::id, double, bool>>& global_list, int _millisecondsToWait);

	void operator() ();

};