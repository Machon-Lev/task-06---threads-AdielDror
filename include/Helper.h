#pragma once

#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <list>
#include <chrono>

using std::cout;
using std::endl;
using std::thread;
using std::mutex;
using std::condition_variable;
using std::this_thread::get_id;

extern std::list<std::tuple<thread::id, double, bool>> my_list;
extern bool is_last_message;

class Lockers {
public:
	static mutex _mtx_cout;
	static mutex _mtx_global_list;
	static condition_variable _cond_global_list;
};