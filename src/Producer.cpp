#include "Producer.h" 

// Init static  
Lockers Producer::_lockers;


Producer::Producer(std::list<std::tuple<thread::id, double, bool>>& global_list, thread::id thread_id, int millisecondsToWait) :
	_global_list(global_list), _thread_id(thread_id), _millisecondsToWait(millisecondsToWait){}



void Producer::operator() () {

	double value = std::hash<thread::id>{}(_thread_id);
	int i = 2;
	while (value > 0)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(500));  

		{
			std::unique_lock lock(_lockers._mtx_global_list);
			_global_list.push_back(std::make_tuple(_thread_id, value, is_last_message));
		}
		_lockers._cond_global_list.notify_all();



		value /= 10.0;  // Divide value by 10 for the next message
		--i;
	}



	std::unique_lock lock(_lockers._mtx_global_list);
	is_last_message = true;  // Set the last message flag
	_lockers._cond_global_list.notify_all();  // Notify consumer about the last message


}

thread::id Producer::get_thread_id() const
{
	return _thread_id;
}

