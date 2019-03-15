#include "fGraph.hpp"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <limits>
#include <set>
#include <sstream>
#include <string>
#include <utility>
#include <queue>
#include <list>
#include <unordered_map>

using namespace std;

fGraph::fGraph(void)
:graph(0){}

fGraph::~fGraph(void){
  for (auto it : graph){
    delete it.second;
  }
  /*for( unordered_map<string, double>::iterator it = graph.begin(); it !=graph.end(); it++){
    delete it;
  }*/
}

void fGraph::insert(string from, string to, double weight){
  
  unordered_map< string, fNode*>::iterator it = graph.find(from);
  fNode* city;

  //this city was not in the graph
  if( it == graph.end()){
    city = new fNode(from);
    city->neighbours.insert({to, weight});
    graph.insert({from, city});

  }
  //this city is already in the graph
  else{
    city = it->second;
    
    if(city->neighbours.find(from) != city->neighbours.end()){
      if(city->neighbours[from] > weight)
        city->neighbours[from] = weight;
    }
    else{
      city->neighbours.insert({to,weight});
    }
  }

  return;
}

bool fGraph::loadFromFile(const char* in_filename){
  ifstream infile(in_filename);

  while (infile) {
    string s;
    if (!getline(infile, s)) break;

    istringstream ss(s);
    vector<string> record;

    while (ss) {
      string s;
      if (!getline(ss, s, '\t')) break;
      record.push_back(s);
    }
    if (record.size() != 11) {
      continue;
    }

    //TODO - YOU HAVE THE PAIR OF IDS OF 2 FRIENDS IN 'RECORD'. WHAT DO NEED TO DO NOW? 
    //assuming I have the pair of IDS of 2 friendsi n 'RECORD'
    string from = record[2];
    string to = record[3];
    int dist = stoi(record[7]);

    this->insert( from, to, dist);
  }

  if (!infile.eof()) {
    cerr << "Failed to read " << in_filename << "!\n";
    return false;
  }

  infile.close();
  return true;

}
		
void fGraph::shortestPath(const string toC, const string fromC){
  priority_queue<fNode*, vector<fNode*>, fNodePtrComp> sp;
 
  fNode * curr;
  fNode * currN;
  double Dist;

  for(auto itr: graph){
    curr = itr.second;
    if( curr ){
      curr->Distance = std::numeric_limits<double>::max();
      curr->prev = NULL;
      curr->done = false;
    }
  }

  curr = graph[toC];
  curr->Distance = 0;
  sp.push(curr);

  while(!sp.empty()){
    curr = sp.top();
    sp.pop();

    if ( graph[fromC]->done){
      return;
    }
    if( curr->done == false){
      curr->done = true;
      for( auto itr : curr->neighbours){
        Dist = curr->Distance + itr.second;
        currN = graph[itr.first];

        if( !currN){
          continue;
        }
        if( Dist < currN->Distance ){
          currN->prev = curr;
          currN->Distance = Dist;
          sp.push(currN);
        }

      }
    }
  }

  return;
}

void fGraph::printGraph(){
  for( auto itr: graph){
    cout << itr.first << " Distance: " << itr.second << '\n';
  }

}