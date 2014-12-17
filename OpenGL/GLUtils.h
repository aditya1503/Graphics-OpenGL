#ifndef GLUTILS_H
#define GLUTILS_H

#include <string>
#include <chrono>

void MsgAssert(bool assertion, const std::string &msg);
std::string LoadFileAsString(const std::string &fname);

class PerformanceCounter
{
protected:
	std::chrono::system_clock::time_point start;
			
public:
	PerformanceCounter()
	{
		Start();
	}

	void Start()
	{
		// Get initial value
		start = std::chrono::high_resolution_clock::now();
	}

	long long GetTimeNanoSeconds()
	{
		auto end = std::chrono::high_resolution_clock::now();
		return std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
	}

	double GetTimeMilliSeconds()
	{
		return GetTimeNanoSeconds() * 1e-6;
	}
	
	double GetTimeSeconds()
	{
		return GetTimeNanoSeconds() * 1e-9;
	}
};

#endif