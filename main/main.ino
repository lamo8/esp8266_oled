#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include <ESP8266WiFi.h>        // Include the Wi-Fi library
#include <ESP8266WiFiMulti.h>   // Include the Wi-Fi-Multi library
#include <ESP8266HTTPClient.h>
ESP8266WiFiMulti wifiMulti;     // Create an instance of the ESP8266WiFiMulti class, called 'wifiMulti'


#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

#define DEBUG true


 
void setup() {

  if( DEBUG ){
    Serial.begin(9600);
  }

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }

  display.clearDisplay();
  

  WiFiconnect(); // Подключаемся к WiFi
  
  /*
     delay(2000);
  display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    //display.setCursor(0, 10);
    display.setCursor(0, 0);
    // Display static text
    display.println("Hello, world!");
    display.println("osgnjosa gfsdf");
    display.println("sdfs234");
    display.println("dkgpojdot");
    display.println("123412313");
    display.display();
  */
}

void loop() {

  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.clearDisplay();

  if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status
   
    HTTPClient http;  //Declare an object of class HTTPClient
   
    http.begin("http://vds.lamo8.ru/");  //Specify request destination
    int httpCode = http.GET();                                                                  //Send the request
   
    if (httpCode > 0) { //Check the returning code
   
      String payload = http.getString();   //Get the request response payload
      Serial.println(payload);                     //Print the response payload

      display.print(payload);
      display.print(WiFi.localIP());
      display.display();
   }
   
    http.end();   //Close connection
   
  }
  else {
     display.setTextSize(2);
     display.print("Error get page!!!");
     display.display();
  }
   
  delay(3000);    //Send a request every 30 seconds





  /*
  display.setTextSize(5);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  long i;
  while(i < 100000){
     display.setCursor(0, 0);
     display.print(i);
     display.display();
     delay(1);
     display.clearDisplay();
     i++;
  }
  display.clearDisplay();
  */
} 

void WiFiconnect(){
  
  wifiMulti.addAP("NEP", "Nep-2013");   // add Wi-Fi networks you want to connect to
  wifiMulti.addAP("lenovo", "1111100000");
  //wifiMulti.addAP("ssid_from_AP_3", "your_password_for_AP_3");

  // Подключаемся к wifi
  if( DEBUG ){
    Serial.println("Connecting WiFi...");
  }
  
  int i = 0;
  while (wifiMulti.run() != WL_CONNECTED) { // Wait for the Wi-Fi to connect: scan for Wi-Fi networks, and connect to the strongest of the networks above
    delay(1000);
    if( DEBUG ){
      Serial.print('.');
    }
  }

  if( DEBUG ){
    Serial.println('\n');
    Serial.print("Connected to ");
    Serial.println(WiFi.SSID());              // Tell us what network we're connected to
    Serial.print("IP address:\t");
    Serial.println(WiFi.localIP());           // Send the IP address of the ESP8266 to the computer
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("WiFi: " + WiFi.SSID());
  display.println(WiFi.localIP());  
  display.display();
  delay(1000);
}
 

/*
 * https://tttapa.github.io/ESP8266/Chap07%20-%20Wi-Fi%20Connections.html
 Access Point mode
To configure the ESP8266 as an access point, to allow other devices like smartphones or laptops to connect to it, you can use the softAP function:
#include <ESP8266WiFi.h>        // Include the Wi-Fi library

const char *ssid = "ESP8266 Access Point"; // The name of the Wi-Fi network that will be created
const char *password = "thereisnospoon";   // The password required to connect to it, leave blank for an open network

void setup() {
  Serial.begin(115200);
  delay(10);
  Serial.println('\n');

  WiFi.softAP(ssid, password);             // Start the access point
  Serial.print("Access Point \"");
  Serial.print(ssid);
  Serial.println("\" started");

  Serial.print("IP address:\t");
  Serial.println(WiFi.softAPIP());         // Send the IP address of the ESP8266 to the computer
}

void loop() { }
 */
