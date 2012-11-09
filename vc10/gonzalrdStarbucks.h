#pragma once
#include "Starbucks.h"
#include "../vc10/Node.h"
#include <vector>




class gonzalrdStarbucks : public Starbucks {
/* member variables and methods declared here */
public:
	virtual void build(Entry* c, int n);
	virtual Entry* getNearest(double x, double y);
	Entry* entries;
private:
	Node * root; //maybe make this as my root not. //
	Entry*pickRoot();
	bool compareEntries(Entry*cur, double x , double y);
	void buildKD(Node*cur, Entry*data, bool xLevel); //cur is the current node, node is the one you are entering.
	Entry * search(Node*cur, double x , double y, bool xLevel);
	double calculateDis(Entry*data, double x2, double y2);
};
