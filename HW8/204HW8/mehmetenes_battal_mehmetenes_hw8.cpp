#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <ctime>
#include <chrono>
#include <iomanip>
#include <random>
#include <time.h> 
#include "HW8DynIntQueue.h"

using namespace std;

// MEHMET ENES BATTAL - HW8
 
HW8DynIntQueue myQueue;
mutex myMutex, coutMutex;
int total_customer_count;

int random_range(const int & min, const int & max) 
{     
	static mt19937 generator(time(0));    
	uniform_int_distribution<int> distribution(min, max);     
	return distribution(generator); 
}

void customer(int min, int max)
{
	/* Begin: code taken from ProducerConsumer.cpp and updated */ 

	for(int i = 1; i <= total_customer_count; i++)
	{
		myMutex.lock();
		myQueue.enqueue(i);
		int queueSize = myQueue.getCurrentSize();
		myMutex.unlock();

		coutMutex.lock();
		time_t tt = chrono::system_clock::to_time_t(chrono::system_clock::now()); 
		struct tm *ptm = new struct tm; 
		localtime_s(ptm, &tt);

		cout <<"New customer with ID "<< i << " has arrived (queue size is " << 
			queueSize << "): " << put_time(ptm,"%X") << endl;
		coutMutex.unlock();

		this_thread::sleep_for(chrono::seconds(random_range(min, max)));

		delete ptm; // To prevent memory leak
	}

	/* End: code taken from ProducerConsumer.cpp and updated */
}

void cashier(int min, int max, int treshold, int cashierID)
{
	/* Begin: code taken from ProducerConsumer.cpp and updated */ 

	this_thread::sleep_for(chrono::seconds(random_range(min, max)));
	
	static int served = 0;
	int item;

	while(served < total_customer_count)
	{
		myMutex.lock();
		if ((myQueue.getCurrentSize() != 0 && cashierID == 1) || (cashierID == 2 && myQueue.getCurrentSize() >= treshold)) 
		{  
			myQueue.dequeue(item);
			int queueSize = myQueue.getCurrentSize();
			served++;
			myMutex.unlock();
			
			coutMutex.lock();
			time_t tt = chrono::system_clock::to_time_t(chrono::system_clock::now()); 
			struct tm *ptm = new struct tm; 
			localtime_s(ptm, &tt); 

			cout << "Cashier " << cashierID <<" started transaction with customer " << item <<
				" (queue size is " << queueSize << "): " << put_time(ptm,"%X") << endl;
			coutMutex.unlock();
			
			this_thread::sleep_for(chrono::seconds(random_range(min, max))); // simulation for transaction

			coutMutex.lock();
			tt = chrono::system_clock::to_time_t(chrono::system_clock::now()); 
			localtime_s(ptm, &tt);

			cout <<"Cashier " << cashierID << " finished transaction with customer " << item 
				<< " " << put_time(ptm,"%X") << endl;
			coutMutex.unlock();

			delete ptm; // To prevent memory leak
		}

		else
		{
			myMutex.unlock();
		}
	}

	/* End: code taken from ProducerConsumer.cpp and updated */
}

int main()
{
	cout << "Please enter the total number of customers: ";
	cin >> total_customer_count ;

	int cashier2_threshold;
	cout << "Please enter the number of customers waiting in the queue to open the second cashier: ";
	cin >> cashier2_threshold;

	int min_arrival, max_arrival;
	cout << "Please enter the inter-arrival time range between two customers: " << endl;
	cout << "Min: ";
	cin >> min_arrival;
	cout << "Max: ";
	cin >> max_arrival;

	int min_checkout_time, max_checkout_time;
	cout << "Please enter the checkout time range of cashiers: " << endl;
	cout << "Min: ";
	cin >> min_checkout_time;
	cout << "Max: ";
	cin >> max_checkout_time;

	time_t tt = chrono::system_clock::to_time_t(chrono::system_clock::now());
	struct tm *ptm = new struct tm; 
	localtime_s(ptm, &tt);

	cout << "Simulation starts " << put_time(ptm,"%X") << endl;

	thread thr0(&customer, min_arrival, max_arrival); // Customer thread
	thread thr1(&cashier, min_checkout_time, max_checkout_time, cashier2_threshold, 1); // Cashier 1 thread
	thread thr2(&cashier, min_checkout_time, max_checkout_time, cashier2_threshold, 2); // Cashier 2 thread

	thr0.join();
	thr1.join();
	thr2.join();

	tt = chrono::system_clock::to_time_t(chrono::system_clock::now());
	localtime_s(ptm, &tt);

	cout << "End of the simulation ends: " << put_time(ptm,"%X") << endl;

	delete ptm; // To prevent memory leak

	return 0;
}