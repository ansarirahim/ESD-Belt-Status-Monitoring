#include <ESP8266WiFi.h>
///37984,15106 is considered as 0.3 esd

//A. R. Ansari
//05.03.2020
//29896 1000 0.62,0.59  0.62 0.39 0.48 0.20
//firmware is revised to meet rgb led connections
//firmware is revised to give RESET MODE AND 5 MINUTES OVER FOR RESET MODE
//ReadESDStationData();//modification
//16.12.19
// CHECK CONNECTIVITY IS ADDED 21022020
#define FIRMWAREVERSION "VER1.00 REV1.00"
#define FILENAME "Station06032020"
#define RMSRAW "0.3"
//#include "DHT.h"

//------------------------------------------------------------------------------------
// Defining I/O Pins
//------------------------------------------------------------------------------------
#define       LED0      2         // WIFI Module LED
#define       LED1      D0        // Connectivity With Client #1
#define       LED2      D2        // Connectivity With Client #2
#define       BUTTON    D1        // Connectivity ReInitiate Button
#define       TWI_FREQ  400000L   // I2C Frequency Setting To 400KHZ
#define DHTPIN D7

#define DHTTYPE DHT11   // DHT 11
///DHT dht(DHTPIN, DHTTYPE);
//------------------------------------------------------------------------------------
// BUTTON Variables
//------------------------------------------------------------------------------------
int           ButtonState;
int           LastButtonState   = LOW;
int           LastDebounceTime  = 0;
int           DebounceDelay     = 50;
const String  ButtonColor       = "BLU";
float temperature ;
float humidity ;
String t, h;
//------------------------------------------------------------------------------------
// LED Delay Variables
//------------------------------------------------------------------------------------
int           LEDState          = LOW;
unsigned long CurrMillis        = 0;
unsigned long PrevMillis        = 0;
unsigned long Interval          = 1000;
//------------------------------------------------------------------------------------
// Authentication Variables
//------------------------------------------------------------------------------------
char*         TKDssid;
float RmsValueStringToFloat;
char*         TKDpassword;
IPAddress     TKDServer(192, 168, 4, 1);
WiFiClient    TKDClient;

#define NOOFSAMPLES 1000
#define VS 5000UL
#define R2 10000UL
#define R1 1500UL
#define BUTTON_STATE_LOW 0
#define BUTTON_STATE_HIGH 1
int StaionStatus = 0;
#define ESD_BELT_PLUGGED 1
#define ESD_BELT_UN_PLUGGED 3
#define ESD_BELT_FAULTY 2
#define RESET_MODE 4
#define MINT5_AFTER_RESET 5
#define LUNCH_MODE 6
///#define LED_BLUE D6

#define BLUELED D0            // Led in NodeMCU at pin GPIO16 (D0).
#define LED_BLUE BLUELED  ///D6
#define REDLED D1
#define GREENLED D2
#define BUTTON_BYPASSMODE D3
#define BUTTON_RESETMODE D4
#define BUTTON_LUNCHMODE D6
#define BUTTON_RESET_5MINT D5
#define LED_ESD_RESETMODE BLUELED //D6
 
#define LED_ESD_NORMAL GREENLED ///D7
#define LED_ESD_FAULTY REDLED ///D8
double calibs = 5.0;
const int analogInPin = A0;  // ESP8266 Analog Pin ADC0 = A0

///int sensorValue = 0;  // value read from the pot
int outputValue = 0;  // value to output to a PWM pin

String ReadSwitches = "";
double sensorValues[NOOFSAMPLES];
//double calib[NOOFSAMPLES];
double sensorValue = 0;
double MaxSensorValue = 0;
double Rmsvalue = 0;
double sqaurevalues = 0;
int buttonState = 0;
int fiveminutescounter = 0;
#define RESET_TIMES 5

#define RESET_TIMEOUT 400
bool Stopthecount = false;
bool Stopmilisec=false;

#define BROADCAST_DELAY 1000  ///1000
 String stationinf = "";
unsigned short stationid;
unsigned short CRC16(unsigned short CRC, unsigned char Data) {
  Data ^= CRC & 255;
  Data ^= Data << 4;
  unsigned short t = (((unsigned short)Data << 8) | ((CRC >> 8) & 255));
  t ^= (unsigned char)(Data >> 4);
  t ^= ((unsigned short)Data << 3);
  return t;
}
byte mac[6];
#define SERVERNAME "SERVER1"
#define PASSWORD "TajMahal"
String StringRmsRaw="";
void PrintGeneralFirmwareInformation()
{
  StringRmsRaw=RMSRAW;
    Serial.println("*******************");
Serial.println(FIRMWAREVERSION);
Serial.println(FILENAME);
Serial.println("WILL CONNECT TO THE MASTER:");
  Serial.println(SERVERNAME);
   Serial.print("stationID= ");
  Serial.println(stationid, DEC); //&0x0000ffffffff);
  Serial.print("espchipID=");
  Serial.print(ESP.getChipId());
  RmsValueStringToFloat=StringRmsRaw.toFloat();
  Serial.println("\nRMSCheck=");
    Serial.println(RmsValueStringToFloat);
   Serial.println("*******************");
}
void PrintIPformation()
{
   Serial.println("!-- Client Device Connected --!");

  // Printing IP Address --------------------------------------------------
  Serial.println("Connected To      : " + String(WiFi.SSID()));
  Serial.println("Signal Strenght   : " + String(WiFi.RSSI()) + " dBm");
  Serial.print  ("Server IP Address : ");
  Serial.println(TKDServer);
  Serial.print  ("Device IP Address : ");
  Serial.println(WiFi.localIP());

}


