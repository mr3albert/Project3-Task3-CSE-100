#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

class fNode{
	public:
		string cityN;
		double Distance;
		fNode* prev;
		bool done;

		unordered_map<string, double> neighbours;

		//overloaded the operator for use in the priority que
		//compare core degrees
		bool operator<( const fNode& other){
		  if (this->Distance > other.Distance){
		    return true;
		  }

		  return false;
		}

		fNode(string from){
			cityN = from;
		}
};
