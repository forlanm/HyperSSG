#include <iostream>
#include <stdio.h>
#include <cstring>
#include <unistd.h>

#define MOVE system("mv main_b ~/workdir/bin"); // you can change the path for the binaries to whatever you need
#define REMOVE system("rm -R main_b");
#define START_BASE system("./main_b");
#define GPP_C(arg) ({ strcat(strcat(strcpy(new char[100], "g++ -Wall "), arg), " -o main_b"); })
#define GCC_C(arg) ({ strcat(strcat(strcpy(new char[100], "gcc -Wall "), arg), " -o main_b"); })
#define GPP_IF(arg) (strstr(arg, ".cpp") != NULL || strstr(arg, ".cxx") != NULL || strstr(arg, ".c++") != NULL)

inline const bool GPP_B(const char* arg) {
	const char* c = GPP_C(arg);
	try { 
		system(c); 
		std :: cout << c << " completed!\n";
		return 1;
	}
	catch(const std::exception& e) { 
		std::cerr << "System Error: \n" << e.what();
		std::cout << "The system failed to compile this C++ file. The BUILD system supports only *.cxx, *.cpp and *.c++ file extensions..";
		return 0;
	}
}

inline const bool GCC_B(const char* arg) {
	const char* c = GCC_C(arg);
	try { 
		system(c);
		std::cout << c << " completed!\n"; 
		return 1;
	} 
	catch(const std::exception& e) {  
		std::cerr << "System Error: \n" << e.what();
		std::cout << "The system failed to compile this C file. Is this a C file for sure?"; 
		return 0;
	} 
}

inline const bool SYSBUILD(const char* arg) { 
	if (GPP_IF(arg)) { 
		return GPP_B(arg); 
	} else { 
		return GCC_B(arg); 
	}
}

static bool build(const char* file_n) {
	switch(SYSBUILD(file_n)){
		case 1:
			std :: cout << "Build ended without errors.";
			return 1;
		case 0:
			std :: cout << "Fatal error.. Closing.";
			return 0;
	}
}

std::string getCurrentDir() {
    char buffer[FILENAME_MAX];
    getcwd(buffer, FILENAME_MAX);
    return std::string(buffer);
}

void mnrQA(const std :: string curr_d, const char* filename){
	char inp;
	std :: cout << " Do you want to move " << filename << " to bin or to run it once (it will be removed after running)?(CTRL+C cancel)(m/r) ";
	std :: cin >> inp;
	switch(inp){
		case 'm':
			try {
				MOVE 
				REMOVE
			}
			catch (const std::exception& e){
				std :: cout << e.what() << std :: endl;
				std :: cout << "Fatal error, can't move.\n"; 
			}
		case 'r':
			try {
				START_BASE 
				REMOVE
			}
			catch (const std::exception& e){
				std :: cout << e.what() << std :: endl;
				std :: cout << "Fatal error, can't move.\n";
			}
	}
}

int main(int argc, char **argv) {
	try {
		char buff[strlen(argv[1])];
		strcpy(buff, argv[1]);
		std :: string curr_d = getCurrentDir();
		if (build(buff) == 1)
			mnrQA(curr_d, buff);
		else
			return 0;
	}
	catch (const std::exception& e){
		std :: cout << e.what() << std :: endl;
				std :: cout << "FATAL ERROR; It can't be builded!\n"; 
	}
}
