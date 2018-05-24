#include <ESP8266WiFi.h>
#include <Wire.h>
#include <U8g2lib.h>
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

const char* ssid     = "your_ssid";
const char* password = "your_password";
const char* host = "your_domain";
const int port = 6666;
WiFiClient client;

void setup() {
  Serial.begin(115200);
  delay(10);
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  while (!client.connected()){ 
    if (!client.connect(host, port)){
      Serial.println("Connect failed, retrying...");
      client.stop();
      delay(500);
    }
  }
  Serial.println("Connected!");
  u8g2.begin();
  delay(500);
  client.println("n");
}

unsigned char img[1024];
int i = 0;

void loop() {
  while (client.available()){
    if (i == 1024){
      i = 0;
      client.println("n"); //ask for next frame
      break;
    }
    img[i] = client.read();
    //Serial.write(img[i]);
    i++;
  }
  

  u8g2.firstPage();
  do {
    u8g2.drawXBMP(0,0, 128, 64, img);
  } while ( u8g2.nextPage() );
  

  
}