//void DisplayRed()
//{
//  digitalWrite(GREENLED, LOW);
//  digitalWrite(BLUELED, LOW);
//  digitalWrite(REDLED, HIGH);
//}
//
//void DisplayBlue()
//{
//  digitalWrite(REDLED, LOW);
//  digitalWrite(GREENLED, LOW);
//  digitalWrite(BLUELED, HIGH);
//
//}
//void DisplayGreen()
//{ digitalWrite(BLUELED, LOW);
//  digitalWrite(REDLED, LOW);
//  digitalWrite(GREENLED, HIGH);
//
//}
void DisplayRed()
{
  digitalWrite(GREENLED, HIGH);
  digitalWrite(BLUELED, HIGH);
  digitalWrite(REDLED, LOW);
}

void DisplayBlue()
{
  digitalWrite(REDLED, HIGH);
  digitalWrite(GREENLED, HIGH);
  digitalWrite(BLUELED, LOW);

}
void DisplayGreen()
{ digitalWrite(BLUELED, HIGH);
  digitalWrite(REDLED, HIGH);
  digitalWrite(GREENLED, LOW);

}

#define BLUELED D0            // Led in NodeMCU at pin GPIO16 (D0).
#define REDLED D1
#define GREENLED D2
void setupLeds() {
  pinMode(BLUELED, OUTPUT);    // LED pin as output.
  pinMode(REDLED, OUTPUT);    // LED pin as output.
  pinMode(GREENLED, OUTPUT);    // LED pin as output.
}
void RgbTest() {
//digitalWrite(LED, HIGH);// turn the LED off.(Note that LOW is the voltage level but actually 
                        //the LED is on; this is because it is acive low on the ESP8266.
//delay(1000);            // wait for 1 second.
//digitalWrite(LED, LOW); // turn the LED on.
DisplayRed();
delay(300);
DisplayGreen();
delay(600);
DisplayBlue();
delay(900); // wait for 1 second.
}


void setup()
{
  /* ----------------------------------------------------------------------
     Setting The I2C Pins SDA, SCL
     Because We Didnt Specify Any Pins The Defult
     SDA = D4 <GPIO2>, SCL = D5 <GPIO14> For ESP8266 Dev Kit Node MCU v3
    --------------------------------------------------------------------- */
  //Wire.begin();                   // Begginning The I2C
  //    dht.begin();

  // Setting Up The I2C Of The MPU9250 ------------------------------------
  //    Wire.setClock(TWI_FREQ);        // Setting The Frequency MPU9250 Require

  // Setting The Serial Port ----------------------------------------------
  setupLeds() ;
   for(int i=0;i<3;i++)
  RgbTest();
  Serial.begin(115200);           // Computer Communication

  // Setting The Mode Of Pins ---------------------------------------------
  ///pinMode(LED0, OUTPUT);          // WIFI OnBoard LED Light
 /// pinMode(LED1, OUTPUT);          // Indicator For Client #1 Connectivity
 // pinMode(LED2, OUTPUT);          // Indicator For Client #2 Connectivity
  ////pinMode(BUTTON, INPUT_PULLUP);  // Initiate Connectivity
////  digitalWrite(LED0, !LOW);       // Turn WiFi LED Off

WiFi.macAddress(mac);
 stationid = 80;
  for (int i = 0; i < 6; i++)
    stationid = CRC16(stationid, mac[i]);
   
  // Print Message Of I/O Setting Progress
  
  ///StationInf = "$" + String(stationid) + "," + String( WiFi.macAddress()) + ",";
  // Print Message Of I/O Setting Progress --------------------------------
  Serial.println("\nI/O Pins Modes Set .... Done");

  // Starting To Connect --------------------------------------------------
  WiFi.mode(WIFI_STA);            // To Avoid Broadcasting An SSID
  WiFi.begin(SERVERNAME, PASSWORD);         // The SSID That We Want To Connect To

  // Printing Message For User That Connetion Is On Process ---------------
  Serial.println("!--- Connecting To " + WiFi.SSID() + " ---!");
 PrintGeneralFirmwareInformation();

  
  // WiFi Connectivity ----------------------------------------------------
 CheckConnectivity();            // Checking For Connection
PrintIPformation();
  // Stop Blinking To Indicate Connected ----------------------------------
 /// digitalWrite(LED0, !HIGH);
ReadESDStationData();

  // Conecting The Device As A Client -------------------------------------
  TKDRequest();
}


String WifiModuleID = ",Wifi1\n\r";
char recieved;
String  inData = "";
void loop()
{
  //delay(200);
  //ReadESDStationData();
  senddata("BISMILLAH\n");///stationinf);//"BISMILLAH\n");

///ReadESDStationData();

}




