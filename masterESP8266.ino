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