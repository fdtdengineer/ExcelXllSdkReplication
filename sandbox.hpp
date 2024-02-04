#ifndef SANDBOX_HPP
#define SANDBOX_HPP


#include <windows.h> 
#include <math.h> 
#include <string>
#include <cmath>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <ctype.h>
#include <windows.h>
#include "xlcall.h"
#include "framewrk.h"
#include <unordered_map>  

#include "timestamp.hpp"

std::unordered_map<std::string, void *> hashClass;


__declspec(dllexport) LPXLOPER12 WINAPI genDummyArray(void);
__declspec(dllexport) LPXLOPER12 WINAPI updateArray(LPXLOPER12 arrayin);


class Memory
{
private:
	double x;

public:
	Memory(void) { x = 0; };
	void registerMemory(double x_) { x = x_; };
	double getMemory(void) { return x; };
};


__declspec(dllexport) double WINAPI registerObjMemory(double x);
__declspec(dllexport) double WINAPI getObjMemory(void);

__declspec(dllexport) char* WINAPI hashRegister(double x);
__declspec(dllexport) double WINAPI hashGet(char* chrHash);






#endif