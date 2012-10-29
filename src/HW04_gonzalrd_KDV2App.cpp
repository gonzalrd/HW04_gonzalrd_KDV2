#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Starbucks.h"
#include "../vc10/gonzalrdStarbucks.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class HW04_gonzalrd_KDV2App : public AppBasic {
  public:
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
	Entry*read();
	int size;
	

};

Entry* HW04_gonzalrd_KDV2App::read()
{
	vector<Entry> readLocs;
	
	//Entry* entries = new Entry[size];
	
	ifstream in ("Starbucks_2006.csv");

	string line;
	double x;
	double y;
	int i = 0;
	
	
	while(!in.eof()){

	//for(int i = 0; i<size; i++){
	
	getline(in , line, ',');
	in.get();
	in >> x;
	in.get();
	in >> y;

	Entry* newEntry = new Entry();
	newEntry->identifier = line;
	newEntry->x = x;
	newEntry->y = y;

	
	readLocs.push_back(*newEntry);
	
	
}
	size = readLocs.size();
	Entry*entries = new Entry[size];
	for(int n = 0; n< size; n++){
		entries[n] = readLocs[n];
	}

	return entries;
	
}

void HW04_gonzalrd_KDV2App::setup()
{
	gonzalrdStarbucks star;

	Entry*myLocs = read();

	star.build(myLocs,size);

	Entry* BEST = star.getNearest(.434, .345);

}

void HW04_gonzalrd_KDV2App::mouseDown( MouseEvent event )
{

}

void HW04_gonzalrd_KDV2App::update()
{
}

void HW04_gonzalrd_KDV2App::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) ); 
}

CINDER_APP_BASIC( HW04_gonzalrd_KDV2App, RendererGl )
