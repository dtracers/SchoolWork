#include "Vertex.h"

Vertex::Vertex(int sid) {
	id=sid;
}
void Vertex::print_vertex()
{
	printf("current vertex: %d adjacent vertices: ",getID());
	for(int listi=0;listi<2;listi++)
	{
		printf(listi==0?"IN ":"OUT ");
		vector<Edge*> list=listi==0?inList:outList;
		if(list.size()==0)
			printf("N/A ");
		for(int k=0;k<list.size();k++)
		{
			Edge* in=list[k];
			printf("V:%d W:%d ",
				listi==0?in->getsVertP()->getID():in->geteVertP()->getID(),in->getWeight());
				//gets the start if edge is input or start if edge is output
		}
	}
	printf("\n");
}
void Vertex::add_edge(Edge* e,int i)
{
	if(i==0)//then it is output
		outList.push_back(e);
	else if(i==1)
		inList.push_back(e);
}
