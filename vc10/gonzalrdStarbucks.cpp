#pragma once
#include "gonzalrdStarbucks.h"


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
						cur-> rightChild_ = newNode;
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
	
	 
	 
	 for(int i = 0; i< n; i++){
		 buildKD(root, &c[i], true); //alwasy want to start at the root.
	 }
 }

 //implementation of a linear search

Entry*  gonzalrdStarbucks::getNearest(double x, double y){

 Entry *Best =  search(root, x ,y ,true);
	

		return Best;

}

double gonzalrdStarbucks::calculateDis(Entry*data, double x2, double y2){
	
	if(data == NULL) return 4;
	double x1 = data->x ;
	double y1 = data->y;
	double dis = sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));

	return  dis;
}

//Got help from Brandon Harmon
Entry* gonzalrdStarbucks::search(Node*cur, double x , double y, bool xLevel){
	Entry*candidate;
	
	if(cur == NULL) return NULL;
	double curDis = calculateDis(cur->data_, x , y);
	if(!compareEntries(cur->data_, x,y) )return cur->data_;
	if(xLevel){
		if(x< cur->data_->x)
		{
			
			candidate = search(cur->leftChild_,x , y, false);
		}
		else
			candidate = search(cur->rightChild_ ,x, y, false);
		
}

		if(!xLevel){
		if(y< cur->data_->y)
		{

			candidate = search(cur->leftChild_,x , y, true);
		}
		else
			candidate = search(cur->rightChild_ ,x, y, true);
		
}
		double canDis = calculateDis(candidate ,x, y);

		if(curDis < canDis){
			candidate = cur->data_;
			canDis = curDis;
		}


		if(candidate->identifier != "root node") return candidate;
		else return cur->leftChild_->data_;

}
