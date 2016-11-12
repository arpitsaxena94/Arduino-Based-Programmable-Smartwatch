#include <DS3231.h>

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN 6
 int z=0;
int a[12];
int bright=51;
int watchMode=1;
int buttonInt=0;
//-----------------------
int redPin= 8;
int greenPin= 9;
int bluePin= 10;
//-------
int rePin= 11;
int gePin=12;
// Init the DS3231 using the hardware interface
DS3231  rtc(SDA, SCL);
// Init a Time-data structure
Time  t;

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(12, PIN, NEO_GRB + NEO_KHZ800);

// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.
 
void setup() {


  Serial.begin(9600);

  pinMode(2,INPUT);
  pinMode(3, INPUT);

  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
 

 

 // Initialize the rtc object
  rtc.begin();
  
  // The following lines can be uncommented to set the date and time
// rtc.setDOW(WEDNESDAY);     // Set Day-of-Week to SUNDAY
 rtc.setTime(6, 50, 10);     // Set the time to 12:00:00 (24hr format)
  //rtc.setDate(19, 10, 2016);   // Set the date to January 1st, 2014

  
  strip.begin();
  strip.setBrightness(bright);
  strip.show(); // Initialize all pixels to 'off'

   for(int i=0; i<=11; i++)
   {
    a[i] = (255./11.)*i;
   }

for(int j=0;j<=11;j++)
{ 
  for(int j=0;j<=11; j++)
  {
    strip.setPixelColor(j, Wheel(a[j]));
    
 
  }
    strip.show();
    rotate(a,12);
    delay(50);

}

for(int j=0;j<=11; j++)
  {
    strip.setPixelColor(j,0,0,0);
    
 
  }
    strip.show();

attachInterrupt(0,react,RISING);

}

void loop() {

 digitalWrite(redPin, HIGH);
   digitalWrite(bluePin, HIGH);
   digitalWrite(greenPin, HIGH);    

  
   

  t = rtc.getTime();

if(digitalRead(3)==HIGH){
  if(bright<255){
    bright=bright+51;

  }
  else{
  bright=51;
  }
      strip.setBrightness(bright);
   strip.show();
}



switch (watchMode)
{
  case 1:
  clearPixel();
  
 for(int i=0; i<=t.hour; i++)
 {
  strip.setPixelColor(i,255,0,0);
   strip.show();
 }
  delay(1000);

  for(int i=0; i<t.min/5; i++)
  {
    strip.setPixelColor(i,0,255,0);
    strip.show();
  }
 
delay(1000);

for(int i=0; i<t.min/5; i++)
  {
    strip.setPixelColor(i,0,0,0);
    strip.show();
  }

  delay(1000);
  break; 
  
  case 2:
  clearPixel();
 for(int j=0; j<=11; j++)
 {
  strip.setPixelColor(j,0,0,0);
 
 }
  strip.show();
 
 for(int i=0; i<= 11; i++)
 {
  int r=0;
 int g=0;
 int b=0;
  if(i==t.hour){
    b=255;  }  
  if(i==t.min/5){
    g=255;}
    if(i==t.sec/5){
    r=255;}

strip.setPixelColor(i,r,g,b);

 }
 
  strip.show();
  break;

   


  case 3:
clearPixel();
  for(int i=0;i<12; i++)
  {
  strip.setPixelColor(i,255,255,255);
  }
  strip.show();
  break;

 case 4:
clearPixel();
   for(int i=0; i<12; i++)
   {strip.setPixelColor(i,255,255,255);
   }
   strip.show();
   delay(50);
   for(int i=0; i<12; i++)
   {
    strip.setPixelColor(i,0,0,0);
   }
   strip.show();
  delay(50);
  break;
  case 5:
  
clearPixel();
  rainbow(50);
  break;
 
  /*case 5:
  clearPixel();
  
   float temp1 = rtc.getTemp();
   temp1= round(temp1*10);
   int temp2 =(int)(temp1);
 Serial.println(temp2);
  print_digits(temp2);
     
      
  for(int i=0; i<=(a-1); i++)
   {
  strip.setPixelColor(i,255,0,0);
}
strip.show();
delay(1000);
  for(int i=0; i<b; i++)
  {
    strip.setPixelColor(i,0,255,0);
  }
  strip.show();
  delay(1000);

  for(int i=0; i<c; i++)
  {
    strip.setPixelColor(i,0,0,255);
  }
  strip.show();
  delay(1000);
  */
break;
}



 //colorWipe(strip.Color(255, 0, 0), 50); // Red
  //colorWipe(strip.Color(0, 255, 0), 50); // Green
  //colorWipe(strip.Color(0, 0, 255), 50); // Blue
//colorWipe(strip.Color(0, 0, 0, 255), 50); // White RGBW
  // Send a theater pixel chase in...
  //theaterChase(strip.Color(127, 127, 127), 50); // White
  //theaterChase(strip.Color(127, 0, 0), 50); // Red
  //theaterChase(strip.Color(0, 0, 127), 50); // Blue
  //rainbow(20);
  //rainbowCycle(20);
  //theaterChaseRainbow(50);
    }

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}

void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    if(buttonInt==1){
      buttonInt=0;
    break;}
    delay(wait);
  }
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) {
  for (int j=0; j<10; j++) {  //do 10 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, c);    //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(uint8_t wait) {
  for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) {
      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, Wheel( (i+j) % 255));    //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}

void rotate(int arr[], int n)
{
    int temp=arr[11];
int j;
for(j=11;j>0;j--)
{
   arr[j]=arr[j-1];
   
}
arr[0]=temp;
}

void clearPixel(){
    for(short  i=0; i<12; i++) {
      strip.setPixelColor(i, 0,0,0);
      strip.show();
     /* if (!buttonInterupted()){
          if (animate){
              delay(DELAY);
          }
      }else
          break;*/
  }
}

void react(){
  
  if(watchMode<=5)
  {
  watchMode++;}
   else{
       watchMode=1;
       buttonInt=1;}
    
}
       
void print_digits(int n) {
    // In case n is negative, print the leading '-'
    // and transform n to a non-negative number
   
    
    int r,g,b;
    
    if(n < 0) {
        Serial.print("-");
        n = -n;
    }
    if(n/10) {
        print_digits(n/10);
        z++;
          clearPixel();
        for(int i=0; i<n/10; i++)
 {

  int r=0;
 int g=0;
 int b=0;
  if(z==1){
    r=255;  }  
  if(z==2){
    g=255;}
    if(z==3){
    b=255;}

strip.setPixelColor(i,r,g,b);
 r=0;b=0;g=0;

 }
 
  strip.show();
  delay(1000);
    }
    Serial.println( n%10);
}


