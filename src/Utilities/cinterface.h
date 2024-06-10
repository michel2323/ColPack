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

// Builds coloring, bicoloring or partial coloring from file
extern "C" int build_coloring_from_file(void** ref, int* len, const char* _filename, const char* _method, const char* _order, int verbose);
extern "C" int build_bicoloring_from_file(void** ref, int* len1, int* len2, const char* _filename, const char* _method, const char* _order, int verbose);
extern "C" int build_partial_coloring_from_file(void** ref, int* len1, int* len2, const char* _filename, const char* _method, const char* _order, int verbose);
// Builds coloring from ADOLC compressed row format. csr is an array of int* row pointers.
// Each row has the number of elements in csr[0] and with csr[i] having the column value of element i.
extern "C" int build_coloring_from_csr(void** ref, int* len, unsigned int** csr, int rowcount, const char* _method, const char* _order, int verbose);
extern "C" int build_bicoloring_from_csr(void** ref, int* len1, int* len2, unsigned int** csr, int rowcount, int colcount, const char* _method, const char* _order, int verbose);
extern "C" int build_partial_coloring_from_csr(void** ref, int* len1, int* len2, unsigned int** csr, int rowcount, int colcount, const char* _method, const char* _order, int verbose);
extern "C" void get_coloring(void* ref, int* coloring);
extern "C" void get_bicoloring(void* ref, int* left_coloring, int* right_coloring);
extern "C" void get_partial_coloring(void* ref, int* left_coloring, int* right_coloring);
extern "C" void free_coloring(void* ref);
extern "C" void free_bicoloring(void* ref);
extern "C" void free_partial_coloring(void* ref);
#endif
