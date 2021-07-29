#include<iostream>
#include<thread>
#include <condition_variable>
#include <mutex>
#include <queue>
#include <vector>
#include <chrono>
#include <list>
#include <memory>
#include <unordered_map>
#include <iostream>
using namespace std;


int main()
{	
	vector<float> a (1000, 0.1f);	
	unique_ptr<float[]> tmp(new float[1000]);
	for (int i = 0; i < 1000; i++)
	{
		tmp[i] = i * 0.001f;
	}
	cout << "unique_ptr<float[]>: " << sizeof(tmp) << endl;
	system("pause");
	return 0;
}