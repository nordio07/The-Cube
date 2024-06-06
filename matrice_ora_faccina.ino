#include <WiFiS3.h>

#include <FastLED.h>

#include <Wire.h>


int status = WL_IDLE_STATUS;
#include "arduino_secrets.h" 
///////please enter your sensitive data in the Secret tab/arduino_secrets.h
char ssid[] = SECRET_SSID;        // your network SSID (name)
char pass[] = SECRET_PASS;    // your network password (use for WPA, or use as key for WEP)
int keyIndex = 0;            // your network key index number (needed only for WEP)

unsigned int localPort = 2390;      // local port to listen for UDP packets

IPAddress timeServer(162, 159, 200, 123); // pool.ntp.org NTP server

const int NTP_PACKET_SIZE = 48; // NTP timestamp is in the first 48 bytes of the message

byte packetBuffer[NTP_PACKET_SIZE]; //buffer to hold incoming and outgoing packets

// A UDP instance to let us send and receive packets over UDP
WiFiUDP Udp;

int epoch;
int a;
int c;
int A;
int B;
int C;
int D;

#define pin_buttom_ora 9

#define pin_buttom_0 2
#define pin_buttom_1 4
#define pin_buttom_2 5
#define pin_buttom_3 6
#define pin_buttom_4 7
#define pin_buttom_5 8

#define pin_pot_lum A1

#define pin_aut_lum A2

#define NUM_LEDS 256

#define DATA_PIN 12

CRGB leds[NUM_LEDS];

//#include <SoftwareSerial.h>

//SoftwareSerial port(10, 11); // RX, TX

byte frame[16] [16] = {
  {0,0,0,0,  0,0,0,0,  0,0,0,0, 0,0,0,0,}, // 1
  {0,0,0,0,  0,0,0,0,  0,0,0,0, 0,0,0,0,}, // 2
  {0,0,0,0,  0,0,0,0,  0,0,0,0, 0,0,0,0,}, // 3
  {0,0,0,0,  0,0,0,0,  0,0,0,0, 0,0,0,0,}, // 4
  {0,0,0,0,  0,0,0,0,  0,0,0,0, 0,0,0,0,}, // 5
  {0,0,0,0,  0,0,0,0,  0,0,0,0, 0,0,0,0,}, // 6
  {0,0,0,0,  0,0,0,0,  0,0,0,0, 0,0,0,0,}, // 7
  {0,0,0,0,  0,0,0,0,  0,0,0,0, 0,0,0,0,}, // 8
  {0,0,0,0,  0,0,0,0,  0,0,0,0, 0,0,0,0,}, // 9
  {0,0,0,0,  0,0,0,0,  0,0,0,0, 0,0,0,0,}, // 10
  {0,0,0,0,  0,0,0,0,  0,0,0,0, 0,0,0,0,}, // 11
  {0,0,0,0,  0,0,0,0,  0,0,0,0, 0,0,0,0,}, // 12
  {0,0,0,0,  0,0,0,0,  0,0,0,0, 0,0,0,0,}, // 13
  {0,0,0,0,  0,0,0,0,  0,0,0,0, 0,0,0,0,}, // 14
  {0,0,0,0,  0,0,0,0,  0,0,0,0, 0,0,0,0,}, // 15
  {0,0,0,0,  0,0,0,0,  0,0,0,0, 0,0,0,0,}, // 16
};

byte frameR[16] [16] = {
  {0,0,0,0,  0,0,0,0,  0,0,0,0, 0,0,0,0,}, // 1
  {0,0,0,0,  0,0,0,0,  0,0,0,0, 0,0,0,0,}, // 2
  {0,0,0,0,  0,0,0,0,  0,0,0,0, 0,0,0,0,}, // 3
  {0,0,0,0,  0,0,0,0,  0,0,0,0, 0,0,0,0,}, // 4
  {0,0,0,0,  0,0,0,0,  0,0,0,0, 0,0,0,0,}, // 5
  {0,0,0,0,  0,0,0,0,  0,0,0,0, 0,0,0,0,}, // 6
  {0,0,0,0,  0,0,0,0,  0,0,0,0, 0,0,0,0,}, // 7
  {0,0,0,0,  0,0,0,0,  0,0,0,0, 0,0,0,0,}, // 8
  {0,0,0,0,  0,0,0,0,  0,0,0,0, 0,0,0,0,}, // 9
  {0,0,0,0,  0,0,0,0,  0,0,0,0, 0,0,0,0,}, // 10
  {0,0,0,0,  0,0,0,0,  0,0,0,0, 0,0,0,0,}, // 11
  {0,0,0,0,  0,0,0,0,  0,0,0,0, 0,0,0,0,}, // 12
  {0,0,0,0,  0,0,0,0,  0,0,0,0, 0,0,0,0,}, // 13
  {0,0,0,0,  0,0,0,0,  0,0,0,0, 0,0,0,0,}, // 14
  {0,0,0,0,  0,0,0,0,  0,0,0,0, 0,0,0,0,}, // 15
  {0,0,0,0,  0,0,0,0,  0,0,0,0, 0,0,0,0,}, // 16
};

