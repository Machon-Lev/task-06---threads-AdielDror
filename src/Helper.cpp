#include "Helper.h"

std::list<std::tuple<thread::id, double, bool>> my_list;
bool is_last_message = false;

mutex Lockers::_mtx_cout;
mutex Lockers::_mtx_global_list;
condition_variable Lockers::_cond_global_list;