void senddata(String datains) {

  ///TKDClient.println(datains);///"Client1Temp" + t );
if(TKDClient.connected()){
  TKDClient.flush();
  if (TKDClient.available())
  {
    // Here We Read The Message
    ReadESDStationData();
    String Message = TKDClient.readStringUntil('\n');//\r');
    // Here We Print The Message On The Screen
    Serial.println(Message);
    /// if(Message=="_ESD_DATA")//<GETESD>")
   /// ReadESDStationData();
    TKDClient.println(stationinf);//datains);
    TKDClient.flush();
    // Here We Reply To The Client With A Message
    /// TKDClient.print(WifiID+"End\nWe Got Your Message");
    //TKDClient.flush();
  }//
}
else
{
  ESP.reset();
  CheckConnectivity();
}
///WiFi.mode(WIFI_STA);            // To Avoid Broadcasting An SSID
 /// WiFi.begin(SERVERNAME, PASSWORD); 
// else
// {
//  ESP.restart(); 
// /// CheckConnectivity();
//
// }
    ///TKDRequest();
}


///void (*state_table[])() = { DisplayBlue, DisplayRed, DisplayGreen};
void CheckConnectivity()
{
  int i=0;
  while (WiFi.status() != WL_CONNECTED)
  {
    
   switch(i)
    {
      case 0 :
      DisplayBlue();
      break;
      case 1 :
      DisplayRed();
      break;
      case 2:
      DisplayGreen();
     
      
      Serial.print(".");
    }
    delay(200);
    i++;
    if(i>3)
    i=0;
    Serial.println("");
  }
}



void TKDRequest()
{
  // First Make Sure You Got Disconnected
  TKDClient.stop();

  // If Sucessfully Connected Send Connection Message
  if (TKDClient.connect(TKDServer, 9001))
  {
    //      Serial.println    ("<" + ButtonColor + "-CONNECTED>");
    //      TKDClient.println ("<" + ButtonColor + "-CONNECTED>");
    Serial.println    ("Client Connected");
    /// TKDClient.println ("Client Connected");
  }
}


///////////////////////


void DisplayOFF()
{
  digitalWrite(GREENLED, LOW);
   digitalWrite(BLUELED, LOW);
    digitalWrite(REDLED, LOW);
}


void RGBLEDsetup() {
pinMode(BLUELED, OUTPUT);    // LED pin as output.
pinMode(REDLED, OUTPUT);    // LED pin as output.
pinMode(GREENLED, OUTPUT);    // LED pin as output.
}
//local start;
long now;
long finished;
long delta;
#define BYPASSMODETIMEOUT 300
void ReadButtonsExecuteLED()
{


  //  buttonState = digitalRead(button); // put your main code here, to run repeatedly:
 if (digitalRead(BUTTON_BYPASSMODE) == 0)
  {
    if (Stopmilisec==false)///Stopthecount == false)
    { // fiveminutescounter++;
      
    now = millis()/1000;
    Stopmilisec=true;
    Serial.print("Starttime=");
    Serial.println(now);
    ReadSwitches = String(RESET_MODE);
    }
    else
    {
        ReadSwitches = String(RESET_MODE);
 finished = millis()/1000;//-now)/1000;
 Serial.print("finished=");
    Serial.println(finished);
    
 delta=finished-now;
 Serial.print("Delta=");
    Serial.println(delta);
 if(delta>=BYPASSMODETIMEOUT)
 
      {
       ReadSwitches=String(MINT5_AFTER_RESET);
      }
    // else
     
      
    }
    //  Serial.print("cOUNTER=");
    //// Serial.println(fiveminutescounter);
    /// Serial.println("RESET MODE");
    
  }

else
  {
   
    Stopmilisec=false;
  
    if (Rmsvalue < RmsValueStringToFloat)
    //0.3
    {
      ///digitalWrite(LED_ESD_NORMAL, LOW);
      /// digitalWrite(LED_ESD_FAULTY, HIGH);
      ReadSwitches = String(ESD_BELT_PLUGGED);
    }
    else
    { ReadSwitches = String(ESD_BELT_UN_PLUGGED);
      /// digitalWrite(LED_ESD_NORMAL, HIGH);
      /// digitalWrite(LED_ESD_FAULTY, LOW);
    }

  }
  if (Rmsvalue < RmsValueStringToFloat)
  {
    DisplayRed();
   //// digitalWrite(LED_ESD_NORMAL, LOW);
    //Serial.println("esd normal led d7 low");
  ////  digitalWrite(LED_ESD_FAULTY, HIGH);
    //Serial.println("esd normal led d8 high");
  }
  else
  {
DisplayGreen();

   // digitalWrite(LED_ESD_NORMAL, HIGH);
    //Serial.println("esd normal led d7 high");
   /// digitalWrite(LED_ESD_FAULTY, LOW);
    //  Serial.println("esd normal led d8 low");

  }

 

}
bool displaymode = true;
void ReadESDStationData()

