#pragma once
#include "gonzalrdStarbucks.h"
#include "Node.h"

int size;

//this is a recursive method - deteminres if two entries are the same and returns true if they are
bool gonzalrdStarbucks::compareEntries(Entry*cur, Entry*data){

	double xoffset = abs(cur->x - data->x);
	double yoffset = abs(cur->y - data->y);

	if((xoffset < .00001) && (yoffset < .00001)) {return false;}

	else {return true;}
	
}

void gonzalrdStarbucks:: buildKD(Node*cur, Entry*data, bool xLevel){
//handles the left side
	if(xLevel){
		if(!compareEntries(cur->data_, data)){ //compate the data)
			if(xLevel){ //compare by x
				if(cur->data_->x > data->x){
					if(cur->leftChild_ == NULL){ 
						Node* newNode = new Node();
						newNode->data_ = data;
						cur-> leftChild_ = newNode;
					}
					else {buildKD(cur->leftChild_, data,false);}
				}
		}
		}
	}
//handles the right side
	if(xLevel){
		if(!compareEntries(cur->data_, data)){ //compate the data)
			if(xLevel){ //compare by x
				if(cur->data_->x < data->x){
					if(cur->rightChild_ == NULL)
						{ 
						Node* newNode = new Node();
						newNode->data_ = data;
						cur-> rightChild_ = newNode;
						}
					else {buildKD(cur->rightChild_, data,false);}
				}
		}
		}
	}

	//the y levels
		//left condidtion
		if(!xLevel){
		if(!compareEntries(cur->data_, data)){ //compate the data)
			if(xLevel){ //compare by y
				if(cur->data_->y > data->y){
					if(cur->leftChild_ == NULL)
						{ 
						Node* newNode = new Node();
						newNode->data_ = data;
						cur-> leftChild_ = newNode;
						}
					else {buildKD(cur->leftChild_, data,true);}
				}
		}
		}
	}

		//right condition
		if(!xLevel){
		if(!compareEntries(cur->data_, data)){ //compate the data)
			if(xLevel){ //compare by y
				if(cur->data_->y < data->y){
					if(cur->rightChild_ == NULL)
						{ 
						Node* newNode = new Node();
						newNode->data_ = data;
						cur-> leftChild_ = newNode;
						}
					else {buildKD(cur->rightChild_, data,true);}
				}
		}
		}
	}

}
	
 void gonzalrdStarbucks::build(Entry* c, int n){
//need to pick median and them remove from list
	 root = new Node();

	 root->data_->identifier = "root node";
	 root->data_->x = .5;
	 root->data_->y = .5;
	 //this equals the root node
	 entries = new Entry[n];

	 for(int i = 0; i< n; i++){
		 buildKD(root, &c[i], true); //alwasy want to start at the root.
	 }
 }

 //implementation of a linear search

Entry*  gonzalrdStarbucks::getNearest(double x, double y){

	Entry *Best = new Entry();
		double smallestDistance = sqrt(abs(entries[0].x-x) + abs(entries[0].y-y));

		for(int i=1; i<size; i++){

			double candidateDis = sqrt(abs(entries[i].x-x) + abs(entries[i].y-y));

			if(candidateDis < smallestDistance){
				Best->identifier = entries[i].identifier;
				Best->x = entries[i].x;
				Best->y = entries[i].y;
				smallestDistance = candidateDis;
			}

		}

		return Best;

}



