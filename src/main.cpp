#include "Helper.h"
#include "Producer.h"
#include "Consumer.h"


int main()
{
	try {
		Consumer consumer1(my_list, 450);

		// Create thread objects
		thread tC(std::ref(consumer1));
		thread::id producer1_thread_id, producer2_thread_id;

		{
			// Create producer1 with a unique thread ID
			thread producer1_thread([&] {
				try {
					Producer producer1(my_list, std::this_thread::get_id(), 150);
					producer1_thread_id = std::this_thread::get_id();
					producer1();
				}
				catch (const std::exception& ex) {
					// Handle producer1 exception
					std::cerr << "Producer1 Exception: " << ex.what() << std::endl;
				}
				});

			// Create producer2 with a unique thread ID
			thread producer2_thread([&] {
				try {
					Producer producer2(my_list, std::this_thread::get_id(), 150);
					producer2_thread_id = std::this_thread::get_id();
					producer2();
				}
				catch (const std::exception& ex) {
					// Handle producer2 exception
					std::cerr << "Producer2 Exception: " << ex.what() << std::endl;
				}
				});

			// Wait for the producers to finish
			producer1_thread.join();
			producer2_thread.join();
		}


		// Wait for the consumer to finish
		tC.join();
	}catch (const std::exception& ex) {
		// Handle main thread exception
		std::cerr << "Main Thread Exception: " << ex.what() << std::endl;
	}
	return 0;
}