{
  // read the analog in value
  MaxSensorValue = 0;
  for (int i = 0; i < NOOFSAMPLES; i++) {

    //    if(i==0){
    //      Serial.print("vout=");
    //     Serial.println(calibfactor());}
    ///delay(0.02);
    sensorValue = analogRead(analogInPin);
    sensorValues[i] = sensorValue;

    if (MaxSensorValue < sensorValue)
      MaxSensorValue = sensorValue;

  }
  sqaurevalues = 0;

  for (int i = 0; i < NOOFSAMPLES; i++)
  {

    sqaurevalues += sensorValues[i] * sensorValues[i];

  }
  Rmsvalue = sqrt(sqaurevalues / NOOFSAMPLES);

  Rmsvalue = Rmsvalue * calibs / 1024;
  MaxSensorValue = MaxSensorValue * calibs / 1024;
  ///  Serial.print(sensorValue*calibs/1024); Serial.print(" \t ");
  //Serial.print(MaxSensorValue);//*calibs/1024);
  //Serial.print(" \t "); Serial.println(Rmsvalue);//*calibs/1024);


  ReadButtonsExecuteLED();



  if (ReadSwitches == String(MINT5_AFTER_RESET))
  {
    if (displaymode == true)
    {
      DisplayBlue();
      displaymode = false;
      Serial.println("blue");
    }
    else
    { Serial.println("red ");
      DisplayRed();
      displaymode = true;
    }

    /// delay(1);

  }
  else if (ReadSwitches ==  String(RESET_MODE))
  {
    Serial.println("bLUE ENABLED");
    DisplayBlue();

    //delay(10);
  } else if (ReadSwitches == String(ESD_BELT_UN_PLUGGED))
  {
    DisplayRed();
   /// Serial.println("RED ENABLED");
    //delay(10);



  }
  else if (ReadSwitches == String(ESD_BELT_PLUGGED))
  {
    DisplayGreen();
    Serial.println("green ENABLED");
    //delay(10);



  }

  stationinf = "$" + String(stationid) + "," + String( WiFi.macAddress()) + "," + String(ReadSwitches) + "," + String(MaxSensorValue) + "," + String(Rmsvalue)+'\n'; //+"@";

  ///Serial.println(stationinf);
  ReadSwitches = "";





  ///delay(BROADCAST_DELAY);//1000);
}

From: AbdulRahim Ansari 
Sent: Thursday, February 27, 2020 2:24 PM
To: AbdulRahim Ansari
Subject: RE: "cLIENTS NODE MCU

#include <ESP8266WiFi.h>

//A. R. Ansari
//firmware is revised to meet rgb led connections
//firmware is revised to give RESET MODE AND 5 MINUTES OVER FOR RESET MODE
//16.12.19
// CHECK CONNECTIVITY IS ADDED 21022020
#define FIRMWAREVERSION "VER1.00 REV1.00"
#define FILENAME "ClientCA21022020"
//#include "DHT.h"

//------------------------------------------------------------------------------------
// Defining I/O Pins
//------------------------------------------------------------------------------------
#define       LED0      2         // WIFI Module LED
#define       LED1      D0        // Connectivity With Client #1
#define       LED2      D2        // Connectivity With Client #2
#define       BUTTON    D1        // Connectivity ReInitiate Button
#define       TWI_FREQ  400000L   // I2C Frequency Setting To 400KHZ
#define DHTPIN D7

#define DHTTYPE DHT11   // DHT 11
///DHT dht(DHTPIN, DHTTYPE);
//------------------------------------------------------------------------------------
// BUTTON Variables
//------------------------------------------------------------------------------------
int           ButtonState;
int           LastButtonState   = LOW;
int           LastDebounceTime  = 0;
int           DebounceDelay     = 50;
const String  ButtonColor       = "BLU";
float temperature ;
float humidity ;
String t, h;
//------------------------------------------------------------------------------------
// LED Delay Variables
//------------------------------------------------------------------------------------
int           LEDState          = LOW;
unsigned long CurrMillis        = 0;
unsigned long PrevMillis        = 0;
unsigned long Interval          = 1000;
//------------------------------------------------------------------------------------
// Authentication Variables
//------------------------------------------------------------------------------------
char*         TKDssid;
char*         TKDpassword;
IPAddress     TKDServer(192, 168, 4, 1);
WiFiClient    TKDClient;

#define NOOFSAMPLES 100
#define VS 5000UL
#define R2 10000UL
#define R1 1500UL
#define BUTTON_STATE_LOW 0
#define BUTTON_STATE_HIGH 1
int StaionStatus = 0;
#define ESD_BELT_PLUGGED 1
#define ESD_BELT_UN_PLUGGED 3
#define ESD_BELT_FAULTY 2
#define RESET_MODE 4
#define MINT5_AFTER_RESET 5
#define LUNCH_MODE 6
///#define LED_BLUE D6

#define BLUELED D0            // Led in NodeMCU at pin GPIO16 (D0).
#define LED_BLUE BLUELED  ///D6
#define REDLED D1
#define GREENLED D2
#define BUTTON_BYPASSMODE D3
#define BUTTON_RESETMODE D4
#define BUTTON_LUNCHMODE D6
#define BUTTON_RESET_5MINT D5
#define LED_ESD_RESETMODE BLUELED //D6
 
#define LED_ESD_NORMAL GREENLED ///D7
#define LED_ESD_FAULTY REDLED ///D8
double calibs = 5.0;
const int analogInPin = A0;  // ESP8266 Analog Pin ADC0 = A0

///int sensorValue = 0;  // value read from the pot
int outputValue = 0;  // value to output to a PWM pin

String ReadSwitches = "";
double sensorValues[NOOFSAMPLES];
//double calib[NOOFSAMPLES];
double sensorValue = 0;
double MaxSensorValue = 0;
double Rmsvalue = 0;
double sqaurevalues = 0;
int buttonState = 0;
int fiveminutescounter = 0;
#define RESET_TIMES 5

#define RESET_TIMEOUT 400
bool Stopthecount = false;
bool Stopmilisec=false;

#define BROADCAST_DELAY 1000  ///1000
 String stationinf = "";
