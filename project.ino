
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <SoftwareSerial.h>

// OLED display TWI address
#define OLED_ADDR   0x3C
#define TxD 2
#define RxD 3
char str[100];
int i=0;

Adafruit_SSD1306 display(-1);

#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

SoftwareSerial mySerial(RxD, TxD); // RX, TX for Bluetooth

void setup() {
  mySerial.begin(9600); // For Bluetooth
  Serial.begin(9600); // Default communication rate of the Bluetooth module
  
  // initialize and clear display
  display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);
  display.clearDisplay();
  display.drawBitmap(0, 0, glass, 128, 128, WHITE);
  display.display();
  
  // display a pixel in each corner of the screen
  display.drawPixel(0, 0, WHITE);
  display.drawPixel(127, 0, WHITE);
  display.drawPixel(0, 63, WHITE);
  display.drawPixel(127, 63, WHITE);

 
}

void loop() {
  boolean isValidInput; 
  char c ;

    
   // get the next character from the bluetooth serial port
  do{
  
      while (!mySerial.available());  // LOOP...         
        c = mySerial.read();
        if(c!='*'){
            str[i] = c; 
            i = i + 1 ;
        }
 
       if (c=='*'){
          str[i]='\0';
          writeToOled(str);
          i =0;
          isValidInput=true;
       }
        
       isValidInput=false;
   
   }while(isValidInput);
}

void writeToOled(char arr[])
{
    Serial.println(arr);
    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(0,20);
    display.print(arr);
    display.display();
  
}


