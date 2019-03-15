#ifndef FGRAPH_HPP
#define FGRAPH_HPP

#include "fNode.hpp"
#include <unordered_map>
//#include "fNode.cpp"

using namespace std;

class fGraph {
	protected:

	public:
		unordered_map <string, fNode*> graph;

		fGraph(void);

		~fGraph(void);

		void insert( string c1, string c2, double);

		bool loadFromFile(const char* in_filename);

		void shortestPath(const string toC, const string fromC);

		void printGraph();


};
class fNodePtrComp {
public:
    bool operator()(fNode*& lhs, fNode*& rhs) const {
        return *lhs < *rhs;
    }
};
#endif