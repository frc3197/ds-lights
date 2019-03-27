#include <Adafruit_NeoPixel.h>

#define NUM 149
#define PIN 8

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUM, PIN, NEO_GRB + NEO_KHZ800);

//rainbow data
uint32_t rainbowArr[NUM];
uint32_t chaserArr[NUM];
uint32_t randomArr[NUM];
int rainbowCounter = 0;
int rainbowDelay;

int mode;

void setup() {
  pinMode(5, INPUT);
  pixels.begin();
  Serial.begin(57600);

  for (int i = 0; i < NUM; i++) {
    rainbowArr[i] = Wheel((int) ((i * 255.0f) / NUM));
    float a = (sin(TWO_PI * i * 6 / NUM) + 1) * 0.5;
//    chaserArr[i] = pixels.Color(255 * a, 48 * a, 0);
    chaserArr[i] = pixels.Color(10 * a, 10 * a, 255 * a);
    randomArr[i] = pixels.Color(255 * a, 10 * a, 10 * a);
  }

  
  
  rainbowDelay = 10;

mode = 2;

}

bool previous = false;
void loop() {
  
  if(digitalRead(5) && false){
    if(!previous){
    previous = true;
    mode = (mode + 1) % 4;
    }
  } else {
    previous = false;
  }
  
  switch(mode){
//    case 0:
//     setColor(pixels.Color(255,0,0));
//    break;
//     case 1:
//    setColor(pixels.Color(0,0,255));
//    break;
    case 2:
    rainbow();
    break;
//    case 3:
//    //CHASE
//    for (int i = 0; i < NUM; i++) {
//      pixels.setPixelColor(i, chaserArr[(i + rainbowCounter) % NUM]);
//    }
//      rainbowCounter=(rainbowCounter + 1) % NUM;
//  delay(rainbowDelay);
//    break;
//    case 4:
//     for (int i = 0; i < NUM; i++) {
//      pixels.setPixelColor(i, randomArr[(i + rainbowCounter) % NUM]);
//    }
//      rainbowCounter=(rainbowCounter + 1) % NUM;
//  delay(rainbowDelay);
//  break;
  }
  pixels.show();
}



void setColor(uint32_t color){
    for (int i = 0; i < NUM; i++) {
    pixels.setPixelColor(i, color);
  }
}

void rainbow() {
  for (int i = 0; i < NUM; i++) {
    pixels.setPixelColor(i, rainbowArr[(i + rainbowCounter) % NUM]);
  }
  rainbowCounter=(rainbowCounter + 1) % NUM;
  delay(rainbowDelay);
}

uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return pixels.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return pixels.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return pixels.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}
