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
extern "C" int build_coloring_from_file(void** ref, int* len, const char* filename, const char* method, const char* order, int verbose);
extern "C" int build_partial_coloring_from_file(void** ref, int* len, const char* filename, const char* method, const char* order, int verbose);
extern "C" int build_bicoloring_from_file(void** ref, int* len1, int* len2, const char* filename, const char* method, const char* order, int verbose);

// Builds coloring, bicoloring or partial coloring from ADOLC compressed row format. csr is an array of int* row pointers.
// Each row has the number of elements in csr[0] and with csr[i] having the column value of element i.
extern "C" int build_coloring_from_adolc(void** ref, int* len, unsigned int** csr, int rowcount, const char* method, const char* order, int verbose);
extern "C" int build_partial_coloring_from_adolc(void** ref, int* len, unsigned int** csr, int rowcount, int colcount, const char* method, const char* order, int verbose);
extern "C" int build_bicoloring_from_adolc(void** ref, int* len1, int* len2, unsigned int** csr, int rowcount, int colcount, const char* method, const char* order, int verbose);

// Build partial coloring from CSR format.
extern "C" int build_partial_coloring_from_csr(void** ref, int* len, int* rows, int* cols, int rowcount, int colcount, const char* method, const char* order, int verbose);

extern "C" void get_coloring(void* ref, int* coloring);
extern "C" void get_partial_coloring(void* ref, int* coloring);
extern "C" void get_bicoloring(void* ref, int* left_coloring, int* right_coloring);

extern "C" int ncolors_coloring(void* ref);
extern "C" int ncolors_partial_coloring(void* ref);
extern "C" int ncolors_bicoloring(void* ref);

extern "C" void free_coloring(void* ref);
extern "C" void free_partial_coloring(void* ref);
extern "C" void free_bicoloring(void* ref);
#endif
