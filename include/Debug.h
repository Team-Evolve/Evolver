#ifndef DEBUG_H
#define DEBUG_H

#include <iostream>

#define LOG_INFO(message) LogInfo(message, __LINE__, __FILE__, __TIME__)
#define LOG_ERROR(message) LogError(message, __LINE__, __FILE__, __TIME__)

inline std::string GetColoredInfo(std::string msg)
{
	std::string toReturn("\u001b[44;1m" + msg + "\u001b[0m");
	return toReturn;
}

inline std::string GetColoredError(std::string msg)
{
	std::string toReturn("\u001b[41;1m" + msg + "\u001b[0m");
	return toReturn;
}

inline void LogInfo(std::string msg, int line, const char* file, const char* time)
{
	std::cout << "[" << time << "] " << GetColoredInfo("INFO") << " " << file << "(" << line << ") " << msg << '\n';
}

inline void LogError(std::string msg, int line, const char* file, const char* time)
{
	std::cout << "[" << time << "] " << GetColoredError("ERROR") << " " << file << "(" << line << ") " << msg << '\n';
}

#endif DEBUG_H