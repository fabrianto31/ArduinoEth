#include <SPI.h>
#include <Ethernet.h>
//Library Sensor DHT11
#include "DHT.h"
#define DHTPIN 5
#define DHTTYPE DHT11
//Library Sensor ACS712
#include "ACS712.h"
#define acsPIN 1
#define ACS712
//Library Sensor ZMPT101B
#include "ZMPT101B.h"
#define zmpt101bPIN 2
#define ZMPT101B 

DHT dht(DHTPIN, DHTTYPE);

//const int pinADC = A0;
int sensitivitas = 66; //tegantung sensor arus yang digunakan, yang ini 30A
float nilaiadc= 00;
int teganganoffset = 2500; //nilai pembacaan offset saat tidak ada arus yang lewat
float tegangan = 00;
float nilaiarus = 00;

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
byte ip[] = {192, 168, 0, 101 }; //Enter the IP of ethernet shield
byte serv[] = {192, 168, 0, 100} ; //Enter the IPv4 address
EthernetClient cliente;

void setup() {
Serial.begin(9600); //setting the baud rate at 9600
Ethernet.begin(mac, ip);
dht.begin();
delay(2000);
}

void data_olah(){
//Sensor ACS712
  nilaiadc = analogRead(acsPIN);
  tegangan = (nilaiadc / 1024.0) * 5000;
  nilaiarus = ((tegangan - teganganoffset) / sensitivitas);}
  
void loop() {
//Sensor DHT11
float hum = dht.readHumidity(); //Reading the humidity and storing in hum
float temp = dht.readTemperature(); //Reading the temperature as Celsius and storing in temp
float fah = dht.readTemperature(true); //reading the temperature in Fahrenheit
float heat_index = dht.computeHeatIndex(fah, hum); //Reading the heat index in Fahrenheit
float heat_indexC = dht.convertFtoC(heat_index); //Converting the heat index in Celsius


/*float nilaiadc = acs.readNilaiADC();
float tegangan = acs.readTegangan();
float arus = acs.readArus();*/

if (cliente.connect(serv, 80)) { //Connecting at the IP address and port we saved before
Serial.println("connected");
cliente.print("GET /ethernet/data.php?"); //Connecting and Sending values to database
//Data DHT
cliente.print("temperature=");
cliente.print(temp);
cliente.print("&humidity=");
cliente.print(hum);
cliente.print("&heat_index=");
cliente.println(heat_indexC);

data_olah();
//Data Arus
cliente.println("Nilai ADC=");
cliente.print(nilaiadc);
cliente.println("Tegangan=");
cliente.print(tegangan, 3);
cliente.println("Arus=");
cliente.print(nilaiarus, 3);

/*cliente.println("HTTP/1.1");
cliente.println("Host: 192, 168, 0, 102");
cliente.println();
cliente.println();*/

//Printing the values on the serial monitor
Serial.print("Temperature= ");
Serial.println(temp);
Serial.print("Humidity= ");
Serial.println(hum);
Serial.print("Heat Index= ");
Serial.println(heat_indexC);

data_olah();
Serial.print("Nilai ADC= ");
Serial.println(nilaiadc);
Serial.print("Tegangan= ");
Serial.println(tegangan,3);
Serial.print("Arus= ");
Serial.println(nilaiarus,3);

cliente.stop(); //Closing the connection
}
else {
// if you didn't get a connection to the server:
Serial.println("connection failed");
}
delay(5000);
}
