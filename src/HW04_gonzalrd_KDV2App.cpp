
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
	//void keyDown(keyDown event);
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
	void zoom();
	void drawLocs(uint8_t* pixels);
	void drawCircle(uint8_t* pixels, int center_x, int center_y, int r, Color8u c);
	void prepareSettings(Settings* settings);
	Entry*read();
	


private:
	Surface* map;
	int size;
	gl::Texture myImage;
	int mapWidth;
	int mapHeight;
	Entry*myLocs;
	CameraPersp mCam;

	

	static const int kAppWidth=1126;
	static const int kAppHeight= 674;
	static const int kTextureSize=2048;
	

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

void HW04_gonzalrd_KDV2App::prepareSettings(Settings* settings){
	(*settings).setWindowSize(kAppWidth,kAppHeight);
	(*settings).setResizable(false);
}



void HW04_gonzalrd_KDV2App::setup()
{

	map = new Surface(loadImage("usa-map.jpg"));

	uint8_t* dataArray = (*map).getData();

	
	

	

	//mapWidth = myImage.getWidth();
	//mapHeight = myImage.getHeight();

//	gonzalrdStarbucks star;

	//set up for camera for zoom
	mCam.setPerspective( 60.0f, getWindowAspectRatio(), 5.0f, -1.0f);



   myLocs = read();   

   drawLocs(dataArray);



//	star.build(myLocs,size);

  // Entry* BEST = star.getNearest(.421, .675);

}

//Goal D.
void HW04_gonzalrd_KDV2App::zoom(){

	Vec3f mEye  = Vec3f( 0.0f, 0.0f, 7000.0f );
	Vec3f mCenter = Vec3f::zero();
	Vec3f mUp  =  Vec3f::zAxis();
	
	mCam.lookAt( mEye, mCenter, mUp );

	mCam.setAspectRatio( getWindowAspectRatio() );

	gl::setMatrices(mCam);

}

void HW04_gonzalrd_KDV2App::mouseDown( MouseEvent event )
{
	float x = event.getX();
	float y = event.getY();
	zoom();

}

//void HW04_gonzalrd_KDV2App::keyDown( KeyDown event){


//}

void HW04_gonzalrd_KDV2App::update()
{
	//writeImage("gonzalrd.png",*map);
}

void HW04_gonzalrd_KDV2App::drawCircle(uint8_t* pixels, int center_x, int center_y, int r, Color8u c){
	for(int y = center_y-r; y<=center_y+r; y++){
		for(int  x =center_x-r; x<=center_x+r; x++){
			//Bounds test, to make sure we don't access array out of bounds
			if(y < 0 || x < 0 || x >= kAppWidth || y >= kAppHeight) continue;
			
					
			int dist = (int)sqrt((double)((x-center_x)*(x-center_x) + (y-center_y)*(y-center_y)));
			if(dist <= r){

				int offset = x + y*kAppWidth;
					pixels[3*(offset)] =  c.r;
					pixels[3*(offset)+1] = c.b;
					pixels[3*(offset)+2] =  c.g;
				
			}
		}
	}
}

//Goal A
void HW04_gonzalrd_KDV2App::drawLocs(uint8_t* pixels){
	int x;
	int y;

	float refx;
	float refy;

	int rad = 2;


	for(int i = 0; i<size; i++){

		//Northeast cost
		if(myLocs[i].x < 1 && myLocs[i].x > 0.7 && myLocs[i].y < .8 && myLocs[i].y > 0 ){

		//x =  myLocs[i].x*1000 + 250;
		//y =  myLocs[i].y*1000 + 100;
			
		x =  myLocs[i].x*1124;
		y =  myLocs[i].y*670;

		Color8u c = Color8u(22,103,70);

		drawCircle(pixels, x, y , rad , c);
		}
		
		//the midwest to california
		if(myLocs[i].x < 0.7 && myLocs[i].x > 0 && myLocs[i].y < .8 && myLocs[i].y > 0 ){

		//x =  myLocs[i].x*1000 + 130;
		//y =  myLocs[i].y*1000 + 170;

		x =  myLocs[i].x*1124;
		y =  myLocs[i].y*670;

		Color8u c = Color8u(12,100,130);
		drawCircle(pixels, x, y , rad , c);
		}
	
	}

}

void HW04_gonzalrd_KDV2App::draw()
{
	// clear out the window with black
	//gl::clear( Color( 0, 0, 0 ) ); 

	gl::draw(*map);
	

}

CINDER_APP_BASIC( HW04_gonzalrd_KDV2App, RendererGl )
