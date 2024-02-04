#include "sandbox.hpp"




__declspec(dllexport) LPXLOPER12 WINAPI genDummyArray(void)
{
	int rows = 2;
	int cols = 3;

	static XLOPER12 xlArray;
	xlArray.val.array.rows = rows;
	xlArray.val.array.columns = cols;
	xlArray.xltype = xltypeMulti | xlbitDLLFree;

	xlArray.val.array.lparray = reinterpret_cast<LPXLOPER12>(::new XLOPER12[rows * cols] /*::malloc(rows * cols * sizeof(XLOPER12))*/);
	for (int r = 0; r < rows; r++)
	{
		for (int c = 0; c < cols; c++)
		{
			XLOPER12* var = xlArray.val.array.lparray + ((r * cols) + c);
			var->xltype = xltypeNum;
			var->val.num = (r * cols) + c;
		}
	}
	return static_cast<LPXLOPER12>(&xlArray);
}


__declspec(dllexport) LPXLOPER12 WINAPI updateArray(LPXLOPER12 arrayin)
{
	if (arrayin->xltype == xltypeMulti | xlbitDLLFree)
	{
		double ScaleFactor = 2.0;
		int rows = arrayin->val.array.rows;
		int cols = arrayin->val.array.columns;

		static XLOPER12 xlArray;
		xlArray.val.array.rows = rows;
		xlArray.val.array.columns = cols;
		xlArray.xltype = xltypeMulti | xlbitDLLFree;

		xlArray.val.array.lparray = reinterpret_cast<LPXLOPER12>(::new XLOPER12[rows * cols] /*::malloc(rows * cols * sizeof(XLOPER12))*/);
		for (int r = 0; r < rows; r++)
		{
			for (int c = 0; c < cols; c++)
			{
				if ((arrayin->val.array.lparray + ((r * cols) + c))->xltype == xltypeNum)
				{
					XLOPER12* var = xlArray.val.array.lparray + ((r * cols) + c);
					var->xltype = xltypeNum;
					var->val.num = ScaleFactor * (arrayin->val.array.lparray + ((r * cols) + c))->val.num;
				}
			}
		}
		return static_cast<LPXLOPER12>(&xlArray);
	}
	return arrayin;
}



// Declared as a Global variable
Memory* clsMemory;

__declspec(dllexport) double WINAPI registerObjMemory(double x)
{
	clsMemory = new Memory;
	clsMemory->registerMemory(x);
	return 0;
}


__declspec(dllexport) double WINAPI getObjMemory(void)
{
	double x;
	x = clsMemory->getMemory();
	return x;
}

// map with the void* pointer
__declspec(dllexport) char* WINAPI hashRegister(double x) {
	Memory* clsMemory = new Memory;
	clsMemory->registerMemory(x);
	std::string timestamp = str_timestamp();
	hashClass[timestamp] = clsMemory;
	char* chr = new char[timestamp.size()+1];
	std::strcpy(chr, timestamp.c_str());

	return chr;
}


__declspec(dllexport) double WINAPI hashGet(char* chrHash) {
	if (hashClass.find(chrHash) == hashClass.end()) {
		return 0;
	}
	Memory* clsMemory = (Memory*)hashClass[chrHash];
	return clsMemory->getMemory();
}


// 
double** lpxploperToArray(LPXLOPER12 arrayin)
{
	int rows = arrayin->val.array.rows;
	int cols = arrayin->val.array.columns;

	double** arr = new double* [rows];
	for (int r = 0; r < rows; r++) {
		arr[r] = new double[cols];
	}

	for (int r = 0; r < rows; r++)
	{
		for (int c = 0; c < cols; c++)
		{
			arr[r][c] = (arrayin->val.array.lparray + ((r * cols) + c))->val.num;
		}
	}
	return arr;
}
