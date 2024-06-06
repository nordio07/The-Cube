// Talkie library
// Copyright 2011 Peter Knight
// This code is released under GPLv2 license.

//
// A female voice with an American accent
//
// Sound is output on digital pin 3 and/or 11. It can drive headphones directly, or add a simple audio amplifier to drive a loudspeaker.

#include <Wire.h>

#include <Arduino.h>

#include "Talkie.h"
#include "Vocab_US_Clock.h"
#include "Vocab_Special.h"

Talkie voice;

int change = 0;
int epoch = 0;
int a;
int ca = -1;
int c;
int cc = -1;
int ac;
int f;
int g;
int finish = 0;

void setup() {
    pinMode(LED_BUILTIN, OUTPUT);
    Serial.begin(115200);
#if defined(__AVR_ATmega32U4__) || defined(SERIAL_USB) || defined(SERIAL_PORT_USBVIRTUAL)  || defined(ARDUINO_attiny3217)
    delay(4000); // To be able to connect Serial monitor after reset or power up and before first print out. Do not wait for an attached Serial Monitor!
#endif
    // Just to know which program is running on my Arduino
    Serial.println(F("START " __FILE__ " from " __DATE__ "\r\nUsing library version " VERSION_TALKIE));

//    voice.doNotUseInvertedOutput();
#if defined(TEENSYDUINO)
    pinMode(5, OUTPUT);
    digitalWrite(5, HIGH); //Enable Amplified PROP shield
#endif

  Serial.begin(115200);
	Wire.begin(3);
	Wire.onRequest(manda);
  Wire.onReceive(ricevi);

}

void loop() { 
  if(g == 1) {
    tulke(a, c);
    g = 0;
  }
  delay(1000);
}

