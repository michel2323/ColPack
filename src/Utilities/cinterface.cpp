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

void print_output(GraphColoringInterface* g, int verbose) {
    if (verbose) {
        double t1 = g->GetVertexOrderingTime();
        double t2 = g->GetVertexColoringTime();
        std::cout << "Order and color time = " << t1 + t2 << "=" << t1 << "+" << t2 << std::endl;
        std::cout << "Number of colors: " << g->GetVertexColorCount() << std::endl;
    }
}

void print_output(BipartiteGraphBicoloringInterface* g, int verbose) {
    if (verbose) {
        double t1 = g->GetVertexOrderingTime();
        double t2 = g->GetVertexColoringTime();
        std::cout << "Order and color time = " << t1 + t2 << "=" << t1 << "+" << t2 << std::endl;
        std::cout << "Number of colors: " << g->GetVertexColorCount() << std::endl;
    }
}

void print_output(BipartiteGraphPartialColoringInterface* g, int verbose) {
    if (verbose) {
        double t1 = g->GetVertexOrderingTime();
        double t2 = g->GetVertexColoringTime();
        std::cout << "Order and color time = " << t1 + t2 << "=" << t1 << "+" << t2 << std::endl;
        std::cout << "Number of colors: " << g->GetVertexColorCount() << std::endl;
    }
}

extern "C" int build_all_coloring_from_file(void** ref, int* len, const char* _filename, const char* _method, const char* _order, int verbose) {
    string filename = string(_filename);
    string method = string(_method);
    string order = string(_order);
    vector<int> coloring;

    std::ifstream file(filename);
    if (!file.good()) {
        std::cerr << "ColPack: Unable to open file " << filename << std::endl;
        return 0;
    }
    file.close();

    if (verbose) {
        std::cout << "Filename: " << filename << "\norder: " << order << "\nmethod: " << method << "\n";
    }

    if (GENERAL_COLORING.count(method)) {
        if (verbose) std::cout << "General Graph Coloring\n";
        GraphColoringInterface* g = new GraphColoringInterface(SRC_FILE, filename.c_str(), "AUTO_DETECTED");
        g->Coloring(order.c_str(), method.c_str());
        print_output(g, verbose);
        g->GetVertexColors(coloring);
        *len = static_cast<int>(coloring.size());
        *ref = static_cast<void*>(g);
    }
    else if (PARTIAL_COLORING.count(method)) {
        if (verbose) std::cout << "Partial Distance Two Bipartite Graph Coloring\n";
        BipartiteGraphPartialColoringInterface* g = new BipartiteGraphPartialColoringInterface(SRC_FILE, filename.c_str(), "AUTO_DETECTED");
        g->PartialDistanceTwoColoring(order, method);
        print_output(g, verbose);
        *ref = static_cast<void*>(g);
    }
    else if (BICOLORING.count(method)) {
        if (verbose) std::cout << "Bipartite Bipartite Graph Coloring\n";
        BipartiteGraphBicoloringInterface* g = new BipartiteGraphBicoloringInterface(SRC_FILE, filename.c_str(), "AUTO_DETECTED");
        g->Bicoloring(order, method);
        print_output(g, verbose);
        *ref = static_cast<void*>(g);
    }
    else {
        std::cerr << "ColPack: Invalid coloring method selected\n";
        return 0;
    }

    return 1;
}

extern "C" int build_coloring_from_csr(void** ref, int* len, unsigned int** csr, int rowcount, const char* _method, const char* _order, int verbose) {
    if (ref == nullptr || len == nullptr || csr == nullptr || _method == nullptr || _order == nullptr) {
        std::cerr << "ColPack: Invalid input parameters\n";
        return 0;
    }

    string method(_method);
    string order(_order);
    vector<int> coloring;
    void* g = nullptr;

    if (GENERAL_COLORING.count(method)) {
        GraphColoringInterface* g = new GraphColoringInterface(SRC_MEM_ADOLC, csr, rowcount);
        print_output(g, verbose);
        g->Coloring(order.c_str(), method.c_str());
        g->GetVertexColors(coloring);
        *len = static_cast<int>(coloring.size());
        *ref = static_cast<void*>(g);
    }
    else {
        std::cerr << "ColPack: Invalid coloring method selected\n";
        return 0;
    }

    return 1;
}

