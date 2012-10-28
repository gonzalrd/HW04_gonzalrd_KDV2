#pragma once 
#include "Starbucks.h"

class Node
{
public:
	Node();

	Node*leftChild_;

	Node*rightChild_;

	Entry*data_;

	~Node(void);
};