byte frameG[16] [16] = {
  {0,0,0,0,  0,0,0,0,  0,0,0,0, 0,0,0,0,}, // 1
  {0,0,0,0,  0,0,0,0,  0,0,0,0, 0,0,0,0,}, // 2
  {0,0,0,0,  0,0,0,0,  0,0,0,0, 0,0,0,0,}, // 3
  {0,0,0,0,  0,0,0,0,  0,0,0,0, 0,0,0,0,}, // 4
  {0,0,0,0,  0,0,0,0,  0,0,0,0, 0,0,0,0,}, // 5
  {0,0,0,0,  0,0,0,0,  0,0,0,0, 0,0,0,0,}, // 6
  {0,0,0,0,  0,0,0,0,  0,0,0,0, 0,0,0,0,}, // 7
  {0,0,0,0,  0,0,0,0,  0,0,0,0, 0,0,0,0,}, // 8
  {0,0,0,0,  0,0,0,0,  0,0,0,0, 0,0,0,0,}, // 9
  {0,0,0,0,  0,0,0,0,  0,0,0,0, 0,0,0,0,}, // 10
  {0,0,0,0,  0,0,0,0,  0,0,0,0, 0,0,0,0,}, // 11
  {0,0,0,0,  0,0,0,0,  0,0,0,0, 0,0,0,0,}, // 12
  {0,0,0,0,  0,0,0,0,  0,0,0,0, 0,0,0,0,}, // 13
  {0,0,0,0,  0,0,0,0,  0,0,0,0, 0,0,0,0,}, // 14
  {0,0,0,0,  0,0,0,0,  0,0,0,0, 0,0,0,0,}, // 15
  {0,0,0,0,  0,0,0,0,  0,0,0,0, 0,0,0,0,}, // 16
};

byte frameB[16] [16] = {
  {0,0,0,0,  0,0,0,0,  0,0,0,0, 0,0,0,0,}, // 1
  {0,0,0,0,  0,0,0,0,  0,0,0,0, 0,0,0,0,}, // 2
  {0,0,0,0,  0,0,0,0,  0,0,0,0, 0,0,0,0,}, // 3
  {0,0,0,0,  0,0,0,0,  0,0,0,0, 0,0,0,0,}, // 4
  {0,0,0,0,  0,0,0,0,  0,0,0,0, 0,0,0,0,}, // 5
  {0,0,0,0,  0,0,0,0,  0,0,0,0, 0,0,0,0,}, // 6
  {0,0,0,0,  0,0,0,0,  0,0,0,0, 0,0,0,0,}, // 7
  {0,0,0,0,  0,0,0,0,  0,0,0,0, 0,0,0,0,}, // 8
  {0,0,0,0,  0,0,0,0,  0,0,0,0, 0,0,0,0,}, // 9
  {0,0,0,0,  0,0,0,0,  0,0,0,0, 0,0,0,0,}, // 10
  {0,0,0,0,  0,0,0,0,  0,0,0,0, 0,0,0,0,}, // 11
  {0,0,0,0,  0,0,0,0,  0,0,0,0, 0,0,0,0,}, // 12
  {0,0,0,0,  0,0,0,0,  0,0,0,0, 0,0,0,0,}, // 13
  {0,0,0,0,  0,0,0,0,  0,0,0,0, 0,0,0,0,}, // 14
  {0,0,0,0,  0,0,0,0,  0,0,0,0, 0,0,0,0,}, // 15
  {0,0,0,0,  0,0,0,0,  0,0,0,0, 0,0,0,0,}, // 16
};

// frame faccina 0 energica
byte frame0[16] [16] = {
  {0,0,0,0,  0,0,0,0,  0,0,0,0, 0,0,0,0,}, // 1
  {0,0,0,0,  0,1,0,0,  0,0,0,1, 0,0,0,0,}, // 2
  {0,0,0,0,  1,0,0,0,  0,0,1,0, 0,0,0,0,}, // 3
  {0,0,0,1,  0,0,0,0,  0,1,0,0, 0,0,0,0,}, // 4
  {0,0,0,1,  1,1,1,0,  0,1,1,1, 1,0,0,0,}, // 5
  {0,0,0,0,  0,0,1,0,  0,0,0,0, 1,0,0,0,}, // 6
  {0,0,0,0,  0,1,0,0,  0,0,0,1, 0,0,0,0,}, // 7
  {0,0,0,0,  1,0,0,0,  0,0,1,0, 0,0,0,0,}, // 8
  {0,0,0,0,  0,0,0,0,  0,0,0,0, 0,0,0,0,}, // 9
  {0,0,0,0,  0,0,0,0,  0,0,0,0, 0,0,0,0,}, // 10
  {0,0,1,0,  0,0,0,0,  0,0,0,0, 0,1,0,0,}, // 11
  {0,0,1,0,  0,0,0,0,  0,0,0,0, 0,1,0,0,}, // 12
  {0,0,1,1,  1,0,0,0,  0,0,0,1, 1,1,0,0,}, // 13
  {0,0,0,0,  1,1,1,1,  1,1,1,1, 0,0,0,0,}, // 14
  {0,0,0,0,  0,0,0,0,  0,0,0,0, 0,0,0,0,}, // 15
  {0,0,0,0,  0,0,0,0,  0,0,0,0, 0,0,0,0,}, // 16
};

