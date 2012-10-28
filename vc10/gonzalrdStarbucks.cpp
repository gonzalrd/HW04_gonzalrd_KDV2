#pragma once
#include "gonzalrdStarbucks.h"
#include "Node.h"

int size;

//this is a recursive method - deteminres if two entries are the same and returns true if they are
bool gonzalrdStarbucks::compareEntries(Entry*cur, double x , double y){

	double xoffset = abs(cur->x - x);
	double yoffset = abs(cur->y - y);

	if((xoffset < .00001) && (yoffset < .00001)) {return false;}

	else {return true;}
	
}

void gonzalrdStarbucks:: buildKD(Node*cur, Entry*data, bool xLevel){
//handles the left side
	if(compareEntries(cur->data_, data->x, data->y))
	{
	if(xLevel)
	{
		if(cur->data_->x > data->x){
				if(cur->leftChild_ == NULL){ 
						Node* newNode = new Node();
						newNode->data_ = data;
						cur-> leftChild_ = newNode;
					}
		else {buildKD(cur->leftChild_, data,false);}
				}

	//Handle the right side
	if(cur->data_->x < data->x){
					if(cur->rightChild_ == NULL)
						{ 
						Node* newNode = new Node();
						newNode->data_ = data;
						cur-> rightChild_ = newNode; 
						}
					else {buildKD(cur->rightChild_, data,false);}
				}
		}//end xLevel
		
	

	//the y levels
		//left condidtion
	if(!xLevel)
	{
	 //compare by y
				if(cur->data_->y > data->y)
				{
					if(cur->leftChild_ == NULL)
						{ 
						Node* newNode = new Node();
						newNode->data_ = data;
						cur-> leftChild_ = newNode;
						}
					else {buildKD(cur->leftChild_, data,true);}
				}
		

			//right condition
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

 Entry *Best =  search(root, x ,y ,true);
		//double smallestDistance = sqrt(abs(entries[0].x-x) + abs(entries[0].y-y));

		//for(int i=1; i<size; i++){

		//	double candidateDis = sqrt(abs(entries[i].x-x) + abs(entries[i].y-y));

		//	if(candidateDis < smallestDistance){
			//	Best->identifier = entries[i].identifier;
			//	Best->x = entries[i].x;
			//	Best->y = entries[i].y;
				//smallestDistance = candidateDis;
			//}

		//}

		return Best;

}

double gonzalrdStarbucks::calculateDis(double x1, double x2, double y1, double y2){

	double dis = sqrt(abs(x1-x2) + abs(y1-y2));
	return  dis;
}

Entry* gonzalrdStarbucks::search(Node*cur, double x , double y, bool xLevel){
	
	if(cur == NULL) return NULL;
	if(!compareEntries(cur->data_, x , y)) return cur->data_;
	if(xLevel){
		if(x < cur->data_->x){
			if(cur->leftChild_ == NULL) cur->data_;
			else if(x > cur->leftChild_->data_->x)
			{//check if bigger than left child
			//if yes then compare distance and return the closet one-do opposite for the right-before return
				double curDis = calculateDis(cur->data_->x, x , cur->data_->y, y);
				double canDis = calculateDis(cur->leftChild_->data_->x, x , cur->leftChild_->data_->y, y);
				if(curDis < canDis)
				{
					//check right here
					return cur->data_;
				}
				else
				{
					return  cur->leftChild_->data_;
				}
			}
			else
			{ 
				return search(cur->leftChild_,x,y,false);
			}
			
	}
		//right side
		else if(x > cur->data_->x){
			if(cur->rightChild_ == NULL) return cur->data_;

			else if(x < cur->rightChild_->data_->x)
			{//check if bigger than left child
			//if yes then compare distance and return the closet one-do opposite for the right-before return
				double curDis = calculateDis(cur->data_->x, x , cur->data_->y, y);
				double canDis = calculateDis(cur->rightChild_->data_->x, x , cur->rightChild_->data_->y, y);
				if(curDis < canDis)
				{
					//check right here
					return cur->data_;
				}
				else
				{
					return  cur->rightChild_->data_;
				}
			}
			else return search(cur->rightChild_,x,y,false);
		}
	}

	if(!xLevel){
		if(y < cur->data_->y){
			if(cur->leftChild_ == NULL) return cur->data_;
				else if(y > cur->leftChild_->data_->y)
			{//check if bigger than left child
			//if yes then compare distance and return the closet one-do opposite for the right-before return
				double curDis = calculateDis(cur->data_->x, x , cur->data_->y, y);
				double canDis = calculateDis(cur->leftChild_->data_->x, x , cur->leftChild_->data_->y, y);
				if(curDis < canDis)
				{
					//check right here
					return cur->data_;
				}
				else
				{
					return  cur->leftChild_->data_;
				}
			}
			else return search(cur->leftChild_,x,y,true);
	}
		else if(y > cur->data_->y){
			if(cur->rightChild_ == NULL) return cur->data_;
			else if(y < cur->rightChild_->data_->y)
			{//check if bigger than left child
			//if yes then compare distance and return the closet one-do opposite for the right-before return
				double curDis = calculateDis(cur->data_->x, x , cur->data_->y, y);
				double canDis = calculateDis(cur->rightChild_->data_->x, x , cur->rightChild_->data_->y, y);
				if(curDis < canDis)
				{
					//check right here
					return cur->data_;
				}
				else
				{
					return  cur->rightChild_->data_;
				}
			}
			else return search(cur->rightChild_,x,y,true);
		}
	}
		
}



