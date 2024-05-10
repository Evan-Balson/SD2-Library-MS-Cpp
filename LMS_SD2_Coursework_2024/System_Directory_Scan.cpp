
#include "System_Directory_Scan.h"


// get source directory so that we can create the receipt file in a specific location.


bool System_Directory_Scan::directoryExists(const std::string& directoryName) {

	DWORD attributes = GetFileAttributesA(directoryName.c_str());
	return (attributes != INVALID_FILE_ATTRIBUTES && (attributes & FILE_ATTRIBUTE_DIRECTORY));
}

bool System_Directory_Scan::createDirectory(const std::string& directoryName, std::string& fullPath) {
	if (directoryExists(directoryName)) {
		//printf("Directory already exists. \n");
		return false;
	}

	if (CreateDirectoryA(directoryName.c_str(), NULL) != 0) {
		char buffer[MAX_PATH];
		DWORD length = GetFullPathNameA(directoryName.c_str(), MAX_PATH, buffer, NULL);
		if (length != 0 && length < MAX_PATH) {
			fullPath = buffer;
			//printf("Directory created successfully. \n");
			return true;
		}
		else {
			printf("Failed to get full path of the directory. \n");
			return false;
		}
	}
	else {
		printf("Failed to create directory. Error code:  ", GetLastError());
		return false;
	}
}


// find os type so that you can call to open file after writing the reciept.
int System_Directory_Scan::launch_receipt_file(string filename) {

	if (os == "Windows") {
		system(("start " + filename).c_str());
		return 0;
	}
	else if (os == "macOS") {
		system(("open " + filename).c_str()); 
		return 0;
	}
	else if (os == "Linux") {
		system(("xdg-open " + filename).c_str());
		return 0;
	}
	else {
		return 1;
	}

}