#include "Consumer.h"

// init static 
Lockers Consumer::_lockers;


Consumer::Consumer(std::list<std::tuple<thread::id, double, bool>>& global_list, int millisecondsToWait) :
	_global_list(global_list), _millisecondsToWait(millisecondsToWait) {}

void Consumer::operator() () {


	std::tuple<thread::id, double, bool> tpl;


	int termination_notices = 0;

	while (true) {
		{
			std::unique_lock lock(_lockers._mtx_global_list);
			_lockers._cond_global_list.wait(lock, [this]() { return !_global_list.empty(); });
			tpl = _global_list.front();
			_global_list.pop_front();

		}

		if (is_last_message) {
			cout << std::get<0>(tpl) << " finished " << endl;
			++termination_notices;
			if (termination_notices == 2)
				break;  // Exit the loop if termination notices received from both producers
		}
		else {

			cout << std::get<0>(tpl) << " sent: " << std::get<1>(tpl) << endl;

		}

		_lockers._cond_global_list.notify_all();  // Notify producer that the message has been processed
	}

}
