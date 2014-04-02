/*
 * Path.cpp
 *
 *  Created on: Dec 4, 2011
 *      Author: gigemjt
 */

#include "Path.h"

Path::Path() {
	// TODO Auto-generated constructor stub

}
Path::Path(int w,Vertex* v)
{
	path_list.push_back(v);
	weight=w;
}
Path::Path(int w)
{
	weight=w;
}
void Path::add_vertex(Vertex* v)
{
	path_list.push_back(v);
}
void Path::add_vertex(Path* p,Vertex* v)
{
	if(path_list.size()>0)
		path_list.clear();
	for(int k=0;k<p->path_list.size();k++)
	{
		path_list.push_back(p->path_list[k]);
	}
	path_list.push_back(v);
}
Path::~Path() {
	// TODO Auto-generated destructor stub
}
