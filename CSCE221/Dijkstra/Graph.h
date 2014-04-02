#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Vertex.h"
#include "Edge.h"

using namespace std;

class Edge;
class Vertex;

class Graph{

private:
	vector<Vertex*> vertList;
	vector<Edge*> edgeList;
public:
	Graph(string filename) {
		// This function is the most difficult one. Be carefull.
		// Using ifstream, e.g. ifstream ifs(filename.c_str()); 
		// make new vertices and edges, also fill out the information for them
		// the expected result will be: vertList contains all vertices and edgeList contains all edges. 
		// and the vertices and edges should contains information, e.g. weight, source/end vertex pointer for edge
		ifstream input(filename.c_str());
		vector<vector<int>* > matrix;//a vector of a vector... good god
		int numvertex;
		input>>numvertex;
	//	cerr<<"output made it here";
		for(int k=0;k<numvertex;k++)
		{
			int in=0;
			int time=0;
			vector<int >* list=new vector<int>();
			input>>in;
		//	cerr<<"input? "<<in<<endl;
			while(in!=-1)
			{
		//		cerr<<"am i negative? "<<in<<endl;;
				if(time==0)
				{
					vertList.push_back(new Vertex(in));
				}else
					list->push_back(in);
				time++;

				input>>in;
		//		cerr<<in<<endl;
			}
		//	cerr<<"i am exiting "<<in<<endl;
			matrix.push_back(list);
		}
		for(int k=0;k<vertList.size();k++)
		{
	//		cerr<<"vertex "<<vertList[k]<<"id"<<vertList[k]->getID()<<endl;
		}
	//	cerr<<"printing matrix"<<endl;
		for(int k=0;k<matrix.size();k++)
		{
			for(int q=0;q<(matrix[k])->size();q++)
			{
		//		cerr<<(*matrix[k])[q]<<" ";
			}
		//	cerr<<endl;
		}

		input.close();
	//	cerr<<"output made it here"<<endl;
		for(int r=0;r<matrix.size();r++)
		{

			Vertex* start=vertList[r];
		//	cerr<<"starting with vertex "<<start->getID()<<" :: ";
			vector<int>* list=matrix[r];
			Vertex* end=NULL;
			int weight;
			int size=list->size();
	//		cerr<<"list size "<<size;
			for(int k=0;k<size;k++)
			{
		//		cerr<<"value "<<(*list)[k]<<" "<<"index "<<k<<" ";
				if(k%2==0)
				{
					int b=(*list)[k];
		//			cerr<<"getting vertex?"<<b;
					end=vertList[b-1];
				}
				else if(end!=NULL&&k%2==1)
				{
		//			cerr<<"end is??? "<<end<<" id "<<end->getID();
					Edge* i=new Edge(start,end,(*list)[k]);
					edgeList.push_back(i);
					start->add_edge(i,0);
					end->add_edge(i,1);
			//		i->print_edge();
					end=NULL;
				}
			}
	//		cerr<<endl;
		}
		//cerr<<"output made it to here"<<endl;
	}
	
	void PrintGraph() // print out all the edges and associated vertices in the entire graph
	{
		printf("Graph is as follows: ");

		// print all edges and related vertices
		printf("\nedges:\n");
		for(int i=0;i<edgeList.size();i++)
		{
			edgeList[i]->print_edge();
			// print out weight of edge
			// and source/end vertex id
		}
		printf("\nverticies:\n");
		// print all vertices and related edges
		for(int i=0;i<vertList.size();i++)
		{
			vertList[i]->print_vertex();
			// print out in edges and out edges with weight information
		}
	}
	vector<Vertex*> getVertices() const {
		return vertList;
	}
};
#endif
