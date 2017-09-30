#define TINY_GSM_MODEM_SIM800
#include <TinyGsmClient.h>
#include <TinyGPS.h>
#include <TinyGPS++.h>
#include <SoftwareSerial.h>

TinyGPSPlus gps;
SoftwareSerial mySerial(7, 8); // RX, TX
TinyGsm modem(mySerial);
TinyGsmClient client(modem);


const char apn[]  = "internet";
const char user[]  = "";
const char pass[]  = "";
const char server[] = "(your link)";
const char resource[] = "(path your API GET)";
int port = 80;



void setup() {
  // Open serial communications and wait for port to open:
  delay(30000);
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
Serial.println("Restart Modem");
   modem.restart();
  
  delay(3000);
  Serial.println("Goodnight moon!");

  // set the data rate for the SoftwareSerial port
  mySerial.begin(9600);
  mySerial.println("AT+CGNSPWR=1");
  mySerial.println("AT+CGNSTST=1");
  Serial.println("Finding GPS... ");
 delay(9 0000);
  
  
}

void loop() { // run over and over
  
  if (mySerial.available()) {
    gps.encode(mySerial.read());
 }
if (gps.location.isUpdated())
{
  float latt = gps.location.lat();
  float longg = gps.location.lng();
Serial.print("LATITUDE:");
Serial.println(latt,10); // Latitude in degrees (double)
Serial.print("LONGITUDE:");
Serial.println(longg,10); // Longitude in degrees (double)
Serial.print("TANGGAL:");
Serial.println(gps.date.value()); // Raw date in DDMMYY format (u32)
Serial.print("WAKTU:");
Serial.println(gps.time.value()); // Raw time in HHMMSSCC format (u32)
Serial.print("KECEPATAN:");
Serial.println(gps.speed.kmph()); 
Serial.print("ALTITUDE:");
Serial.println(gps.altitude.meters());


Serial.println("Stop GPS... ");
mySerial.println("AT+CGNSTST=0");
  delay(1000); 
  
Serial.print(F("Waiting for network..."));
  if (!modem.waitForNetwork()) {
    Serial.println(" fail");
    delay(10000);
    return;
  }
  Serial.println(" OK");

  Serial.print(F("Connecting to "));
  Serial.print(apn);
  if (!modem.gprsConnect(apn, user, pass)) {
    Serial.println(" fail");
    delay(10000);
    return;
  }
  Serial.println(" OK");

  
  
  mySerial.println("AT+HTTPINIT");
  delay(500);
  mySerial.println("AT+HTTPPARA=CID,1");
  delay(500);


  Serial.println("Kirim data");
  Serial.println("AT+HTTPPARA=URL,(your server link+path API GET)" + String(latt,10) + "(part of path API GET)" + String(longg,10));
mySerial.println("AT+HTTPPARA=URL,(your server link+path API GET)" + String(latt,10) + "(part of path API GET)" + String(longg,10));
 mySerial.println("AT+HTTPACTION=0");
  delay(15000);
 mySerial.println("AT+HTTPTERM");
  delay(500);
 mySerial.println("AT+SAPBR=0,1");
delay(500);
  mySerial.println("AT+CGNSTST=1");
}
}
 
  
 


