#include <WiFi.h>
#include "Arduino_LED_Matrix.h"
#include <stdint.h>

ArduinoLEDMatrix matrix;

const char* ssid = "WIFINAME";
const char* password = "PASSWORD";

const uint32_t good[][4] = {
    {
        0x10,
        0x80000004,
        0x22041f8,
        66
    }
};
const uint32_t medium[][4] = {
  {
        0x20,
        0x40000000,
        0xf0000000,
        66
    }
};
const uint32_t low[][4] = {
  {
        0x20,
        0x40000f01,
        0x8204000,
        66
    }
};
const uint32_t GG[][4] = {
  {
        0x29410,
        0x82940000,
        0xf030c402,
        66
    }
};

const uint32_t animation1[][4] = {
	{
		0x0,
		0x6006000,
		0x0,
		66
	},
  };

const uint32_t animation2[][4] = {
	{
		0x0,
		0x6606600,
		0x0,
		66
	},
  };

const uint32_t animation3[][4] = {
	{
		0x0,
		0x6666660,
		0x0,
		66
	}
  };

void setup() {
    Serial.begin(115200);
    int i=1;
    WiFi.begin(ssid, password);

    matrix.begin();
    matrix.play(true);

    while (WiFi.status() != WL_CONNECTED) {

        if (i ==1){
          matrix.loadSequence(animation1);
          i+=1;
        }else if (i==2){
          matrix.loadSequence(animation2);
          i+=1;
        }
        else if (i==3){
          matrix.loadSequence(animation3);
          i=1;
        }
        Serial.println("Connecting to WiFi...");
        delay(1000);
    }
    Serial.println("Connected to WiFi");
}

void loop() {
    int32_t rssi = WiFi.RSSI();
  
    Serial.print("WiFi Signal Strength (RSSI): ");
    Serial.print(rssi);
    Serial.println(" dBm");
    if(rssi==0){
        matrix.loadSequence(GG);
    }else if(rssi>=-49){
        matrix.loadSequence(good);
    }else if(rssi>=-57){
        matrix.loadSequence(medium);
    }else if(rssi>=-73){
        matrix.loadSequence(low);
    }
    delay(1000);
}
