/*
 * Path.h
 *
 *  Created on: Dec 4, 2011
 *      Author: gigemjt
 */
#include"Vertex.h"
#ifndef PATH_H_
#define PATH_H_

class Path {
public:
	vector<Vertex*> path_list;
	int weight;
	Path();
	Path(int w,Vertex* v);
	Path(int w);
	virtual ~Path();
	void add_vertex(Vertex* v);
	void add_vertex(Path* p,Vertex* v);
};

#endif /* PATH_H_ */
