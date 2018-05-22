#include <ESP8266WiFi.h>
#include <Wire.h>
#include <U8g2lib.h>
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

const char* ssid     = "LTYZ-EDU";
const char* password = "ltyz13579";
const char* host = "172.16.20.36";
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

  while (!client.connected()){ //连接TCP服务器
    if (!client.connect(host, port)){
      Serial.println("Connect failed, retrying...");
      client.stop();
      delay(500);
    }
  }
}

unsigned int img[1024];
int i = 0;

void loop() {
  while (client.available()){
    if (i == 1024){
      i = 0;
      break;
    }
    img[i] = client.read();
  }

  u8g2.firstPage();
  do {
    u8g2.drawXBMP(0,0, 128, 64, (uint8_t*)&img);
  } while ( u8g2.nextPage() );

  client.println("n"); //显示完成，请求下一帧
}