// frame faccina 1 felice
byte frame1[16] [16] = {
  {0,0,0,0,  0,0,0,0,  0,0,0,0, 0,0,0,0,}, // 1
  {0,0,0,0,  0,0,0,0,  0,0,0,0, 0,0,0,0,}, // 2
  {0,0,0,1,  1,1,0,0,  0,0,1,1, 1,0,0,0,}, // 3
  {0,0,0,1,  1,1,0,0,  0,0,1,1, 1,0,0,0,}, // 4
  {0,0,0,1,  1,1,0,0,  0,0,1,1, 1,0,0,0,}, // 5
  {0,0,0,1,  1,1,0,0,  0,0,1,1, 1,0,0,0,}, // 6
  {0,0,0,0,  0,0,0,0,  0,0,0,0, 0,0,0,0,}, // 7
  {0,0,1,1,  0,0,0,0,  0,0,0,0, 1,1,0,0,}, // 8
  {0,0,0,1,  1,0,0,0,  0,0,0,1, 1,0,0,0,}, // 9 
  {0,0,0,0,  0,0,0,0,  0,0,0,0, 0,0,0,0,}, // 10
  {0,0,1,0,  0,0,0,0,  0,0,0,0, 0,1,0,0,}, // 11
  {0,0,1,0,  0,0,0,0,  0,0,0,0, 0,1,0,0,}, // 12
  {0,0,1,1,  1,0,0,0,  0,0,0,1, 1,1,0,0,}, // 13
  {0,0,0,0,  1,1,1,1,  1,1,1,1, 0,0,0,0,}, // 14
  {0,0,0,0,  0,0,0,0,  0,0,0,0, 0,0,0,0,}, // 15
  {0,0,0,0,  0,0,0,0,  0,0,0,0, 0,0,0,0,}, // 16
};

// frame faccina 2 apatica
byte frame2[16] [16] = {
  {0,0,0,0,  0,0,0,0,  0,0,0,0, 0,0,0,0,}, // 1
  {0,0,0,0,  0,0,0,0,  0,0,0,0, 0,0,0,0,}, // 2
  {0,0,0,0,  0,0,0,0,  0,0,0,0, 0,0,0,0,}, // 3
  {0,0,0,0,  0,0,0,0,  0,0,0,0, 0,0,0,0,}, // 4
  {0,0,1,1,  1,1,0,0,  0,0,1,1, 1,1,0,0,}, // 5
  {0,0,1,1,  1,1,0,0,  0,0,1,1, 1,1,0,0,}, // 6
  {0,0,0,0,  0,0,0,0,  0,0,0,0, 0,0,0,0,}, // 7
  {0,0,0,0,  0,0,0,0,  0,0,0,0, 0,0,0,0,}, // 8
  {0,0,0,0,  0,0,0,0,  0,0,0,0, 0,0,0,0,}, // 9
  {0,0,0,0,  0,0,0,0,  0,0,0,0, 0,0,0,0,}, // 10
  {0,0,0,0,  0,0,0,0,  0,0,0,0, 0,0,0,0,}, // 11
  {0,0,0,1,  1,1,1,1,  1,1,1,1, 1,0,0,0,}, // 12
  {0,0,0,0,  0,0,0,0,  0,0,0,0, 0,0,0,0,}, // 13
  {0,0,0,0,  0,0,0,0,  0,0,0,0, 0,0,0,0,}, // 14
  {0,0,0,0,  0,0,0,0,  0,0,0,0, 0,0,0,0,}, // 15
  {0,0,0,0,  0,0,0,0,  0,0,0,0, 0,0,0,0,}, // 16
};

// frame faccina 3 ansiosa
byte frame3[16] [16] = {
  {0,0,0,0,  0,0,0,0,  0,0,0,0, 0,0,0,0,}, // 1
  {0,0,0,0,  0,0,0,0,  0,0,0,0, 0,0,1,0,}, // 2
  {0,0,0,0,  0,0,0,0,  0,0,0,0, 0,0,1,0,}, // 3
  {0,1,1,1,  1,0,0,0,  0,1,1,1, 1,0,0,0,}, // 4
  {0,1,1,1,  1,0,0,0,  0,1,1,1, 1,0,0,0,}, // 5
  {0,1,1,1,  1,0,0,0,  0,1,1,1, 1,0,0,0,}, // 6
  {0,0,0,0,  0,0,0,0,  0,0,0,0, 0,0,0,0,}, // 7
  {0,0,0,0,  0,0,0,0,  0,0,0,0, 0,0,0,0,}, // 8
  {0,0,0,0,  0,0,0,0,  0,0,0,0, 0,0,0,0,}, // 9
  {0,0,0,0,  1,0,0,0,  1,1,0,0, 0,0,0,0,}, // 10
  {0,0,0,1,  0,1,0,0,  1,1,0,1, 0,0,1,0,}, // 11
  {0,0,1,0,  0,1,0,1,  0,1,1,0, 1,0,1,0,}, // 12
  {0,0,0,0,  0,1,0,1,  0,0,0,0, 1,0,1,0,}, // 13
  {0,0,0,0,  0,1,1,0,  0,0,0,0, 0,1,0,0,}, // 14
  {0,0,0,0,  0,0,0,0,  0,0,0,0, 0,0,0,0,}, // 15
  {0,0,0,0,  0,0,0,0,  0,0,0,0, 0,0,0,0,}, // 16
};

