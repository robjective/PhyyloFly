
#include <Arduino.h>
#include <fFly.h>
#include <Adafruit_NeoPixel.h>

const int ledPin1=3;
const int ledPin2=4;
const int numFlies=1;

Adafruit_NeoPixel strip1 = Adafruit_NeoPixel(numFlies, ledPin1, NEO_GRB + NEO_KHZ800);
//Adafruit_NeoPixel strip2 = Adafruit_NeoPixel(numFlies, ledPin2, NEO_GRB + NEO_KHZ800);
Fly Flies[numFlies];

void setup ()
{
  //Serial.begin(115200); 
  //Serial.println("Started");
  strip1.begin();
  //strip2.begin();
  for (int i=0;i<numFlies;i++){
     // Flies[i]= Fly(number, foreground color, background color, blinklength, onrate, off length)
     // Pinkish to black
     //Flies[i]=Fly(Flies[i].Color(0,50,254),Flies[i].Color(0,0,0),random(20,2400),random(100));//,random(1000,4000)
     // Greenish to black 
   Flies[i]=Fly(Flies[i].Color(254,20,70),Flies[i].Color(0,0,0),random(500,2400),random(100),random(500,2400));
//      black blinks so mostly green
     //Flies[i]=Fly(Flies[i].Color(0,0,0),Flies[i].Color(254,0,50),random(500,2000),random(100),random(4000,10000));
     // white blinks so mostly red
  //   Flies[i]=Fly(Flies[i].Color(254,254,254),Flies[i].Color(0,0,200),random(500,2000),random(100));
     // white blinks, mostly black
     //Flies[i]=Fly(Flies[i].Color(254,254,254),Flies[i].Color(0,0,0),random(500,2000),random(100));
     // black blinks, mostly white
     //Flies[i]=Fly(Flies[i].Color(0,0,0),Flies[i].Color(254,254,254),random(500,2000),random(100),random(4000,10000));
     // white and gold
     //Flies[i]=Fly(Flies[i].Color(254,254,254),Flies[i].Color(254,0,223),random(500,2000),random(100),random(4000,10000));
     // BLUE TO SLOW PUTPLE
     //Flies[i]=Fly(Flies[i].Color(0,254,254),Flies[i].Color(0,254,0),random(2000,4000),random(100));
     // metalic red to tourquouise
     //Flies[i]=Fly(Flies[i].Color(0,0,212),Flies[i].Color(209,204,72),random(200,1000),random(100),random(4000,10000));
  }
}

void loop ()
{
 for (int i=0;i<numFlies;i++){
    Flies[i].Update();
 }
    strip1.setPixelColor(0,Flies[0].flyColor); 
   // strip2.setPixelColor(0,Flies[1].flyColor); 
  
  
  strip1.show();
 // strip2.show();
}  
