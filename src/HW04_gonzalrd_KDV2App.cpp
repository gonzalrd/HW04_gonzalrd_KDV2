
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
#include "cinder/Font.h"
#include "cinder/Text.h"

using namespace ci;
using namespace ci::app;
using namespace std;



class HW04_gonzalrd_KDV2App : public AppBasic {

  public:
	void setup();
	void keyDown(KeyEvent event);
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
	void render();
	void prepareSettings(Settings* settings);
	Entry*read();
	


private:
	Surface* map;
	int size;
	gl::Texture myImage;
	Entry*myLocs;
	CameraPersp mCam;
	gonzalrdStarbucks star;
	uint8_t* dataArray;
	Vec2i	tSize;
	gl::Texture texture_font_;
	double currentX;
	double currentY;


	

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

	int n;//dont care about this need to get to next one

	double x;
	double y;
	
	double population;

	int count = 0; //keep track of data. Dont want to read in entire set
	
	//while(!in.eof()){
	for(int i =start; i<end; i++){

			in >> n;
			in.get();
			in >> n;
			in.get();
			in >> n;
			in.get();
			in >> n;
			in.get();
			in >> population;
			in.get();
			in >> x;
			in.get();
			in >> y;
	
			Census* data = new Census();
			data->x = x;
			data->y = y;
			data->population = population;
		if(count % 50 == 0){
	
			readCen.push_back(*data);

			delete data;
		}
		count ++;
	}

	in.close();
	return readCen;
}


void HW04_gonzalrd_KDV2App::setup()
{

	currentX = -1;
	currentY = -1;

	map = new Surface(loadImage("usa-map.jpg"));

	 dataArray = (*map).getData();

	 tSize = Vec2i(600,30);
		render();
//set up for camera for zoom
//mCam.setPerspective( 60.0f, getWindowAspectRatio(), 5.0f, kTextureSize);

   myLocs = read();   

	star.build(myLocs,size);


}

//Goal D. 
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
	double searchRad = .3;

	for(int i = 0; i< Cen2000.size(); i++){
		int starbucks = star.SearchRegion(Cen2000[i].x, Cen2000[i].y, searchRad);
		float density2000 = starbucks/Cen2000[i].population;
		float  density2010 = starbucks/Cen2010[i].population;

		int x = Cen2000[i].x*kAppWidth;
		int y = Cen2000[i].y*kAppHeight;

		for(int n = x; n < x+15; n++){
		for(int j = y; j < y+15; j++){
			int offset = n + j*kAppWidth;

		if(density2000 > density2010){//if densisty decreased color the region red
			pixels[3*(offset)] =  red.r;
				}
		else if(density2000 < density2010){//if densisty increases
			pixels[3*(offset)+1] = green.g;
				}
			}
		}

	}

}
	
void HW04_gonzalrd_KDV2App::mouseDown( MouseEvent event )
{
	currentX = event.getX()/kAppWidth;
	currentY = 1-(event.getY()/kAppHeight);

}

void HW04_gonzalrd_KDV2App::keyDown(KeyEvent event){
	if(event.getCode() == event.KEY_d){
		
		drawChangDensity(dataArray, 600, 10000);
	}
	 else if(event.getCode() == event.KEY_l){
		   drawLocs(dataArray);
	}
		  
		} 
	
void HW04_gonzalrd_KDV2App::render(){

	Font ft  = Font("Times new roman",20);
	string ms = "Press d to see density change, l to see all locations and click to get Nearest-but you may need to travel across country or swim";
	TextBox tbox = TextBox().alignment( TextBox::CENTER ).font(ft).size( tSize.x, tSize.y ).text( ms );
	tbox.setColor( Color( 0.0f, 0.85f, 1.0f ) );
	tbox.setBackgroundColor( ColorA( 0, 0, 0, 0 ) );
	Vec2i sz = tbox.measure();
	console() << "Height: " << sz.y << endl;
	texture_font_ = gl::Texture( tbox.render() );

}

void HW04_gonzalrd_KDV2App::update()
{

	Entry* BEST = star.getNearest(currentX, currentY);

	int drawX = BEST->x*kAppWidth;
	int drawY = (1-BEST->y)*kAppHeight;

	if(currentX != -1 && currentY != -1){
	Color8u c = Color8u(150,150,0);
	drawCircle(dataArray, drawX, drawY, 10,  c);
	}
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
		y =  (1-myLocs[i].y)*kAppHeight;

		drawCircle(pixels, x, y , rad , c);
		
	}

}

void HW04_gonzalrd_KDV2App::draw()
{
	
	gl::draw(*map);
	gl::draw(texture_font_);
}

CINDER_APP_BASIC( HW04_gonzalrd_KDV2App, RendererGl )