// frame faccina 4 triste
byte frame4[16] [16] = {
  {0,0,0,0,  0,0,0,0,  0,0,0,0, 0,0,0,0,}, // 1
  {0,0,0,0,  0,0,0,0,  0,0,0,0, 0,0,0,0,}, // 2
  {0,0,0,0,  0,0,0,0,  0,0,0,0, 0,0,0,0,}, // 3
  {0,0,0,0,  0,0,0,0,  0,0,0,0, 0,0,0,0,}, // 4
  {0,0,1,1,  1,1,0,0,  0,0,1,1, 1,1,0,0,}, // 5
  {0,0,1,1,  1,1,0,0,  0,0,1,1, 1,1,0,0,}, // 6
  {0,0,0,0,  0,1,0,0,  0,0,1,0, 0,0,0,0,}, // 7
  {0,0,0,0,  1,0,0,0,  0,0,0,1, 0,0,0,0,}, // 8
  {0,0,0,1,  0,0,0,0,  0,0,0,0, 1,0,0,0,}, // 9
  {0,0,0,0,  0,0,0,0,  0,0,0,0, 0,0,0,0,}, // 10
  {0,0,0,0,  1,1,1,1,  1,1,1,1, 0,0,0,0,}, // 11
  {0,0,1,1,  1,0,0,0,  0,0,0,1, 1,1,0,0,}, // 12
  {0,0,1,0,  0,0,0,0,  0,0,0,0, 0,1,0,0,}, // 13
  {0,0,1,0,  0,0,0,0,  0,0,0,0, 0,1,0,0,}, // 14
  {0,0,0,0,  0,0,0,0,  0,0,0,0, 0,0,0,0,}, // 15
  {0,0,0,0,  0,0,0,0,  0,0,0,0, 0,0,0,0,}, // 16
};

// frame faccina 5 arrabiata
byte frame5[16] [16] = {
  {0,0,0,0,  0,0,0,0,  0,0,0,0, 0,0,0,0,}, // 1
  {0,0,0,0,  0,0,0,0,  0,0,0,0, 0,0,0,0,}, // 2
  {0,0,0,0,  0,0,0,0,  0,0,0,0, 0,0,0,0,}, // 3
  {0,0,1,0,  0,0,0,0,  0,0,0,0, 0,1,0,0,}, // 4
  {0,0,1,1,  0,0,0,0,  0,0,0,1, 1,1,0,0,}, // 5
  {0,0,0,1,  1,1,0,0,  0,0,1,1, 1,0,0,0,}, // 6
  {0,0,0,0,  0,1,0,0,  0,0,1,0, 0,0,0,0,}, // 7
  {0,0,0,0,  0,0,0,0,  0,0,0,0, 0,0,0,0,}, // 8
  {0,0,0,0,  0,0,0,0,  0,0,0,0, 0,0,0,0,}, // 9
  {0,0,0,1,  1,1,1,1,  1,1,1,1, 1,0,0,0,}, // 10
  {0,0,1,1,  0,0,0,0,  0,0,0,0, 1,1,0,0,}, // 11
  {0,0,1,0,  0,0,0,0,  0,0,0,0, 0,1,0,0,}, // 12
  {0,0,0,0,  0,0,0,0,  0,0,0,0, 0,0,0,0,}, // 13
  {0,0,0,0,  0,0,0,0,  0,0,0,0, 0,0,0,0,}, // 14
  {0,0,0,0,  0,0,0,0,  0,0,0,0, 0,0,0,0,}, // 15
  {0,0,0,0,  0,0,0,0,  0,0,0,0, 0,0,0,0,}, // 16
};

int mer = 0;
int face = 3;
int change = 0;

int state_buttom_ora;
int state_buttom_0;
int state_buttom_1;
int state_buttom_2;
int state_buttom_3;
int state_buttom_4;
int state_buttom_5;
int buf = 0;
int at;
int ct;

int vr = 111;  // colore viola
int vg = 0;
int vb = 255;

int soglia = 0;
long somma = 0;
int media;
long num = 0;


void setup() {
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(2);

  pinMode(pin_buttom_ora, INPUT);
  
  // Open serial communications and wait for port to open:
  Wire.begin();
  Serial.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only

  }
  
  // check for the WiFi module:
  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed!");
    // don't continue
    while (true);
  }

  String fv = WiFi.firmwareVersion();
  if (fv < WIFI_FIRMWARE_LATEST_VERSION) {
    Serial.println("Please upgrade the firmware");
  }

  // attempt to connect to WiFi network:
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);

    calibra();
    Serial.print("soglia: ");
    Serial.println(soglia);

    // wait 10 seconds for connection:
    delay(10000);
  }

  Serial.println("Connected to WiFi");
  printWifiStatus();

  Serial.println("\nStarting connection to server...");
  Udp.begin(localPort);

  leds[0] = CRGB(0,255,0);
  leds[15] = CRGB(255,0,0);
  FastLED.show();
  delay(5000);
  leds[0] = CRGB(0,0,0);
  leds[15] = CRGB(0,0,0);
  FastLED.show();
}

