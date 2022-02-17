#ifndef CINTERFACE_H
#define CINTERFACE_H
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <ctime>
#include <cstdlib>
#include <stdarg.h> //  support for variadic functions
//#include <cctype> //for toupper()

#include <list>
#include <set>
#include <map>
#include <string>
#include <vector>
#include <cstring>
#include <unordered_set>

#include "ColPackHeaders.h"

using namespace ColPack;

// Builds coloring from file
extern "C" int build_coloring(void** ref, int* len, const char* _filename, const char* _method, const char* _order, int verbose);
// Builds coloring from ADOLC compressed row format. csr is an array of int* row pointers.
// Each row has the number of elements in csr[0] and with csr[i] having the column value of element i.
extern "C" int build_coloring_from_csr(void** ref, int* len, unsigned int** csr, int rowcount, const char* _method, const char* _order, int verbose);
extern "C" void get_colors(void* ref, int* _coloring, char* _method, int verbose);
#endif
