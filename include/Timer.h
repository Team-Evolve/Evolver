#pragma once

#include <chrono>
#include <iostream>
#include "Debug.h"

namespace evolver
{
	class Timer
	{
	public:
		void Update()
		{
			endTime = std::chrono::system_clock::now();
			elapsedTime = endTime - startTime;
			// for starting
			miliseconds = elapsedTime.count() > 1.0 ? 0.0 : elapsedTime.count();

			startTime = std::chrono::system_clock::now();
		}

		void Print()
		{
			LOG_INFO("FPS : " + std::to_string(miliseconds) + " ms");
		}

		double GetMiliseconds() { return miliseconds; }

	private:
		std::chrono::time_point<std::chrono::system_clock> startTime, endTime;
		std::chrono::duration<double> elapsedTime;
		double miliseconds;
	};
}
