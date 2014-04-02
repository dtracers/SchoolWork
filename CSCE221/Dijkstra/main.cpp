#include "PriorityQueueVector.h"
#include "PriorityQueue.h"
#include "Graph.h"
#include "Path.h"
#include <iostream>
#include <map>
#include <stdio.h>

const int MAX_NUM = 999999;

using namespace std;

void printGraph(map< Vertex*, Vertex*> pi, Vertex* s, Vertex* v, Vertex* u) {

};

int main(int argc, char** argv) 
{
//	cerr<<"haha";
//	int w=printf("haha2");
	//cerr<<w;
	int i, num;
	string str;
	if(argc!=2)
		str = "random_sparse.txt";//"random_sparse.txt";
	else
		str = argv[1];

	Graph graph(str);
//	graph.PrintGraph();

	vector< Vertex* > vet = graph.getVertices();
	vector<Vertex* >done;
	//initialize single source
	cout<<"Insert the vertex you want to get everything from:"<<endl;
	//int num;
	cin>>num;
	Vertex* chosen=vet[num-1];
	PriorityQueueVector<Vertex*>* p=new PriorityQueueVector<Vertex*>();//blah blah blah
	//initialize priority queue
	for(int k=0;k<vet.size();k++)
	{
		int distance=vet[k]==chosen?0:MAX_NUM;
		(p)->insertItem(vet[k],distance);
	}
//	cerr<<"change1"<<endl;
//	p->set_key(vet[10],4);
//	cerr<<"change2"<<endl;
//	p->set_key(vet[11],3);
//	cerr<<"change3"<<endl;
//	p->set_key(vet[12],6);
//	cerr<<"change4"<<endl;
//	p->set_key(vet[13],5);
//	cerr<<"change 5"<<endl;
	int pause;
//	cin>>pause;
	/*
	for(int k=0;k<vet.size();k++)
	{
		Vertex* item=p->removeMin();
		cerr<<"get items? "<<item->getID()<<endl;
	}
	*/
	//main algorithm
	map<Vertex*,Path*> lengths;
	lengths[chosen]=new Path(0,chosen);

	while(p->get_size()>0)
	{
		Vertex* current=p->removeMin();
		done.push_back(current);
		Path* current_path=lengths[current];
		vector<Edge*> list=current->getOutEdges();
		for(int k=0;k<list.size();k++)
		{
			Edge* path=list[k];
			Vertex* other=path->geteVertP();
			if(other==chosen)
							continue;
			int partial_length=path->getWeight();
			if(lengths.count(other)<=0)
			{
				lengths[other]=new Path(MAX_NUM);
			}
			Path* other_path=lengths[other];
			int other_length=other_path->weight;
			int total_length=current_path->weight+partial_length;
			if(total_length<other_length)
			{
				other_path->weight=total_length;
				other_path->add_vertex(current_path,other);
				p->set_key(other,total_length);
			}
		}

	}
	for(int k=0;k<vet.size();k++)
	{
		Path* p2=lengths[vet[k]];
		int length=lengths[vet[k]]->weight;
//		cerr<<done[k]<<endl;
		printf("%d\t",length);
		for(int q=0;q<p2->path_list.size();q++)
		{
			printf("%d ",p2->path_list[q]->getID());
		}
		printf("\n");

		//printf("the length from vertex %d to vertex %d is %d\n",chosen->getID(),vet[k]->getID(),length);
	}
	printf("remove comparisons %d ",p->remove);
	// print out the results
//	cerr<<"what?";
	return 0;
}
