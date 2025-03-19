         ////////////////////////////////////////////////////  
        //     IoT Interactive Gift Card on Localhost     //
       //                                                //
      //          -------------------------             //
     //                ESP-WROOM-32                    //           
    //               by Kutluhan Aktar                // 
   //                                                //
  ////////////////////////////////////////////////////

// In this project, I wanted to create a gift card for new year to share with my friends in code working on their localhost, including three features.
// I used an ESP32 Development Board to create a module updating the gift card's database table because I had it available at the time.
// Of course, you can use any other microcontroller that can make an HTTP GET Request instead of ESP32 Development Board to create the module for this project.
//
// Features:
// Block the gift card using the module.
// Change the color of the christmas tree embroidery by choosing an RGB color pattern on the module.
// Play or pause Jingle Bells song integrated into the gift card via the module.
//
// Inspect and Download Interactive Gift Card:
// https://www.theamplituhedron.com/dashboard/Interactive-Gift-Card/
//
// As localhost, I used XAMPP but you can use any other localhost application with this code.
// Note: Do not forget to create a table on the database before uploading this code to your microcontroller.
//
// You can learn about it more from the link below.
// https://www.theamplituhedron.com/projects/IoT-Interactive-New-Year-Gift-Card-on-Localhost/
//
// Connections
// ESP-WROOM-32 :           
//                                RGB
// 25 ---------------------------
// 26 ---------------------------
// 27 ---------------------------
//
//                                Red_Potentiometer                                
// 32 ---------------------------
//                                Green_Potentiometer                                
// 33 ---------------------------
//                                Blue_Potentiometer                                
// 34 ---------------------------
//                                BLOCK_BUTTON                                
// 13 ---------------------------
//                                AUDIO_BUTTON                                
// 14 ---------------------------

// include WiFi.h and HTTPClient.h libraries to make an HTTP Get Request to the localhost using ESP32.
#include <WiFi.h>
#include <HTTPClient.h>

// Define your WiFi settings.
const char *ssid = "[WiFi_SSID]";
const char *password = "[WiFi_PASSWORD]";

const char *host = "[Local IpV4 IPAdress]"; // e.g., 192.168.1.22, 198.168.1.30 ...

// Define the gift card connection path.
String GIFT_PATH = "http://[Local IpV4 Address]/GiftCard/convey.php";

// Define data holders.
String block = "false";
String audio = "false";
String color;
int R, G, B;

// Define BLOCK, AUDIO, red_pin, green_pin, blue_pin, red_pot, green_pot, and blue_pot pins.
#define red_pin 25
#define green_pin 26 
#define blue_pin 27

int red_pot =  32;
int green_pot =  33;
int  blue_pot =  34;

int BLOCK = 13;
int AUDIO = 14;


void setup(){
  pinMode(BLOCK, INPUT);
  pinMode(AUDIO, INPUT);
  
  // Configure LED PWM functionalitites
  ledcSetup(0, 5000, 8);
  ledcSetup(1, 5000, 8);
  ledcSetup(2, 5000, 8);
  // Attach pins.
  ledcAttachPin(red_pin, 0);
  ledcAttachPin(green_pin, 1);
  ledcAttachPin(blue_pin, 2);
  
  Serial.begin(115200);
  
  // Connect ESP32 to your WiFi.
  WiFi.begin(ssid, password);
  
  Serial.print("Try to connect to WiFi. Please wait! ");
  // Wait until successful connection established.
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print("*");
  }

  // If connection is successful, write WiFi SSID to serial monitor along with assigned IPAddress.
  Serial.print("\n\n-------------------------------------\n\nConnection is successful!\n\nConnected WiFi SSID :");
  Serial.print(ssid);
  Serial.print("\n\nConnected IP_Adress: \n\n");
  Serial.println(WiFi.localIP());

}

void loop(){
  // Get variables.
  readButtons();
  
  changeColor();

  // Define connection path to transfer data to the database.
  String send_data = GIFT_PATH + "?block=" + block + "&color=" + color + "&audio=" + audio;

  // Define the client and make an HTTP request.
  HTTPClient http;
  http.begin(send_data);
  int httpCode = http.GET();
  if(httpCode == 200){ Serial.println("\nData Send to Localhost Successfully!"); }else{ Serial.print("ERROR: " + String(httpCode)); }
  http.end();
}

void readButtons(){
  // Use the ternary operator to change values easily.
  if(digitalRead(BLOCK) == HIGH){ block = (block == "true") ? "false" : "true"; }
  if(digitalRead(AUDIO) == HIGH){ audio = (audio == "true") ? "false" : "true"; }
}

void changeColor(){
  R = map(analogRead(red_pot), 0, 4096, 0, 255);  
  G = map(analogRead(green_pot), 0, 4096, 0, 255);  
  B = map(analogRead(blue_pot), 0, 4096, 0, 255);

  // Display color pattern on the module.
  ledcWrite(0, 255 - R);
  ledcWrite(1, 255 - G);
  ledcWrite(2, 255 - B);

  // Define the rgb color variable.
  color = "rgb(" + String(R) + "," + String(G) + "," + String(B) + ")";

}
  