void loop() {
  
  sendNTPpacket(timeServer); // send an NTP packet to a time server
  // wait to see if a reply is available

  if (Udp.parsePacket()) {

    Wire.requestFrom(3,8);
	  Serial.print("Lo slave ha scritto:  ");
	  if(Wire.available()) {
		  change = Wire.read();
		  Serial.print(change);
	  }
	  Serial.println();


    state_buttom_ora = digitalRead(pin_buttom_ora);

    state_buttom_0 = digitalRead(pin_buttom_0);
    state_buttom_1 = digitalRead(pin_buttom_1);
    state_buttom_2 = digitalRead(pin_buttom_2);
    state_buttom_3 = digitalRead(pin_buttom_3);
    state_buttom_4 = digitalRead(pin_buttom_4);
    state_buttom_5 = digitalRead(pin_buttom_5);

    int n = analogRead(A0);

    int lum1 = map(analogRead(pin_aut_lum),0,1023,5,40) + map(analogRead(pin_pot_lum),0,1023,0,50);
    int lum2 = (lum1 - (lum1 % 3));
    FastLED.setBrightness(lum2);

    while(state_buttom_ora == 1) {
      change = 1;
      state_buttom_ora = digitalRead(pin_buttom_ora);
    }

    // faccina energica, colore: arancione
    if(state_buttom_0 == 1) {
      face = 0;
      vr = 255;
      vg = 50;
      vb = 0;
    }

    // faccina felice, colore: giallo
    if(state_buttom_1 == 1) {
      face = 1;
      vr = 255;
      vg = 100;
      vb = 0;
    }

    // faccina apatica, colore: verde
    if(state_buttom_2 == 1) {
      face = 2;
      vr = 0;
      vg = 255;
      vb = 0;
    }

    // facciana ansiosa, colore: viola
    if(state_buttom_3 == 1) {
      face = 3;
      vr = 111;
      vg = 0;
      vb = 255;
    }

    // faccina triste, colore: blu
    if(state_buttom_4 == 1) {
      face = 4;
      vr = 25;
      vg = 25;
      vb = 255;

    }

    // faccina arrabiata, colore: rosso
    if(state_buttom_5 == 1) {
      face = 5;
      vr = 255;
      vg = 0;
      vb = 0;
    }

    if(n > soglia) {
      change = 1;
    }

    Serial.print("change: ");
    Serial.print(change);
    Serial.print(" n: ");
    Serial.print(n);
    Serial.print(" sogla: ");
    Serial.print(soglia);

    somma = somma + n;
    num++;
    if(num > 500000) {
      Serial.println();
      Serial.println("ricalcolo soglia...");
      Serial.println(millis());
      delay(5000);
      media = somma/num;
      somma = 0;
      num = 0;
      soglia = (int)((float)media * 1.2f); 
    }

    Serial.print(" num: ");
    Serial.print(num);
    Serial.print(" somma: ");
    Serial.println(somma);

    //Serial.println(face);
    // We've received a packet, read the data from it
    Udp.read(packetBuffer, NTP_PACKET_SIZE); // read the packet into the buffer
    //the timestamp starts at byte 40 of the received packet and is four bytes,
    // or two words, long. First, extract the two words:
    unsigned long highWord = word(packetBuffer[40], packetBuffer[41]);
    unsigned long lowWord = word(packetBuffer[42], packetBuffer[43]);
    // combine the four bytes (two words) into a long integer
    // this is NTP time (seconds since Jan 1 1900):
    unsigned long secsSince1900 = highWord << 16 | lowWord;
    // now convert NTP time into everyday time:
    // Unix time starts on Jan 1 1970. In seconds, that's 2208988800:
    const unsigned long seventyYears = 2208988800UL;
    // subtract seventy years:
    unsigned long epoch = secsSince1900 - seventyYears;

    int a = ((epoch  % 86400L) / 3600)+2;
    int at = a + 100;
    int c = (epoch  % 3600) / 60;
    int ct = c + 200;

    int A = a%10;
    int B = (a/10)%10;
    int C = c%10;
    int D = (c/10)%10;

    if(change == 1) {
      
      clearMatrix();
      clearFrame();
      digit(B, 2, 1);  // seconda cifra ora
      digit(A, 9, 1);  // prima cifra ora
      digit(D, 2, 10); // seconda cifra minuti
      digit(C, 9, 10); // prima cifra minuti
      digit(10, 4, 7); // punto 1
      digit(10, 9, 7); // punto 2
      con(vr,vg,vb);
      com(); 
      FastLED.show();

      //trasmissine con l'atmega328p dell'ora e dei minuti
      Wire.beginTransmission(3);
      Wire.write(at);
      Serial.print("at:   ");
      Serial.print(at);
      Serial.print("   ");
      Wire.endTransmission();

      delay(10);

      Wire.beginTransmission(3);
      Wire.write(ct);
      Serial.print("ct:   ");
      Serial.print(ct);
      Serial.println("   ");
      Wire.endTransmission();

      delay(5000);
      change = 0;
    }

    if( change == 0) {
      clearMatrix();
      clearFrame();
      faccina();
      con(vr,vg,vb);
      com(); 
      FastLED.show();
    }
  }  

  // wait ten seconds before asking for the time again
  //delay(1000);
}

