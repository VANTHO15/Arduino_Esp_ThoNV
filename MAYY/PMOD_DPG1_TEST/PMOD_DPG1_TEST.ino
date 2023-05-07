/************************************************************************
*
* Test of Pmod DPG1
*
*************************************************************************
* Description: Pmod_DPG1
* The pressure is displayed on the serial monitor.
*
*
* Material
* 1. Arduino Uno
* 2. Pmod DPG1
* 3. Adafruit module TXB0108
*
* Shématic
* Module<----------> TXB0108 <-----------> Arduino
* J1 broche 6 3.3 V
* J1 broche 5 GND
* J1 broche 4 13
* J1 broche 3 12
* J1 broche 1 10
*
************************************************************************/

#define CS 53 // Assignment of the CS pin

#include <SPI.h> // call library

int i;
byte recu[3]; // Storage of module data
int valeur;
float pression;

void setup()
{
 Serial.begin(9600); // initialization of serial communication
 SPI.begin(); // initialization of SPI port
 SPI.setDataMode(SPI_MODE0); // configuration of SPI communication in mode 0
 SPI.setClockDivider(SPI_CLOCK_DIV16); // configuration of clock at 1MHz
 pinMode(CS, OUTPUT);
}

void loop()
{
 digitalWrite(CS, LOW); // activation of CS line
 delayMicroseconds(20);
 for (i=0;i<2;i=i+1)
    {
    recu[i] = SPI.transfer(0); // Sending 2 data to retrieve the value of the two -byte conversion
    delayMicroseconds(20);
    }
 digitalWrite(CS, HIGH); // deactivation of CS line
 valeur = (recu[0] << 8|recu[1]);

 pression=(valeur/4096.0-0.08)/0.09; // The form given by the documentation

 float numerator = (2*(pression))/1.128 ;
 float velocity = (numerator)*0.5;
 
 Serial.print("Velocity =");
 Serial.print(velocity);
 Serial.println(" m/s");  
 delay(1000);
}