extern "C" int build_bicoloring_from_csr(void** ref, int* len, unsigned int** csr, int rowcount, int colcount, const char* _method, const char* _order, int verbose) {
    if (ref == nullptr || len == nullptr || csr == nullptr || _method == nullptr || _order == nullptr) {
        std::cerr << "ColPack: Invalid input parameters\n";
        return 0;
    }

    string method(_method);
    string order(_order);
    vector<int> coloring;
    void* g = nullptr;

    if (BICOLORING.count(method)) {
        BipartiteGraphBicoloringInterface* g = new BipartiteGraphBicoloringInterface(SRC_MEM_ADOLC, csr, rowcount, colcount);
        print_output(g, verbose);
        g->Bicoloring(order, method);
        *ref = static_cast<void*>(g);
    }
    else {
        std::cerr << "ColPack: Invalid coloring method selected\n";
        return 0;
    }

    return 1;
}

extern "C" int build_partial_coloring_from_csr(void** ref, int* len, unsigned int** csr, int rowcount, int colcount, const char* _method, const char* _order, int verbose) {
    if (ref == nullptr || len == nullptr || csr == nullptr || _method == nullptr || _order == nullptr) {
        std::cerr << "ColPack: Invalid input parameters\n";
        return 0;
    }

    string method(_method);
    string order(_order);
    vector<int> coloring;
    void* g = nullptr;

    if (PARTIAL_COLORING.count(method)) {
        BipartiteGraphPartialColoringInterface* g = new BipartiteGraphPartialColoringInterface(SRC_MEM_ADOLC, csr, rowcount, colcount);
        print_output(g, verbose);
        g->PartialDistanceTwoColoring(order, method);
        *ref = static_cast<void*>(g);
    }
    else {
        std::cerr << "ColPack: Invalid coloring method selected\n";
        return 0;
    }

    return 1;
}

extern "C" void get_colors(void* ref, int* _coloring, const char* _method, int verbose) {
    vector<int> coloring;
    std::string method(_method);

    if (GENERAL_COLORING.count(method)) {
        GraphColoringInterface* g = static_cast<GraphColoringInterface*>(ref);
        print_output(g, verbose);
        g->GetVertexColors(coloring);
    }
    else if (BICOLORING.count(method)) {
        BipartiteGraphBicoloringInterface* g = static_cast<BipartiteGraphBicoloringInterface*>(ref);
        print_output(g, verbose);
        g->GetVertexColors(coloring);
    }
    else if (PARTIAL_COLORING.count(method)) {
        BipartiteGraphPartialColoringInterface* g = static_cast<BipartiteGraphPartialColoringInterface*>(ref);
        print_output(g, verbose);
        g->GetVertexColors(coloring);
    }
    else {
        std::cerr << "ColPack: Invalid coloring method specified\n";
        return;
    }

    memcpy(_coloring, coloring.data(), coloring.size() * sizeof(int));
}

extern "C" void free_coloring(void** ref) {
    if (*ref != nullptr) {
        GraphColoringInterface *g = dynamic_cast<GraphColoringInterface*>(*ref);
        if (g != nullptr) {
            delete g;
            *ref = nullptr;
            return;
        }

        BipartiteGraphBicoloringInterface *bg = dynamic_cast<BipartiteGraphBicoloringInterface*>(*ref);
        if (bg != nullptr) {
            delete bg;
            *ref = nullptr;
            return;
        }

        BipartiteGraphPartialColoringInterface *pg = dynamic_cast<BipartiteGraphPartialColoringInterface*>(*ref);
        if (pg != nullptr) {
            delete pg;
            *ref = nullptr;
            return;
        }

        std::cerr << "Unknown interface type for free_coloring\n";
    }
}
