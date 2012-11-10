
#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/ImageIo.h"
#include "cinder/gl/Texture.h"
#include "cinder\Surface.h"
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
	


private:
	Surface* map;
	int size;
	gl::Texture myImage;

	static const int kAppWidth=800;
	static const int kAppHeight=600;
	static const int kTextureSize=1024;
	

};

Entry* HW04_gonzalrd_KDV2App::read()
{
	vector<Entry> readLocs;
	
	
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

	delete newEntry;
	
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

	myImage = gl::Texture( loadImage("usa-map.jpg"));


//	gonzalrdStarbucks star;

	//This is the setup that everyone needs to do
	
	
	

    Entry*myLocs = read();


//	star.build(myLocs,size);

//	Entry* BEST = star.getNearest(.334, .650);

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

	gl::draw( myImage, getWindowBounds() );


	

	gl::color(Color(0.7f, 0.3f, 0.2f));

	gl::drawSolidCircle( Vec2f( 100.0f, 100.0f ), 3.4f );

	

	
}

CINDER_APP_BASIC( HW04_gonzalrd_KDV2App, RendererGl )