unsigned short stationid;
unsigned short CRC16(unsigned short CRC, unsigned char Data) {
  Data ^= CRC & 255;
  Data ^= Data << 4;
  unsigned short t = (((unsigned short)Data << 8) | ((CRC >> 8) & 255));
  t ^= (unsigned char)(Data >> 4);
  t ^= ((unsigned short)Data << 3);
  return t;
}
byte mac[6];
#define SERVERNAME "SERVER1"
#define PASSWORD "TajMahal"
void PrintGeneralFirmwareInformation()
{
    Serial.println("*******************");
Serial.println(FIRMWAREVERSION);
Serial.println(FILENAME);
Serial.println("WILL CONNECT TO THE MASTER:");
  Serial.println(SERVERNAME);
   Serial.print("stationID= ");
  Serial.println(stationid, DEC); //&0x0000ffffffff);
  Serial.print("espchipID=");
  Serial.print(ESP.getChipId());
   Serial.println("*******************");
}
void PrintIPformation()
{
   Serial.println("!-- Client Device Connected --!");

  // Printing IP Address --------------------------------------------------
  Serial.println("Connected To      : " + String(WiFi.SSID()));
  Serial.println("Signal Strenght   : " + String(WiFi.RSSI()) + " dBm");
  Serial.print  ("Server IP Address : ");
  Serial.println(TKDServer);
  Serial.print  ("Device IP Address : ");
  Serial.println(WiFi.localIP());

}


//void DisplayRed()
//{
//  digitalWrite(GREENLED, LOW);
//  digitalWrite(BLUELED, LOW);
//  digitalWrite(REDLED, HIGH);
//}
//
//void DisplayBlue()
//{
//  digitalWrite(REDLED, LOW);
//  digitalWrite(GREENLED, LOW);
//  digitalWrite(BLUELED, HIGH);
//
//}
//void DisplayGreen()
//{ digitalWrite(BLUELED, LOW);
//  digitalWrite(REDLED, LOW);
//  digitalWrite(GREENLED, HIGH);
//
//}
void DisplayRed()
{
  digitalWrite(GREENLED, HIGH);
  digitalWrite(BLUELED, HIGH);
  digitalWrite(REDLED, LOW);
}

void DisplayBlue()
{
  digitalWrite(REDLED, HIGH);
  digitalWrite(GREENLED, HIGH);
  digitalWrite(BLUELED, LOW);

}
void DisplayGreen()
{ digitalWrite(BLUELED, HIGH);
  digitalWrite(REDLED, HIGH);
  digitalWrite(GREENLED, LOW);

}

#define BLUELED D0            // Led in NodeMCU at pin GPIO16 (D0).
#define REDLED D1
#define GREENLED D2
void setupLeds() {
  pinMode(BLUELED, OUTPUT);    // LED pin as output.
  pinMode(REDLED, OUTPUT);    // LED pin as output.
  pinMode(GREENLED, OUTPUT);    // LED pin as output.
}
void RgbTest() {
//digitalWrite(LED, HIGH);// turn the LED off.(Note that LOW is the voltage level but actually 
                        //the LED is on; this is because it is acive low on the ESP8266.
//delay(1000);            // wait for 1 second.
//digitalWrite(LED, LOW); // turn the LED on.
DisplayRed();
delay(300);
DisplayGreen();
delay(600);
DisplayBlue();
delay(900); // wait for 1 second.
}


void setup()
{
  /* ----------------------------------------------------------------------
     Setting The I2C Pins SDA, SCL
     Because We Didnt Specify Any Pins The Defult
     SDA = D4 <GPIO2>, SCL = D5 <GPIO14> For ESP8266 Dev Kit Node MCU v3
    --------------------------------------------------------------------- */
  //Wire.begin();                   // Begginning The I2C
  //    dht.begin();

  // Setting Up The I2C Of The MPU9250 ------------------------------------
  //    Wire.setClock(TWI_FREQ);        // Setting The Frequency MPU9250 Require

  // Setting The Serial Port ----------------------------------------------
  setupLeds() ;
   for(int i=0;i<3;i++)
  RgbTest();
  Serial.begin(115200);           // Computer Communication

  // Setting The Mode Of Pins ---------------------------------------------
  ///pinMode(LED0, OUTPUT);          // WIFI OnBoard LED Light
 /// pinMode(LED1, OUTPUT);          // Indicator For Client #1 Connectivity
 // pinMode(LED2, OUTPUT);          // Indicator For Client #2 Connectivity
  ////pinMode(BUTTON, INPUT_PULLUP);  // Initiate Connectivity
////  digitalWrite(LED0, !LOW);       // Turn WiFi LED Off

WiFi.macAddress(mac);
 stationid = 80;
  for (int i = 0; i < 6; i++)
    stationid = CRC16(stationid, mac[i]);
   
  // Print Message Of I/O Setting Progress
  
  ///StationInf = "$" + String(stationid) + "," + String( WiFi.macAddress()) + ",";
  // Print Message Of I/O Setting Progress --------------------------------
  Serial.println("\nI/O Pins Modes Set .... Done");

  // Starting To Connect --------------------------------------------------
  WiFi.mode(WIFI_STA);            // To Avoid Broadcasting An SSID
  WiFi.begin(SERVERNAME, PASSWORD);         // The SSID That We Want To Connect To

  // Printing Message For User That Connetion Is On Process ---------------
  Serial.println("!--- Connecting To " + WiFi.SSID() + " ---!");
 PrintGeneralFirmwareInformation();

  
  // WiFi Connectivity ----------------------------------------------------
 CheckConnectivity();            // Checking For Connection
PrintIPformation();
  // Stop Blinking To Indicate Connected ----------------------------------
 /// digitalWrite(LED0, !HIGH);
 ReadESDStationData();

  // Conecting The Device As A Client -------------------------------------
  TKDRequest();
}


