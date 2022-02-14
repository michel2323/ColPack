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

extern "C" void hello();
extern "C" int build_coloring(void** ref, int* len, const char* _filename, const char* _method, const char* _order, int verbose);
extern "C" void get_colors(void* ref, int* _coloring, char* _method);
#endif