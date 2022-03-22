#include <Arduino.h>
#include <fFly.h>

Fly::Fly (){
    this->blinkLength=2000;
    this->startMillis=millis();
    this->flyColor=100; 
    this->startColor=100; 
    this->_increment=1;
    this->ledState=-1; // off
    uint8_t
      r = (uint8_t)(startColor >> 16),
      b = (uint8_t)(startColor >>  8),
      g = (uint8_t)startColor;
    uint8_t
      br = (uint8_t)(blinkColor >> 16),
      bb = (uint8_t)(blinkColor >>  8),
      bg = (uint8_t)blinkColor;
    
    this->rdiff = (r - br),
    this->bdiff = (g - bg),
    this->gdiff = (b - bb);
}

Fly::Fly (uint32_t fColor, uint32_t bColor, long bLength, long oRate, long offRte){
    this->blinkLength=bLength;
    this->startMillis=millis();
    this->startColor=fColor;   
    this->flyColor=fColor;   
    this->_increment=1;
    this->ledState=-1; //off
    this->onRate=oRate;
    this->offRate=offRte;
    this->blinkColor=bColor;
    uint8_t
      r = (uint8_t)(startColor >> 16),
      b = (uint8_t)(startColor >>  8),
      g = (uint8_t)startColor;
    uint8_t
      br = (uint8_t)(blinkColor >> 16),
      bb = (uint8_t)(blinkColor >>  8),
      bg = (uint8_t)blinkColor;
    
    this->rdiff = (r - br),
    this->bdiff = (b - bb),
    this->gdiff = (g - bg);
    
    
}

void Fly::setFgColor (uint32_t fColor){
    this->startColor=fColor;   
    this->flyColor=fColor;   
    this->_increment=1;
    this->ledState=-1; //off
    uint8_t
      r = (uint8_t)(startColor >> 16),
      b = (uint8_t)(startColor >>  8),
      g = (uint8_t)startColor;

    uint8_t
      br = (uint8_t)(blinkColor >> 16),
      bb = (uint8_t)(blinkColor >>  8),
      bg = (uint8_t)blinkColor;
    this->rdiff = (r - br),
    this->bdiff = (b - bb),
    this->gdiff = (g - bg);
    
    
}
void Fly::setBgColor (uint32_t fColor){
    this->blinkColor=fColor;   
    this->blinkColor=fColor;   
    this->_increment=1;
    this->ledState=-1; //off
    uint8_t
      r = (uint8_t)(startColor >> 16),
      b = (uint8_t)(startColor >>  8),
      g = (uint8_t)startColor;

    uint8_t
      br = (uint8_t)(blinkColor >> 16),
      bb = (uint8_t)(blinkColor >>  8),
      bg = (uint8_t)blinkColor;
    this->rdiff = (r - br),
    this->bdiff = (b - bb),
    this->gdiff = (g - bg);
    
    
}
float Fly::LFO(int seed){   // Wave function
  return sin(radians(seed)); 
}

uint32_t Fly::Color(uint8_t r, uint8_t g, uint8_t b){  
  return ((uint32_t)r << 16) | ((uint32_t)b <<  8) | g;
}

void Fly::Update(){
     uint8_t
      r = (uint8_t)(startColor >> 16),
      b = (uint8_t)(startColor >>  8),
      g = (uint8_t)startColor,
      er = (uint8_t)(blinkColor >> 16),
      eb = (uint8_t)(blinkColor >>  8),
      eg = (uint8_t)blinkColor;
    
    // First check to see if this fly should fire. 
    if (ledState==-1){
        if (millis()-startMillis>offRate){ // If nit firing, check every 2000 millis (2 seconds).
            //Serial.print(random(100));
            //Serial.println("random");
            if(random(100)<onRate){
                ledState=0; // fire!
               // Serial.println("turned on");
               // Serial.print("Rdiff:");
               // Serial.println(rdiff);
               // Serial.print("Bdiff:");
               // Serial.println(bdiff);
               // Serial.print("Gdiff:");
               // Serial.println(gdiff);
                //Serial.println("turned on");          
                startMillis=millis();
            }
        }
    }
    if (ledState==0){
        double milliFraction=(millis()-startMillis)/(float)blinkLength;
        //float amt = float((milliFraction * 360));
        float amt = LFO(float(milliFraction)*360)/2+.5;
        //flyColor=Color(r - (rdiff * amt), g - (gdiff * amt), b - (bdiff * amt));
        //Serial.print("R amount: ");
        if(_increment>0){
            flyColor=Color(r - (rdiff * amt), g - (gdiff * amt), b - (bdiff * amt));
            //flyColor=LFO(int(360*milliFraction))*255;
          //  Serial.println(r - (rdiff * amt));
          //  Serial.println(amt);

        }
        else {
            flyColor=Color(er + (rdiff * amt), eg + (gdiff * amt), eb + (bdiff * amt));
            //Serial.println(r - (rdiff * (amt)));
            //Serial.println(amt);

        }
        if (milliFraction>=1){
            if (_increment<0){ 
                // Finished its blick cycle, now go dormant
                ledState=-1; 
                //flyColor=0;
                //Serial.println("Set Black");
            }
            _increment*=-1;
            startMillis=millis(); 
        }
    }
}