String WifiModuleID = ",Wifi1\n\r";
char recieved;
String  inData = "";
void loop()
{
  //delay(200);
  //ReadESDStationData();
  senddata("BISMILLAH\n");///stationinf);//"BISMILLAH\n");



}




void senddata(String datains) {

  ///TKDClient.println(datains);///"Client1Temp" + t );
if(TKDClient.connected()){
  TKDClient.flush();
  if (TKDClient.available())
  {
    // Here We Read The Message
    String Message = TKDClient.readStringUntil('\n');//\r');
    // Here We Print The Message On The Screen
    Serial.println(Message);
    /// if(Message=="_ESD_DATA")//<GETESD>")
    ReadESDStationData();
    TKDClient.println(stationinf);//datains);
    TKDClient.flush();
    // Here We Reply To The Client With A Message
    /// TKDClient.print(WifiID+"End\nWe Got Your Message");
    //TKDClient.flush();
  }//
}
else
{
  ESP.reset();
  CheckConnectivity();
}
///WiFi.mode(WIFI_STA);            // To Avoid Broadcasting An SSID
 /// WiFi.begin(SERVERNAME, PASSWORD); 
// else
// {
//  ESP.restart(); 
// /// CheckConnectivity();
//
// }
    ///TKDRequest();
}


///void (*state_table[])() = { DisplayBlue, DisplayRed, DisplayGreen};
void CheckConnectivity()
{
  int i=0;
  while (WiFi.status() != WL_CONNECTED)
  {
    
   switch(i)
    {
      case 0 :
      DisplayBlue();
      break;
      case 1 :
      DisplayRed();
      break;
      case 2:
      DisplayGreen();
     
      
      Serial.print(".");
    }
    delay(200);
    i++;
    if(i>3)
    i=0;
    Serial.println("");
  }
}



void TKDRequest()
{
  // First Make Sure You Got Disconnected
  TKDClient.stop();

  // If Sucessfully Connected Send Connection Message
  if (TKDClient.connect(TKDServer, 9001))
  {
    //      Serial.println    ("<" + ButtonColor + "-CONNECTED>");
    //      TKDClient.println ("<" + ButtonColor + "-CONNECTED>");
    Serial.println    ("Client Connected");
    /// TKDClient.println ("Client Connected");
  }
}


///////////////////////


void DisplayOFF()
{
  digitalWrite(GREENLED, LOW);
   digitalWrite(BLUELED, LOW);
    digitalWrite(REDLED, LOW);
}


void RGBLEDsetup() {
pinMode(BLUELED, OUTPUT);    // LED pin as output.
pinMode(REDLED, OUTPUT);    // LED pin as output.
pinMode(GREENLED, OUTPUT);    // LED pin as output.
}
//local start;
long now;
long finished;
long delta;
#define BYPASSMODETIMEOUT 300
void ReadButtonsExecuteLED()
{


  //  buttonState = digitalRead(button); // put your main code here, to run repeatedly:
 if (digitalRead(BUTTON_BYPASSMODE) == 0)
  {
    if (Stopmilisec==false)///Stopthecount == false)
    { // fiveminutescounter++;
      
    now = millis()/1000;
    Stopmilisec=true;
    Serial.print("Starttime=");
    Serial.println(now);
    ReadSwitches = String(RESET_MODE);
    }
    else
    {
        ReadSwitches = String(RESET_MODE);
 finished = millis()/1000;//-now)/1000;
 Serial.print("finished=");
    Serial.println(finished);
    
 delta=finished-now;
 Serial.print("Delta=");
    Serial.println(delta);
 if(delta>=BYPASSMODETIMEOUT)
 
      {
       ReadSwitches=String(MINT5_AFTER_RESET);
      }
    // else
     
      
    }
    //  Serial.print("cOUNTER=");
    //// Serial.println(fiveminutescounter);
    /// Serial.println("RESET MODE");
    
  }

else
  {
   
    Stopmilisec=false;
  
    if (Rmsvalue < 0.3)
    {
      ///digitalWrite(LED_ESD_NORMAL, LOW);
      /// digitalWrite(LED_ESD_FAULTY, HIGH);
      ReadSwitches = String(ESD_BELT_PLUGGED);
    }
    else
    { ReadSwitches = String(ESD_BELT_UN_PLUGGED);
      /// digitalWrite(LED_ESD_NORMAL, HIGH);
      /// digitalWrite(LED_ESD_FAULTY, LOW);
    }

  }
  if (Rmsvalue < 0.3)
  {
    DisplayRed();
   //// digitalWrite(LED_ESD_NORMAL, LOW);
    //Serial.println("esd normal led d7 low");
  ////  digitalWrite(LED_ESD_FAULTY, HIGH);
    //Serial.println("esd normal led d8 high");
  }
  else
  {
DisplayGreen();

   // digitalWrite(LED_ESD_NORMAL, HIGH);
    //Serial.println("esd normal led d7 high");
   /// digitalWrite(LED_ESD_FAULTY, LOW);
    //  Serial.println("esd normal led d8 low");

  }

 

}
bool displaymode = true;
void ReadESDStationData()