// send an NTP request to the time server at the given address
unsigned long sendNTPpacket(IPAddress& address) {
  //Serial.println("1");
  // set all bytes in the buffer to 0
  memset(packetBuffer, 0, NTP_PACKET_SIZE);
  // Initialize values needed to form NTP request
  // (see URL above for details on the packets)
  //Serial.println("2");
  packetBuffer[0] = 0b11100011;   // LI, Version, Mode
  packetBuffer[1] = 0;     // Stratum, or type of clock
  packetBuffer[2] = 6;     // Polling Interval
  packetBuffer[3] = 0xEC;  // Peer Clock Precision
  // 8 bytes of zero for Root Delay & Root Dispersion
  packetBuffer[12]  = 49;
  packetBuffer[13]  = 0x4E;
  packetBuffer[14]  = 49;
  packetBuffer[15]  = 52;

  //Serial.println("3");

  // all NTP fields have been given values, now
  // you can send a packet requesting a timestamp:
  Udp.beginPacket(address, 123); //NTP requests are to port 123
  //Serial.println("4");
  Udp.write(packetBuffer, NTP_PACKET_SIZE);
  //Serial.println("5");
  Udp.endPacket();
  //Serial.println("6");
}


void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your board's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}

void clearMatrix() {
  for(int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB(0,0,0);
  }
}

void clearFrame() {
  for (int iar = 0; iar < 16; iar++) {
    for (int jar = 0; jar < 16; jar++) {
      frame[iar][jar] = 0;
    }
  }
}

void con(int Rab, int Gab, int Bab) {
  for(int dab = 0; dab < 16; dab++) {
    for(int eab = 0; eab < 16; eab++) {
      frameR[dab][eab] = frame[dab][eab] * Rab;
      frameG[dab][eab] = frame[dab][eab] * Gab;
      frameB[dab][eab] = frame[dab][eab] * Bab;
    }
  }
}

void com() {
  for (int aer = 0; aer < 16; aer++) {
    for (int ber = 0; ber < 16; ber++) {
      switch(aer) {
        case 0:
          mer = 15 - ber;
          break;
        case 1:
          mer = 16 + ber;
          break;
        case 2:
          mer = 47 - ber;
          break;
        case 3:
          mer = 48 + ber;
          break;
        case 4:
          mer = 79 - ber;
          break;
        case 5:
          mer = 80 + ber;
          break;
        case 6:
          mer = 111 - ber;
          break;
        case 7:
          mer = 112 + ber;
          break;
        case 8:
          mer = 143 - ber;
          break;
        case 9:
          mer = 144 + ber;
          break;
        case 10:
          mer = 175 - ber;
          break;
        case 11:
          mer = 176 + ber;
          break;
        case 12:
          mer = 207 - ber;
          break;
        case 13:
          mer = 208 + ber;
          break;
        case 14:
          mer = 239 - ber;
          break;
        case 15:
          mer = 240 + ber;
          break;
      }
      if(frame[aer][ber] == 1) {
      leds[mer] = CRGB(frameR[aer][ber],frameG[aer][ber],frameB[aer][ber]);
      }
    }
  }
}

void faccina() {
  for(int i = 0; i < 16; i++) {
    for(int j = 0; j < 16; j++) {
      switch(face) {
        case 0:
          frame[i][j] = frame0[i][j];
          break;
        case 1:
          frame[i][j] = frame1[i][j];
          break;
        case 2:
          frame[i][j] = frame2[i][j];
          break;
        case 3:
          frame[i][j] = frame3[i][j];
          break;
        case 4:
          frame[i][j] = frame4[i][j];
          break;
        case 5:
          frame[i][j] = frame5[i][j];
          break;
      }
    }
  }
}

