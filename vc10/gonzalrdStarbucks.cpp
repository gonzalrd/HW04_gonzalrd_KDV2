#pragma once
#include "gonzalrdStarbucks.h"

int size;
	
 void gonzalrdStarbucks::build(Entry* c, int n){
		size =  n;
	 entries = new Entry[n];

	 entries[1] = c[1]; //move over the first

	 for(int i = 1; i<n; i++){
		 double xoffset = abs(c[i-1].x - c[i].x);
		 double yoffset = abs(c[i-1].y - c[i].y);

		 if(xoffset > 0.00001 && yoffset > 0.00001){
			 entries[i] = c[i];
		 }
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