{
  // read the analog in value
  MaxSensorValue = 0;
  for (int i = 0; i < NOOFSAMPLES; i++) {

    //    if(i==0){
    //      Serial.print("vout=");
    //     Serial.println(calibfactor());}
    delay(0.2);
    sensorValue = analogRead(analogInPin);
    sensorValues[i] = sensorValue;

    if (MaxSensorValue < sensorValue)
      MaxSensorValue = sensorValue;

  }
  sqaurevalues = 0;

  for (int i = 0; i < NOOFSAMPLES; i++)
  {

    sqaurevalues += sensorValues[i] * sensorValues[i];

  }
  Rmsvalue = sqrt(sqaurevalues / NOOFSAMPLES);

  Rmsvalue = Rmsvalue * calibs / 1024;
  MaxSensorValue = MaxSensorValue * calibs / 1024;
  ///  Serial.print(sensorValue*calibs/1024); Serial.print(" \t ");
  //Serial.print(MaxSensorValue);//*calibs/1024);
  //Serial.print(" \t "); Serial.println(Rmsvalue);//*calibs/1024);


  ReadButtonsExecuteLED();



  if (ReadSwitches == String(MINT5_AFTER_RESET))
  {
    if (displaymode == true)
    {
      DisplayBlue();
      displaymode = false;
      Serial.println("blue");
    }
    else
    { Serial.println("red ");
      DisplayRed();
      displaymode = true;
    }

    /// delay(1);

  }
  else if (ReadSwitches ==  String(RESET_MODE))
  {
    Serial.println("bLUE ENABLED");
    DisplayBlue();

    //delay(10);
  } else if (ReadSwitches == String(ESD_BELT_UN_PLUGGED))
  {
    DisplayRed();
   /// Serial.println("RED ENABLED");
    //delay(10);



  }
  else if (ReadSwitches == String(ESD_BELT_PLUGGED))
  {
    DisplayGreen();
    Serial.println("green ENABLED");
    //delay(10);



  }

  stationinf = "$" + String(stationid) + "," + String( WiFi.macAddress()) + "," + String(ReadSwitches) + "," + String(MaxSensorValue) + "," + String(Rmsvalue)+'\n'; //+"@";

  ///Serial.println(stationinf);
  ReadSwitches = "";





  ///delay(BROADCAST_DELAY);//1000);
}

From: AbdulRahim Ansari 
Sent: Thursday, February 27, 2020 1:52 PM
To: AbdulRahim Ansari
Subject: "ESP8266SERVERTO4CLIENTS"

//-- Libraries Included --------------------------------------------------------------
#include <ESP8266WiFi.h>

///master for 4 Clients 
#define FIRMWAREVERSION "VER1.00 REV1.00"
#define FILENAME "ESP8266SERVERTO4CLIENTS"
//271219 WAS CHA
//------------------------------------------------------------------------------------
// Define I/O Pins
#define     LED0      D2           // WIFI Module LED
#define     LED1      D0          // Connectivity With Client #1
#define     LED2      D2          // Connectivity With Client #2
#define     BUTTON    D1          // Connectivity ReInitiate Button
//------------------------------------------------------------------------------------
// Authentication Variables
char*       TKDssid;              // SERVER WIFI NAME
char*       TKDpassword;          // SERVER PASSWORD
//------------------------------------------------------------------------------------
#define     MAXSC     4           // MAXIMUM NUMBER OF CLIENTS
WiFiServer  TKDServer(9001);      // THE SERVER AND THE PORT NUMBER
WiFiClient  TKDClient[MAXSC];     // THE SERVER CLIENTS

#define MCUID "SERVER1"
//ESD_ACCESSPOINT"
#define MCUIDPASS "TajMahal"
String Serverinf;
unsigned short  serverid;
byte mac[6];
unsigned short CRC16(unsigned short CRC, unsigned char Data) {
  Data ^= CRC & 255;
  Data ^= Data << 4;
  unsigned short t = (((unsigned short)Data << 8) | ((CRC >> 8) & 255));
  t ^= (unsigned char)(Data >> 4);
  t ^= ((unsigned short)Data << 3);
  return t;
}
#define SERVERNAME "SERVER1"
#define STANDBYMODE "6,0,0"
#define NORMALMODE "0,0,0"
//#define BUTTON_LUNCHMODE D3 //D6

String SerialMessage;
String  ServerInf = "";
//#define BLUELED D1        //IT WAS D0    // Led in NodeMCU at pin GPIO16 (D0).
///#define REDLED D1
///#define GREENLED D2

int a = 1111;
int eeAddress = 0;
/*
  void DisplayRed()
  {
  digitalWrite(GREENLED, LOW);
  digitalWrite(BLUELED, LOW);
  digitalWrite(REDLED, HIGH);
  }*/
void DisplayRed()
{
  ///digitalWrite(GREENLED, HIGH);
 /// digitalWrite(BLUELED, HIGH);
  //digitalWrite(REDLED, LOW);
}

void DisplayBlue()
{
  //digitalWrite(REDLED, HIGH);
///  digitalWrite(GREENLED, HIGH);
 /// digitalWrite(BLUELED, LOW);

}
void DisplayGreen()
{/// digitalWrite(BLUELED, HIGH);
///  digitalWrite(REDLED, HIGH);
///  digitalWrite(GREENLED, LOW);

}
/*
   common cathode
  void DisplayBlue()
  {
  digitalWrite(REDLED, LOW);
  digitalWrite(GREENLED, LOW);
  digitalWrite(BLUELED, HIGH);

  }
  void DisplayGreen()
  { digitalWrite(BLUELED, LOW);
  digitalWrite(REDLED, LOW);
  digitalWrite(GREENLED, HIGH);

  }*/
