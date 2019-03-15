#include "fGraph.hpp"
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

void usage(char* program_name) {
  cerr << program_name << " called with incorrect arguments." << endl;
  cerr << "Usage: " << program_name
       << " friendship_pairs_file k_value output_file"
       << endl;
  exit(-1);
}

int main(int argc, char* argv[]) {
  

  if (argc != 4) {
    usage(argv[0]);
  }
  

  char* graph_filename = argv[1];
  char* cities_filename = argv[2];
  char* output_filename = argv[3];

  //creating graph
  fGraph fg;
  fg.loadFromFile( graph_filename );

  //TODO   
  /* You can call the pathfinder function from here */
  ifstream cityfile(cities_filename);
  ofstream outfile(output_filename);

  vector<string> flightpath;

  while (cityfile) {
    string s;
    if (!getline(cityfile, s)) break;

    istringstream ss(s);

    while (ss) {
      string s;
      if (!getline(ss, s, '\n')) break;
      flightpath.push_back(s);
    }
  }

  double dist0123 = 0;
  double dist0132 = 0;
  double dist0231 = 0;
  double dist0213 = 0;
  double dist0312 = 0;
  double dist0321 = 0;

  //flight distance! 0123
  fg.shortestPath(flightpath[0],flightpath[1]);
  dist0123 += fg.graph[flightpath[1]]->Distance;
  fg.shortestPath(flightpath[1],flightpath[2]);
  dist0123 += fg.graph[flightpath[2]]->Distance;
  fg.shortestPath(flightpath[2],flightpath[3]);
  dist0123 += fg.graph[flightpath[3]]->Distance;

  //flight distance! 0132
  fg.shortestPath(flightpath[0],flightpath[1]);
  dist0132 += fg.graph[flightpath[1]]->Distance;
  fg.shortestPath(flightpath[1],flightpath[3]);
  dist0132 += fg.graph[flightpath[3]]->Distance;
  fg.shortestPath(flightpath[3],flightpath[2]);
  dist0132 += fg.graph[flightpath[2]]->Distance;

  //flight distance! 0231
  fg.shortestPath(flightpath[0],flightpath[2]);
  dist0231 += fg.graph[flightpath[2]]->Distance;
  fg.shortestPath(flightpath[2],flightpath[3]);
  dist0231 += fg.graph[flightpath[3]]->Distance;
  fg.shortestPath(flightpath[3],flightpath[1]);
  dist0231 += fg.graph[flightpath[1]]->Distance;

  //flight distance! 0213
  fg.shortestPath(flightpath[0],flightpath[2]);
  dist0213 += fg.graph[flightpath[2]]->Distance;
  fg.shortestPath(flightpath[2],flightpath[1]);
  dist0213 += fg.graph[flightpath[1]]->Distance;
  fg.shortestPath(flightpath[1],flightpath[3]);
  dist0213 += fg.graph[flightpath[3]]->Distance;

    //flight distance! 0312
  fg.shortestPath(flightpath[0],flightpath[3]);
  dist0312 += fg.graph[flightpath[3]]->Distance;
  fg.shortestPath(flightpath[3],flightpath[1]);
  dist0312 += fg.graph[flightpath[1]]->Distance;
  fg.shortestPath(flightpath[1],flightpath[2]);
  dist0312 += fg.graph[flightpath[2]]->Distance;

  //flight distance! 0321
  fg.shortestPath(flightpath[0],flightpath[3]);
  dist0321 += fg.graph[flightpath[3]]->Distance;
  fg.shortestPath(flightpath[3],flightpath[2]);
  dist0321 += fg.graph[flightpath[2]]->Distance;
  fg.shortestPath(flightpath[2],flightpath[1]);
  dist0321 += fg.graph[flightpath[1]]->Distance;

  vector<double> distList;
	distList.push_back(dist0123);
  distList.push_back(dist0132);
  distList.push_back(dist0231);
  distList.push_back(dist0213);
  distList.push_back(dist0312);
  distList.push_back(dist0321); 	

  double mindist = distList[0];
  int minIndex = 0;
  for (unsigned int i = 0; i < distList.size(); i++){
  	if(mindist >= distList[i]){
  		mindist = distList[i];
  		minIndex = i;
  	}
  }

  //0123
  if(minIndex == 0){
  	cout << "The shortest path through the three cities is the following: "
  			 << flightpath[0]
  			 << ", "
  			 << flightpath[1]
  			 << ", "
  			 << flightpath[2]
  			 << ",then "
  			 << flightpath[3]
  			 << ". \nAnd the distance is :"
  			 << distList[0] << "\n";
  			 outfile << "The shortest path through the three cities is the following: "
  			 << flightpath[0]
  			 << ", "
  			 << flightpath[1]
  			 << ", "
  			 << flightpath[2]
  			 << ",then "
  			 << flightpath[3]
  			 << ". \nAnd the distance is :"
  			 << distList[0] << "\n";
  }

  //0132
  if(minIndex == 1){
	cout << "The shortest path through the three cities is the following: "
			 << flightpath[0]
			 << ", "
			 << flightpath[1]
			 << ", "
			 << flightpath[3]
			 << ",then "
			 << flightpath[2]
			 << ". \nAnd the distance is :"
			 << distList[1] << "\n";
			 outfile << "The shortest path through the three cities is the following: "
			 << flightpath[0]
			 << ", "
			 << flightpath[1]
			 << ", "
			 << flightpath[3]
			 << ",then "
			 << flightpath[2]
			 << ". \nAnd the distance is :"
			 << distList[1] << "\n";
  }

  //0231
  if(minIndex == 2){
	cout << "The shortest path through the three cities is the following: "
			 << flightpath[0]
			 << ", "
			 << flightpath[2]
			 << ", "
			 << flightpath[3]
			 << ",then "
			 << flightpath[1]
			 << ". \nAnd the distance is :"
			 << distList[2] << "\n";
			 	outfile << "The shortest path through the three cities is the following: "
			 << flightpath[0]
			 << ", "
			 << flightpath[2]
			 << ", "
			 << flightpath[3]
			 << ",then "
			 << flightpath[1]
			 << ". \nAnd the distance is :"
			 << distList[2] << "\n";
  }

    //0213
  if(minIndex == 3){
	cout << "The shortest path through the three cities is the following: "
			 << flightpath[0]
			 << ", "
			 << flightpath[2]
			 << ", "
			 << flightpath[1]
			 << ",then "
			 << flightpath[3]
			 << ". \nAnd the distance is :"
			 << distList[3] << "\n";
			 	outfile << "The shortest path through the three cities is the following: "
			 << flightpath[0]
			 << ", "
			 << flightpath[2]
			 << ", "
			 << flightpath[1]
			 << ",then "
			 << flightpath[3]
			 << ". \nAnd the distance is :"
			 << distList[3] << "\n";

  }

  //0312
  if(minIndex == 4){
	cout << "The shortest path through the three cities is the following: "
			 << flightpath[0]
			 << ", "
			 << flightpath[3]
			 << ", "
			 << flightpath[1]
			 << ",then "
			 << flightpath[2]
			 << ". \nAnd the distance is :"
			 << distList[4] << "\n";
	outfile << "The shortest path through the three cities is the following: "
			 << flightpath[0]
			 << ", "
			 << flightpath[3]
			 << ", "
			 << flightpath[1]
			 << ",then "
			 << flightpath[2]
			 << ". \nAnd the distance is :"
			 << distList[4] << "\n";
  }

  //0321
  if(minIndex == 5){
		cout << "The shortest path through the three cities is the following: "
				 << flightpath[0]
				 << ", "
				 << flightpath[3]
				 << ", "
				 << flightpath[2]
				 << ",then "
				 << flightpath[1]
				 << ". \nAnd the distance is :"
				 << distList[5] << "\n";
		outfile << "The shortest path through the three cities is the following: "
			 << flightpath[0]
			 << ", "
			 << flightpath[3]
			 << ", "
			 << flightpath[2]
			 << ",then "
			 << flightpath[1]
			 << ". \nAnd the distance is :"
			 << distList[5] << "\n";

  }
  
 	if (!cityfile.eof()) {
    cerr << "Failed to read " << cities_filename << "!\n";
  }
  outfile.flush();
  cityfile.close();
  outfile.close();

}  