void tulke(int ora, int minuti) {
  voice.say(spPAUSE1);
  voice.say(spc_THE);
  voice.say(spc_TIME);
  voice.say(spc_IS);
  switch(ora) {
    case 1:
      voice.say(spc_ONE);
      break;

    case 2:
      voice.say(spc_TWO);
      break;
    
    case 3:
      voice.say(spc_THREE);
      break;

    case 4:
      voice.say(spc_FOUR);
      break;

    case 5:
      voice.say(spc_FIVE);
      break;
    
    case 6:
      voice.say(spc_SIX);
      break;

    case 7:
      voice.say(spc_SEVEN);
      break;

    case 8:
      voice.say(spc_EIGHT);
      break;
    
    case 9:
      voice.say(spc_NINE);
      break;

    case 10:
      voice.say(spc_TEN);
      break;

    case 11:
      voice.say(spc_ELEVEN);
      break;
    
    case 12:
      voice.say(spc_TWELVE);
      break;

    case 13:
      voice.say(spc_THIRTEEN);
      break;

    case 14:
      voice.say(spc_FOURTEEN);
      break;
    
    case 15:
      voice.say(spc_FIFTEEN);
      break;

    case 16:
      voice.say(spc_SIXTEEN);
      break;

    case 17:
      voice.say(spc_SEVENTEEN);
      break;
    
    case 18:
      voice.say(spc_EIGHTEEN);
      break;

    case 19:
      voice.say(spc_NINETEEN);
      break;

    case 20:
      voice.say(spc_TWENTY);
      break;
    
    case 21:
      voice.say(spc_TWENTY);
      voice.say(spc_ONE);
      break;

    case 22:
      voice.say(spc_TWENTY);
      voice.say(spc_TWO);
      break;

    case 23:
      voice.say(spc_TWENTY);
      voice.say(spc_THREE);
      break;
    
    case 24:
      voice.say(spc_TWENTY);
      voice.say(spc_FOUR);
      break;
  }

  switch(minuti) {
    case 1:
      voice.say(spc_ONE);
      break;

    case 2:
      voice.say(spc_TWO);
      break;
    
    case 3:
      voice.say(spc_THREE);
      break;

    case 4:
      voice.say(spc_FOUR);
      break;

    case 5:
      voice.say(spc_FIVE);
      break;
    
    case 6:
      voice.say(spc_SIX);
      break;

    case 7:
      voice.say(spc_SEVEN);
      break;

    case 8:
      voice.say(spc_EIGHT);
      break;
    
    case 9:
      voice.say(spc_NINE);
      break;

    case 10:
      voice.say(spc_TEN);
      break;

    case 11:
      voice.say(spc_ELEVEN);
      break;
    
    case 12:
      voice.say(spc_TWELVE);
      break;

    case 13:
      voice.say(spc_THIRTEEN);
      break;

    case 14:
      voice.say(spc_FOURTEEN);
      break;
    
    case 15:
      voice.say(spc_FIFTEEN);
      break;

    case 16:
      voice.say(spc_SIXTEEN);
      break;

    case 17:
      voice.say(spc_SEVENTEEN);
      break;
    
    case 18:
      voice.say(spc_EIGHTEEN);
      break;

    case 19:
      voice.say(spc_NINETEEN);
      break;

    case 20:
      voice.say(spc_TWENTY);
      break;
    
    case 21:
      voice.say(spc_TWENTY);
      voice.say(spc_ONE);
      break;

    case 22:
      voice.say(spc_TWENTY);
      voice.say(spc_TWO);
      break;

    case 23:
      voice.say(spc_TWENTY);
      voice.say(spc_THREE);
      break;
    
    case 24:
      voice.say(spc_TWENTY);
      voice.say(spc_FOUR);
      break;
    
    case 25:
      voice.say(spc_TWENTY);
      voice.say(spc_FIVE);
      break;

    case 26:
      voice.say(spc_TWENTY);
      voice.say(spc_SIX);
      break;
    
    case 27:
      voice.say(spc_TWENTY);
      voice.say(spc_SEVEN);
      break;

    case 28:
      voice.say(spc_TWENTY);
      voice.say(spc_EIGHT);
      break;

    case 29:
      voice.say(spc_TWENTY);
      voice.say(spc_NINE);
      break;
    
    case 30:
      voice.say(spc_THIRTY);
      break;

    case 31:
      voice.say(spc_THIRTY);
      voice.say(spc_ONE);
      break;

    case 32:
      voice.say(spc_THIRTY);
      voice.say(spc_TWO);
      break;
    
    case 33:
      voice.say(spc_THIRTY);
      voice.say(spc_THREE);
      break;

    case 34:
      voice.say(spc_THIRTY);
      voice.say(spc_FOUR);
      break;

    case 35:
      voice.say(spc_THIRTY);
      voice.say(spc_FIVE);
      break;
    
    case 36:
      voice.say(spc_THIRTY);
      voice.say(spc_SIX);
      break;

    case 37:
      voice.say(spc_THIRTY);
      voice.say(spc_SEVEN);
      break;

    case 38:
      voice.say(spc_THIRTY);
      voice.say(spc_EIGHT);
      break;
    
    case 39:
      voice.say(spc_THIRTY);
      voice.say(spc_NINE);
      break;

    case 40:
      voice.say(spc_FOURTY);
      break;

    case 41:
      voice.say(spc_FOURTY);
      voice.say(spc_ONE);
      break;
    
    case 42:
      voice.say(spc_FOURTY);
      voice.say(spc_TWO);
      break;

    case 43:
      voice.say(spc_FOURTY);
      voice.say(spc_THREE);
      break;

    case 44:
      voice.say(spc_FOURTY);
      voice.say(spc_FOUR);
      break;
    
    case 45:
      voice.say(spc_FOURTY);
      voice.say(spc_FIVE);
      break;

    case 46:
      voice.say(spc_FOURTY);
      voice.say(spc_SIX);
      break;

    case 47:
      voice.say(spc_FOURTY);
      voice.say(spc_SEVEN);
      break;
    
    case 48:
      voice.say(spc_FOURTY);
      voice.say(spc_EIGHT);
      break;

    case 49:
      voice.say(spc_FOURTY);
      voice.say(spc_NINE);
      break;

    case 50:
      voice.say(spc_FIFTY);
      break;
    
    case 51:
      voice.say(spc_FIFTY);
      voice.say(spc_ONE);
      break;

    case 52:
      voice.say(spc_FIFTY);
      voice.say(spc_TWO);
      break;

    case 53:
      voice.say(spc_FIFTY);
      voice.say(spc_THREE);
      break;
    
    case 54:
      voice.say(spc_FIFTY);
      voice.say(spc_FOUR);
      break;
    
    case 55:
      voice.say(spc_FIFTY);
      voice.say(spc_FIVE);
      break;

    case 56:
      voice.say(spc_FIFTY);
      voice.say(spc_SIX);
      break;
    
    case 57:
      voice.say(spc_FIFTY);
      voice.say(spc_SEVEN);
      break;

    case 58:
      voice.say(spc_FIFTY);
      voice.say(spc_EIGHT);
      break;

    case 59:
      voice.say(spc_FIFTY);
      voice.say(spc_NINE);
      break;
  }
  finish = 1;
}

void ricevi(){
  while(Wire.available()){
    ac = Wire.read();
    f = (ac-(ac%100))/100;
    if( f == 1) {
      a = ac - 100;
    }
    if( f == 2) {
      c = ac - 200;
      g = 1;
    }
  } 
  Serial.print("a:   ");
  Serial.print(a);
  Serial.print("   c:   ");
  Serial.print(c);
  Serial.println();
}

void manda() {
  if(finish == 1) {
    Wire.write(change);
    finish = 0;
  }	
}