void setupLeds() {
 /// pinMode(BLUELED, OUTPUT);    // LED pin as output.
///  pinMode(REDLED, OUTPUT);    // LED pin as output.
///  pinMode(GREENLED, OUTPUT);    // L///ED pin as output.
}
String Serverstatus;
void  UpdateLunchStatus()
{
 // if (digitalRead(BUTTON_LUNCHMODE) == 0)
  //{

//    Serverstatus = STANDBYMODE;
//    // Serial.println( Serverinf);//"pressed");
//    DisplayRed();
//  }
//  else {
//    DisplayGreen();
//    Serverstatus = NORMALMODE;
//    // Serial.println( Serverinf);
//  }
}
void SetupButton()
{
 /// pinMode(BUTTON_LUNCHMODE, INPUT);
}


#define DEVICE_STATUS_ADDRESS 0
void SetWifi(char* Name, char* Password);


void PrintGeneralFirmwareInformation()
{
  Serial.println("*******************");
  Serial.println(FIRMWAREVERSION);
  Serial.println(FILENAME);
  Serial.print("SERVERNAME=");
  Serial.println(SERVERNAME);
  Serial.print("ServerID= ");
  Serial.println(serverid, DEC); //&0x0000ffffffff);
  Serial.print("espchipID=");
  Serial.print(ESP.getChipId());
  Serial.println("*******************");
}


void RgbTest() {
  //digitalWrite(LED, HIGH);// turn the LED off.(Note that LOW is the voltage level but actually
  //the LED is on; this is because it is acive low on the ESP8266.
  //delay(1000);            // wait for 1 second.
  //digitalWrite(LED, LOW); // turn the LED on.
  DisplayRed();
  delay(300);
  DisplayGreen();
  delay(600);
  DisplayBlue();
  delay(900); // wait for 1 second.
}
void setup()
{

  Serial.begin(9600);           // Computer Communication

  setupLeds();
  SetupButton();
  //  Serial.println("I/O Pins Modes Set .... Done");

  // Setting Up A Wifi Access Point
  SetWifi(MCUID, MCUIDPASS);
  Serial.print("serverid=");

  WiFi.macAddress(mac);
  serverid = 80;
  for (int i = 0; i < 6; i++)
    serverid = CRC16(serverid, mac[i]);
  PrintGeneralFirmwareInformation();
  ServerInf = "#" + String(serverid) + "," + String( WiFi.macAddress()) + ",";
  for (int i = 0; i < 5; i++)
    RgbTest();

}


void IsClients2();

void SerialPoll()
{
  {
    if (Serial.available() > 0) {
      SerialMessage = Serial.readStringUntil('\n');
      ///  Serial.println("actual="+SerialMessage);
      if (SerialMessage == "GET_ESD_DATA")
      {
      /// ;// Serial.print(ServerInf + Serverstatus);//commented to not give server information 21022020
        IsClients2();
      }


    }
  }


}




void loop()
{
  UpdateLunchStatus();
  SerialPoll();

}


void SetWifi(char* Name, char* Password)
{
  // Stop Any Previous WIFI
  WiFi.disconnect();

  // Setting The Wifi Mode
  WiFi.mode(WIFI_AP_STA);
  Serial.println("WIFI Mode : AccessPoint Station");

  // Setting The Access Point
  TKDssid      = Name;
  TKDpassword  = Password;

  // Starting The Access Point
  WiFi.softAP(TKDssid, TKDpassword);
  Serial.println("WIFI < " + String(TKDssid) + " > ... Started");

  // Wait For Few Seconds
  delay(1000);

  // Getting Server IP
  IPAddress IP = WiFi.softAPIP();

  // Printing The Server IP Address
  Serial.print("AccessPoint IP : ");
  Serial.println(IP);

  // Starting Server
  TKDServer.begin();
  Serial.println("Server Started");
}



String GetEsd = "<GET_ESD>" + '\r';
void IsClients2()
{
  if (TKDServer.hasClient())
  {
    for (int i = 0; i < MAXSC; i++)
    {
      //find free/disconnected spot
      if (!TKDClient[i] || !TKDClient[i].connected())
      {
        if (TKDClient[i]) TKDClient[i].stop();
        TKDClient[i] = TKDServer.available();

        //// Serial.print("New Client : "); Serial.print(String(i+1) + " - ");
        continue;
      }
    }
    // no free / disconnected spot so reject
    /// digitalWrite(LED1, HIGH);
    WiFiClient TKDClient = TKDServer.available();
    TKDClient.stop();
  }

  //check clients for data -------------------------------------------------------

  for (int i = 0; i < MAXSC; i++)
  {
    if (TKDClient[i] && TKDClient[i].connected())
    { TKDClient[i].println(GetEsd);///"<GETESD>");
      if (TKDClient[i].available())
      {
        // If Any Data Was Available We Read IT
        while (TKDClient[i].available())
        {

          // Read From Client
          Serial.print(TKDClient[i].readStringUntil('\n'));
          // Reply To Client
          /// TKDClient[i].println("<OK>");
        }
      }
    }
  }
}



