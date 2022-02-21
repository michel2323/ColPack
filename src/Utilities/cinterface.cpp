#include "cinterface.h"

const unordered_set<string> GENERAL_COLORING({
        "DISTANCE_ONE", 
        "ACYCLIC", 
        "ACYCLIC_FOR_INDIRECT_RECOVERY", 
        "STAR", 
        "RESTRICTED_STAR", 
        "DISTANCE_TWO"});
const unordered_set<string> BICOLORING({
        "IMPLICIT_COVERING__STAR_BICOLORING",
        "EXPLICIT_COVERING__STAR_BICOLORING",
        "EXPLICIT_COVERING__MODIFIED_STAR_BICOLORING",
        "IMPLICIT_COVERING__GREEDY_STAR_BICOLORING"});
const unordered_set<string> PARTIAL_COLORING({
        "COLUMN_PARTIAL_DISTANCE_TWO",
        "ROW_PARTIAL_DISTANCE_TWO"});

void print_output(GraphColoringInterface *g, int verbose) {
    if (verbose) {
        double t1 = g->GetVertexOrderingTime();
        double t2 = g->GetVertexColoringTime();
        std::cout << "Order and color time = " << t1+t2 << "=" << t1 << "+" << t2 << std::endl;
        std::cout << "Number of colors: " << g->GetVertexColorCount() << std::endl;
    }
}

extern "C" int build_coloring(void** ref, int* len, const char* _filename, const char* _method, const char* _order, int verbose) {
    string filename = string(_filename);
    string method = string(_method);
    string order = string(_order);
    vector<int> coloring;
    void *g;
    if(verbose) std::cout << "Filename: " << filename << "\norder: " << order << "\nmethod: " << method << "\n";
    if (GENERAL_COLORING.count(_method)) {
        if(verbose) std::cout << "General Graph Coloring\n";
        GraphColoringInterface *g = new GraphColoringInterface(SRC_FILE, filename.c_str(), "AUTO_DETECTED");
        g->Coloring(order.c_str(), method.c_str());
        print_output(g, verbose);
		g->GetVertexColors(coloring);
        *len = (int)(coloring.size());
        *ref = (void*) g;
    }
    else {
        std::cerr << "ColPack: Invalid coloring method selected\n";
        return 0;
    }
    return 1;
}

extern "C" int build_coloring_from_csr(void** ref, int* len, unsigned int** csr, int rowcount, const char* _method, const char* _order, int verbose) {
    string method = string(_method);
    string order = string(_order);
    vector<int> coloring;
    void *g;
    if (GENERAL_COLORING.count(_method)) {
        if(verbose) std::cout << "General Graph Coloring\n";
        GraphColoringInterface *g = new GraphColoringInterface(SRC_MEM_ADOLC, csr, rowcount);
        g->Coloring(order.c_str(), method.c_str());
		g->GetVertexColors(coloring);
        *len = (int)(coloring.size());
        *ref = (void*) g;
    }
    else {
        std::cerr << "ColPack: Invalid coloring method selected\n";
        return 0;
    }
    return 1;
}

extern "C" void get_colors(void* ref, int* _coloring, char* _method, int verbose) {
    GraphColoringInterface *g = (GraphColoringInterface*) ref;
    vector<int> coloring;
    print_output(g, verbose);
	g->GetVertexColors(coloring);
    memcpy(_coloring, coloring.data(), (size_t) coloring.size()*sizeof(int));
} 

extern "C" void free_coloring(void** ref) {
    GraphColoringInterface *g = (GraphColoringInterface*) *ref;
    delete g;
}
