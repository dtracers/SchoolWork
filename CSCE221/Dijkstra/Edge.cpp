#include "Edge.h"

Edge::Edge(){
	sVertP=NULL;
	eVertP=NULL;
	weight=-1;
}
Edge::Edge(Vertex* svert, Vertex* evert,int weit) {
	sVertP=svert;
	eVertP=evert;
	weight=weit;
}	
int Edge::getWeight() {
	return weight;
}
Vertex* Edge::getsVertP() {
	return sVertP;
}
Vertex* Edge::geteVertP() {
	return eVertP;
}
void Edge::print_edge()
{
	printf("%d %d %d\n",getWeight(),getsVertP()->getID(),geteVertP()->getID());
}
