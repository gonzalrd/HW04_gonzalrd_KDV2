#include "cinder/gl/gl.h"
#include "cinder/app/AppBasic.h"
#include "Node.h"

//Defines a Node for Homework one.

//put getters and setters 



Node::Node(void)
{
	this->data_ = new Entry();
	this->leftChild_ = NULL;
	this->rightChild_ = NULL;
}


Node::~Node(void)
{
}
