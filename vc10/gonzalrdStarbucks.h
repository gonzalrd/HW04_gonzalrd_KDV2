#pragma once
#include "Starbucks.h"
#include <vector>


//make a class nodes for ther K-d implementation
class Node
{ 
public:
	Node();

	Node*rightChild_; 

	Node*leftChild_;

	Node*next_;
	Entry*data_;

	~Node(void);
};


class gonzalrdStarbucks : public Starbucks {
/* member variables and methods declared here */
public:
	virtual void build(Entry* c, int n);
	virtual Entry* getNearest(double x, double y);
	Entry* entries;
	


};
