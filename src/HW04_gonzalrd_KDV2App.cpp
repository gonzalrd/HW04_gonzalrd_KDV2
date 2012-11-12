
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
#include "../vc10/Census.h"

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
	gonzalrdStarbucks star;
	uint8_t* dataArray;


	

	static const int kAppWidth=1126;
	static const int kAppHeight= 674;
	static const int kTextureSize=2048;

	void zoom();
	vector<Census> readCensus(string name,int start, int end);//start and end values so that I dont have to read in all the data at once. Makes it entirely to slow
	void drawChangDensity(uint8_t* pixels,int start, int end);
	void drawLocs(uint8_t* pixels);
	void drawCircle(uint8_t* pixels, int center_x, int center_y, int r, Color8u c);
	

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

	in.close();
	return entries;
	
}

void HW04_gonzalrd_KDV2App::prepareSettings(Settings* settings){
	(*settings).setWindowSize(kAppWidth,kAppHeight);
	(*settings).setResizable(false);
}

//Goal E and F and G. Reads in the data from the Census
vector<Census> HW04_gonzalrd_KDV2App::readCensus(string name, int start, int end)
{
	vector<Census> readCen;
	ifstream in (name);

	int n;
	int j;
	double x;
	double y;
	double starbucks;
	double population;
	double pepPerStar;
	
	
	//while(!in.eof()){
	for(int i =start; i<end; i++){
	in >> n;
	in.get();
	in >> j;
	in.get();
	in >> population;
	in.get();
	in >> starbucks;
	in.get();
	in >> pepPerStar;
	in.get();
	in >> x;
	in.get();
	in >> y;
	
	Census* data = new Census();
	data->x = x;
	data->y = y;
	data->population = population;
	data->starbucks = starbucks;
	data-> pepPerStar = pepPerStar;
	
	readCen.push_back(*data);

	delete data;
	
	}

	in.close();
	return readCen;
}


void HW04_gonzalrd_KDV2App::setup()
{



	map = new Surface(loadImage("usa-map.jpg"));

	 dataArray = (*map).getData();

//set up for camera for zoom
//mCam.setPerspective( 60.0f, getWindowAspectRatio(), 5.0f, kTextureSize);

   myLocs = read();   

   //drawChangDensity(dataArray, 500, 3000);

  // drawLocs(dataArray);

	star.build(myLocs,size);


}

//Goal D.-not implemented
void HW04_gonzalrd_KDV2App::zoom(){

	Vec3f mEye  = Vec3f( 0.0f, 0.0f, 500.0f );
	Vec3f mCenter = Vec3f(10.0f, 10.0f , 50.0f);
	Vec3f mUp  =  Vec3f(1.0f, -5.0f, 1.0f);
	
	mCam.lookAt( mEye, mCenter, mUp );

	mCam.setAspectRatio(getWindowAspectRatio());

	gl::setMatrices(mCam);

}


//GOAL E and F
void HW04_gonzalrd_KDV2App::drawChangDensity(uint8_t* pixels,int start, int end){
	//read in the data
	vector<Census> Cen2000 = readCensus("Census_2000.csv",  start,  end);
	vector<Census> Cen2010 = readCensus("Census_2010.csv", start,  end);

	Color8u red = Color8u(190,0,0);
	Color8u green  = Color8u(0,0,197);

	for(int i = 0; i< Cen2000.size(); i++){
		float density2000 = Cen2000[i].starbucks/Cen2000[i].pepPerStar;
		float  density2010= Cen2010[i].starbucks/Cen2010[i].pepPerStar;

		if(density2000 > density2010){//if densisty decreased color the region red
			int x = Cen2000[i].x*kAppWidth;
			int y = Cen2000[i].y*kAppHeight;
			
			for(int n = x; n < x+5; n++){
				for(int j = y; j < y+5; j++){
				int offset = n + j*kAppWidth;
					pixels[3*(offset)] =  red.r;
				}
			}
		}

		else if(density2000 < density2010){//if densisty increases
			int x = Cen2000[i].x*kAppWidth;
			int y = Cen2000[i].y*kAppHeight;

					
			for(int w = x; w < x+5; w++){
				for(int l = y; l < y+5; l++){
					int offset = w + l*kAppWidth;
					
					pixels[3*(offset)+1] = green.g;
				}
			}
		}

	}

}
	
void HW04_gonzalrd_KDV2App::mouseDown( MouseEvent event )
{
	double x = event.getX()/kAppWidth;
	double y = event.getY()/kAppHeight;

	Entry* BEST = star.getNearest(x, y);

	int drawX = BEST->x*kAppWidth;
	int drawY = BEST->y*kAppHeight;

	Color8u c = Color8u(100,100,150);
	drawCircle(dataArray, drawX, drawY, 10,  c);

}


void HW04_gonzalrd_KDV2App::update()
{
	
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

//Goal A and C;
void HW04_gonzalrd_KDV2App::drawLocs(uint8_t* pixels){
	int x;
	int y;

	int rad = 2;

	int red = 0;
	int green=  10;
	int blue = 20;

	
	for(int i = 0; i<size; i++){

		green +=20;
		blue +=40;

		Color8u c = Color8u(red,green,blue);
		x =  myLocs[i].x*kAppWidth;
		y =  myLocs[i].y*kAppHeight;

		x =  myLocs[i].x*kAppWidth;
		y =  myLocs[i].y*kAppHeight;

		drawCircle(pixels, x, y , rad , c);
		
	}

}

void HW04_gonzalrd_KDV2App::draw()
{
	
	gl::draw(*map);
	
}

CINDER_APP_BASIC( HW04_gonzalrd_KDV2App, RendererGl )
