
// include TFT and SPI libraries
#include <TFT.h>  
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>
Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(12345);

// pin definition for Arduino UNO
#define cs   10
#define dc   9
#define rst  8

// create an instance of the library
TFT TFTscreen = TFT(cs, dc, rst);

int x = 60;
int y = TFTscreen.height()/2;

int xPos;
int yPos;

int xPrev = x;
int yPrev = y;

float gforce = 0.00;
float gforce_prev = gforce;


void setup() {
  Serial.begin(9600);
  Serial.println("Accelerometer Test"); Serial.println("");
  accel.setRange(ADXL345_RANGE_2_G);
  // Initialise the sensor 
  if(!accel.begin())
  {
    // There was a problem detecting the ADXL345 ... check your connections 
    Serial.println("Ooops, no ADXL345 detected ... Check your wiring!");
    while(1);
  }
  
  //initialize the library
  TFTscreen.begin();

  //start up 
  printFlag();
  welcome();
  
  // clear the screen with a black background
  TFTscreen.background(0, 0, 0);  
  TFTscreen.stroke(0, 150, 0);
  TFTscreen.circle(60,TFTscreen.height()/2,55);
  TFTscreen.circle(60,TFTscreen.height()/2,27);
  TFTscreen.line(60,4,60,125);
  TFTscreen.line(0,TFTscreen.height()/2,121,TFTscreen.height()/2);

  TFTscreen.setTextSize(1);
  TFTscreen.text("<- ->",120,87);
}

void welcome()
{
  int color = 0;
  TFTscreen.background(0,0,0);

  delay(200);
  while(color < 255)
  {
    TFTscreen.stroke(color,color,color);
    TFTscreen.setTextSize(3);
    TFTscreen.text("WELCOME,",5,40);
    TFTscreen.text("ABOARD!",5,80);
    color = color + 5;
  }
  delay(500);
  
  while(color > 0){
    TFTscreen.stroke(color,color,color);
    TFTscreen.setTextSize(3);
    TFTscreen.text("WELCOME,",5,40);
    TFTscreen.text("ABOARD!",5,80);
    color = color - 20;
  }
  TFTscreen.noStroke();
  
}

void printFlag()
{
  TFTscreen.background(0,0,255);
  TFTscreen.stroke(0,255,0);
  TFTscreen.fill(0,255,0);
  TFTscreen.rect(0,0,53,128);

  TFTscreen.stroke(255,255,255);
  TFTscreen.fill(255,255,255);
  TFTscreen.rect(53,0,53,128);

  TFTscreen.noStroke();
  TFTscreen.noFill();
  delay(1500);
}

void loop() {
  sensors_event_t event; 
  accel.getEvent(&event);
  
  TFTscreen.stroke(0, 150, 0);
  TFTscreen.circle(60,TFTscreen.height()/2,55);
  TFTscreen.circle(60,TFTscreen.height()/2,27);
  TFTscreen.line(60,4,60,125);
  TFTscreen.line(0,TFTscreen.height()/2,121,TFTscreen.height()/2);
  
  //event.acceleration.x*0.101971621
  //event.acceleration.y*0.101971621
  //27 is 50%,55 is 100%
  
  x = 60;
  y = TFTscreen.height()/2;

  x = x - (event.acceleration.x*0.101971621)*55;
  y = y - (event.acceleration.y*0.101971621)*55;

  xPos = y;
  yPos = x;

  if(xPos != xPrev or yPos != yPrev)
  {
    TFTscreen.fill(0,0,0);
    TFTscreen.stroke(0,0,0);
    TFTscreen.circle(xPrev,yPrev,4);  
    TFTscreen.noFill();
    TFTscreen.noStroke();    
  }  
  
  TFTscreen.fill(0,150,0);
  TFTscreen.circle(xPos,yPos,4);
  TFTscreen.noFill();

  xPrev = xPos;
  yPrev = yPos;  

  //gforce data
  
  
  //double xforce = event.acceleration.x*0.101971621;
  double yforce = event.acceleration.y*0.101971621 - .03;

  /*
  if(xforce < 0)
  {
    xforce = -xforce;  
  }
  */

  if(yforce < 0)
  {
    yforce = -yforce;  
  }
  
  gforce = yforce;
  
  if(gforce > 1)
  {
    gforce = 1.00;  
  }
  
  TFTscreen.setTextSize(2);
  if(gforce != gforce_prev)
  {
   TFTscreen.setCursor(110,100); 
   TFTscreen.stroke(0,0,0);
   TFTscreen.print(gforce_prev);
  }

  
  if(gforce > .7)
  {
    TFTscreen.stroke(0,0,225);  
  }
  else if(gforce > .5)
  { 
    TFTscreen.stroke(0,100,220);
  }
  else if(gforce > .35)
  {
    TFTscreen.stroke(0,150,200);
  }
  else
  {
    TFTscreen.stroke(0,150,0);
  }
  
  TFTscreen.setCursor(110,100);
  
  TFTscreen.print(gforce);

  gforce_prev = gforce;
  //gforce data end
  //delay(2);
}

















