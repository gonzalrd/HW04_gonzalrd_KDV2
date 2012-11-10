
#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/ImageIo.h"
#include "cinder/gl/Texture.h"
#include "cinder\Surface.h"
#include "cinder/Camera.h"
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
	int mapWidth;
	int mapHeight;
	Entry*myLocs;
	CameraPersp mCam;
	

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
	mapWidth = myImage.getWidth();
	mapHeight = myImage.getHeight();

//	gonzalrdStarbucks star;

	mCam.setPerspective( 60.0f, mapWidth/mapHeight, 5.0f, 3000.0f );

	Vec3f mEye  = Vec3f( 0.0f, 0.0f, 500.0f );
	Vec3f mCenter = Vec3f::zero();
	Vec3f mUp  =  Vec3f::yAxis();
	
	mCam.lookAt( mEye, mCenter, mUp );

   myLocs = read();


//	star.build(myLocs,size);

  // Entry* BEST = star.getNearest(.421, .675);

}

void HW04_gonzalrd_KDV2App::mouseDown( MouseEvent event )
{
	float x = event.getX();
	float y = event.getY();

}

void HW04_gonzalrd_KDV2App::update()
{

}

void HW04_gonzalrd_KDV2App::draw()
{
	// clear out the window with black
	//gl::clear( Color( 0, 0, 0 ) ); 

	gl::draw( myImage, getWindowBounds() );

	float x;
	float y;
	
	float refLine = .5;
	
	gl::color(Color(0.1f, 0.3f, 0.3f));

	for(int i = 0; i<size; i++){
		if(myLocs[i].x < 0.61 && myLocs[i].x >0.56 && myLocs[i].y < .72 && myLocs[i].y < .70 ){
		x = myLocs[i].x*mapWidth+100;
		y = myLocs[i].y*mapHeight+40;
		gl::drawSolidCircle( Vec2f( x , y ), 3.4f );
		}
	
	}

	gl::setMatrices( mCam );

}

CINDER_APP_BASIC( HW04_gonzalrd_KDV2App, RendererGl )
