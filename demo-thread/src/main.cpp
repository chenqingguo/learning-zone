#include<iostream>
#include<thread>
#include <condition_variable>
#include <mutex>
#include <queue>
#include <vector>
#include <chrono>
#include <list>


using namespace std;

std::mutex mtx;
std::condition_variable cv_p,cv_c;
std::queue<size_t> m_queuw;
size_t m_data = 1;

void producer(const int& num)
{
	while (true)
	{
		std::unique_lock<std::mutex> lck(mtx);
		cv_p.wait(lck, [](){return m_queuw.size() <= 100; });
		m_queuw.push(m_data++);
		cout << "producer: " << num << " queue size: " << m_queuw.size() << endl;
		//cout << "producer: " << num << " data: " << m_data << endl;
		cv_c.notify_one();
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
}

void comsumer(int a)
{
	while (true)
	{
		std::unique_lock<std::mutex> lck(mtx);
		cv_c.wait(lck, []() {return !m_queuw.empty(); });
		a = m_queuw.front();
		m_queuw.pop();
		//cout << "comsumer: " << a << " queue size: " << m_queuw.size() << endl;
		//cout << "comsumer: " << a << " data: " << m_data << endl;
		cv_p.notify_one();
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
};

int main()
{	
	std::thread pros[10],consumers[4];
	vector <int> v1;
	v1.emplace_back(2);
	list <int> lis1;
	lis1.emplace_back(2);
	lis1.push_back(0);

	for (int i = 0; i < 10; i++)
	{
		pros[i]=std::thread(&producer,i);
		pros[i].join();
	}
	for (int i = 0; i < 4; i++)
	{
		consumers[i] = std::thread(&comsumer, i);		
		consumers[i].join();
	}
	return 0;
}