void digit(int nch, int offx, int offy) {
  switch (nch) {
    case 0:
      frame[offy+0][offx+0] = 1;
      frame[offy+0][offx+1] = 1;
      frame[offy+0][offx+2] = 1;
      frame[offy+0][offx+3] = 1;
      frame[offy+0][offx+4] = 1;

      frame[offy+1][offx+0] = 1;
      frame[offy+1][offx+1] = 0;
      frame[offy+1][offx+2] = 0;
      frame[offy+1][offx+3] = 0;
      frame[offy+1][offx+4] = 1;

      frame[offy+2][offx+0] = 1;
      frame[offy+2][offx+1] = 0;
      frame[offy+2][offx+2] = 0;
      frame[offy+2][offx+3] = 0;
      frame[offy+2][offx+4] = 1;

      frame[offy+3][offx+0] = 1;
      frame[offy+3][offx+1] = 0;
      frame[offy+3][offx+2] = 0;
      frame[offy+3][offx+3] = 0;
      frame[offy+3][offx+4] = 1;

      frame[offy+4][offx+0] = 1;
      frame[offy+4][offx+1] = 1;
      frame[offy+4][offx+2] = 1;
      frame[offy+4][offx+3] = 1;
      frame[offy+4][offx+4] = 1;
      break;
    
    case 1:
      frame[offy+0][offx+0] = 0;
      frame[offy+0][offx+1] = 0;
      frame[offy+0][offx+2] = 1;
      frame[offy+0][offx+3] = 0;
      frame[offy+0][offx+4] = 0;

      frame[offy+1][offx+0] = 0;
      frame[offy+1][offx+1] = 1;
      frame[offy+1][offx+2] = 1;
      frame[offy+1][offx+3] = 0;
      frame[offy+1][offx+4] = 0;

      frame[offy+2][offx+0] = 0;
      frame[offy+2][offx+1] = 0;
      frame[offy+2][offx+2] = 1;
      frame[offy+2][offx+3] = 0;
      frame[offy+2][offx+4] = 0;

      frame[offy+3][offx+0] = 0;
      frame[offy+3][offx+1] = 0;
      frame[offy+3][offx+2] = 1;
      frame[offy+3][offx+3] = 0;
      frame[offy+3][offx+4] = 0;

      frame[offy+4][offx+0] = 1;
      frame[offy+4][offx+1] = 1;
      frame[offy+4][offx+2] = 1;
      frame[offy+4][offx+3] = 1;
      frame[offy+4][offx+4] = 1;
      break;

    case 2:
      frame[offy+0][offx+0] = 1;
      frame[offy+0][offx+1] = 1;
      frame[offy+0][offx+2] = 1;
      frame[offy+0][offx+3] = 1;
      frame[offy+0][offx+4] = 1;

      frame[offy+1][offx+0] = 0;
      frame[offy+1][offx+1] = 0;
      frame[offy+1][offx+2] = 0;
      frame[offy+1][offx+3] = 0;
      frame[offy+1][offx+4] = 1;

      frame[offy+2][offx+0] = 1;
      frame[offy+2][offx+1] = 1;
      frame[offy+2][offx+2] = 1;
      frame[offy+2][offx+3] = 1;
      frame[offy+2][offx+4] = 1;

      frame[offy+3][offx+0] = 1;
      frame[offy+3][offx+1] = 0;
      frame[offy+3][offx+2] = 0;
      frame[offy+3][offx+3] = 0;
      frame[offy+3][offx+4] = 0;

      frame[offy+4][offx+0] = 1;
      frame[offy+4][offx+1] = 1;
      frame[offy+4][offx+2] = 1;
      frame[offy+4][offx+3] = 1;
      frame[offy+4][offx+4] = 1;
      break;
    
    case 3:
      frame[offy+0][offx+0] = 1;
      frame[offy+0][offx+1] = 1;
      frame[offy+0][offx+2] = 1;
      frame[offy+0][offx+3] = 1;
      frame[offy+0][offx+4] = 1;

      frame[offy+1][offx+0] = 0;
      frame[offy+1][offx+1] = 0;
      frame[offy+1][offx+2] = 0;
      frame[offy+1][offx+3] = 0;
      frame[offy+1][offx+4] = 1;

      frame[offy+2][offx+0] = 0;
      frame[offy+2][offx+1] = 1;
      frame[offy+2][offx+2] = 1;
      frame[offy+2][offx+3] = 1;
      frame[offy+2][offx+4] = 1;

      frame[offy+3][offx+0] = 0;
      frame[offy+3][offx+1] = 0;
      frame[offy+3][offx+2] = 0;
      frame[offy+3][offx+3] = 0;
      frame[offy+3][offx+4] = 1;

      frame[offy+4][offx+0] = 1;
      frame[offy+4][offx+1] = 1;
      frame[offy+4][offx+2] = 1;
      frame[offy+4][offx+3] = 1;
      frame[offy+4][offx+4] = 1;
      break;
    
    case 4:
      frame[offy+0][offx+0] = 1;
      frame[offy+0][offx+1] = 0;
      frame[offy+0][offx+2] = 0;
      frame[offy+0][offx+3] = 0;
      frame[offy+0][offx+4] = 1;

      frame[offy+1][offx+0] = 1;
      frame[offy+1][offx+1] = 0;
      frame[offy+1][offx+2] = 0;
      frame[offy+1][offx+3] = 0;
      frame[offy+1][offx+4] = 1;

      frame[offy+2][offx+0] = 1;
      frame[offy+2][offx+1] = 1;
      frame[offy+2][offx+2] = 1;
      frame[offy+2][offx+3] = 1;
      frame[offy+2][offx+4] = 1;

      frame[offy+3][offx+0] = 0;
      frame[offy+3][offx+1] = 0;
      frame[offy+3][offx+2] = 0;
      frame[offy+3][offx+3] = 0;
      frame[offy+3][offx+4] = 1;

      frame[offy+4][offx+0] = 0;
      frame[offy+4][offx+1] = 0;
      frame[offy+4][offx+2] = 0;
      frame[offy+4][offx+3] = 0;
      frame[offy+4][offx+4] = 1;
      break;
    
    case 5:
      frame[offy+0][offx+0] = 1;
      frame[offy+0][offx+1] = 1;
      frame[offy+0][offx+2] = 1;
      frame[offy+0][offx+3] = 1;
      frame[offy+0][offx+4] = 1;

      frame[offy+1][offx+0] = 1;
      frame[offy+1][offx+1] = 0;
      frame[offy+1][offx+2] = 0;
      frame[offy+1][offx+3] = 0;
      frame[offy+1][offx+4] = 0;

      frame[offy+2][offx+0] = 1;
      frame[offy+2][offx+1] = 1;
      frame[offy+2][offx+2] = 1;
      frame[offy+2][offx+3] = 1;
      frame[offy+2][offx+4] = 1;

      frame[offy+3][offx+0] = 0;
      frame[offy+3][offx+1] = 0;
      frame[offy+3][offx+2] = 0;
      frame[offy+3][offx+3] = 0;
      frame[offy+3][offx+4] = 1;

      frame[offy+4][offx+0] = 1;
      frame[offy+4][offx+1] = 1;
      frame[offy+4][offx+2] = 1;
      frame[offy+4][offx+3] = 1;
      frame[offy+4][offx+4] = 1;
      break;
    
    case 6:
      frame[offy+0][offx+0] = 1;
      frame[offy+0][offx+1] = 1;
      frame[offy+0][offx+2] = 1;
      frame[offy+0][offx+3] = 1;
      frame[offy+0][offx+4] = 1;

      frame[offy+1][offx+0] = 1;
      frame[offy+1][offx+1] = 0;
      frame[offy+1][offx+2] = 0;
      frame[offy+1][offx+3] = 0;
      frame[offy+1][offx+4] = 0;

      frame[offy+2][offx+0] = 1;
      frame[offy+2][offx+1] = 1;
      frame[offy+2][offx+2] = 1;
      frame[offy+2][offx+3] = 1;
      frame[offy+2][offx+4] = 1;

      frame[offy+3][offx+0] = 1;
      frame[offy+3][offx+1] = 0;
      frame[offy+3][offx+2] = 0;
      frame[offy+3][offx+3] = 0;
      frame[offy+3][offx+4] = 1;

      frame[offy+4][offx+0] = 1;
      frame[offy+4][offx+1] = 1;
      frame[offy+4][offx+2] = 1;
      frame[offy+4][offx+3] = 1;
      frame[offy+4][offx+4] = 1;
      break;
    
    case 7:
      frame[offy+0][offx+0] = 1;
      frame[offy+0][offx+1] = 1;
      frame[offy+0][offx+2] = 1;
      frame[offy+0][offx+3] = 1;
      frame[offy+0][offx+4] = 1;

      frame[offy+1][offx+0] = 1;
      frame[offy+1][offx+1] = 0;
      frame[offy+1][offx+2] = 0;
      frame[offy+1][offx+3] = 0;
      frame[offy+1][offx+4] = 1;

      frame[offy+2][offx+0] = 1;
      frame[offy+2][offx+1] = 0;
      frame[offy+2][offx+2] = 0;
      frame[offy+2][offx+3] = 0;
      frame[offy+2][offx+4] = 1;

      frame[offy+3][offx+0] = 0;
      frame[offy+3][offx+1] = 0;
      frame[offy+3][offx+2] = 0;
      frame[offy+3][offx+3] = 0;
      frame[offy+3][offx+4] = 1;

      frame[offy+4][offx+0] = 0;
      frame[offy+4][offx+1] = 0;
      frame[offy+4][offx+2] = 0;
      frame[offy+4][offx+3] = 0;
      frame[offy+4][offx+4] = 1;
      break;
    
    case 8:
      frame[offy+0][offx+0] = 1;
      frame[offy+0][offx+1] = 1;
      frame[offy+0][offx+2] = 1;
      frame[offy+0][offx+3] = 1;
      frame[offy+0][offx+4] = 1;

      frame[offy+1][offx+0] = 1;
      frame[offy+1][offx+1] = 0;
      frame[offy+1][offx+2] = 0;
      frame[offy+1][offx+3] = 0;
      frame[offy+1][offx+4] = 1;

      frame[offy+2][offx+0] = 0;
      frame[offy+2][offx+1] = 1;
      frame[offy+2][offx+2] = 1;
      frame[offy+2][offx+3] = 1;
      frame[offy+2][offx+4] = 0;

      frame[offy+3][offx+0] = 1;
      frame[offy+3][offx+1] = 0;
      frame[offy+3][offx+2] = 0;
      frame[offy+3][offx+3] = 0;
      frame[offy+3][offx+4] = 1;

      frame[offy+4][offx+0] = 1;
      frame[offy+4][offx+1] = 1;
      frame[offy+4][offx+2] = 1;
      frame[offy+4][offx+3] = 1;
      frame[offy+4][offx+4] = 1;
      break;

    case 9:
      frame[offy+0][offx+0] = 1;
      frame[offy+0][offx+1] = 1;
      frame[offy+0][offx+2] = 1;
      frame[offy+0][offx+3] = 1;
      frame[offy+0][offx+4] = 1;

      frame[offy+1][offx+0] = 1;
      frame[offy+1][offx+1] = 0;
      frame[offy+1][offx+2] = 0;
      frame[offy+1][offx+3] = 0;
      frame[offy+1][offx+4] = 1;

      frame[offy+2][offx+0] = 1;
      frame[offy+2][offx+1] = 1;
      frame[offy+2][offx+2] = 1;
      frame[offy+2][offx+3] = 1;
      frame[offy+2][offx+4] = 1;

      frame[offy+3][offx+0] = 0;
      frame[offy+3][offx+1] = 0;
      frame[offy+3][offx+2] = 0;
      frame[offy+3][offx+3] = 0;
      frame[offy+3][offx+4] = 1;

      frame[offy+4][offx+0] = 1;
      frame[offy+4][offx+1] = 1;
      frame[offy+4][offx+2] = 1;
      frame[offy+4][offx+3] = 1;
      frame[offy+4][offx+4] = 1;
      break;

    case 10:
      frame[offy+0][offx+0] = 1;
      frame[offy+0][offx+1] = 1;
      frame[offy+0][offx+2] = 1;

      frame[offy+1][offx+0] = 1;
      frame[offy+1][offx+1] = 1;
      frame[offy+1][offx+2] = 1;
      break;
  }
}


void calibra() {
  for (int i = 0; i < 100; i++) {
    soglia += analogRead(A0);  
    delay(50);
  }  
  soglia = soglia/100;
  soglia = (int)((float)soglia * 1.3f);
}