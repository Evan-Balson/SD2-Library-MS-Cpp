#pragma once
#include <windows.h>
#include <string>

// We are going to note the operating system.
// I am going to attempt to call an action for opeing the receipt.

// Check if the operating system is Windows
#if defined(_WIN32) || defined(_WIN64)
const std::string os = "Windows";
// Check if the operating system is macOS
#elif defined(__APPLE__)
const std::string os = "macOS";
// Check if the operating system is Linux
#elif defined(__linux__)
const std::string os = "Linux";
#else
const std::string os = "Unknown";
#endif

#include <cstdlib>

using std::string;

class System_Directory_Scan
{
public:

	bool directoryExists(const std::string& directoryName);
	bool createDirectory(const std::string& directoryName, std::string& fullPath);
	int launch_receipt_file(string filename);


private:

	string directoryName;
	string fullPath;
	string file_path;

};

