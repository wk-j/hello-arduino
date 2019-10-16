#ifndef _CAR_BLUETOOTH_H
#define _CAR_BLUETOOTH_H

#include <SoftwareSerial.h>   //Software Serial Port
#include <String.h>
#include <Arduino.h>


//status macro
#define INITIALIZING 0
#define READY        1
#define INQUIRING    2
#define PAIRABLE     3
#define CONNECTING   4
#define CONNECTED    5



//the commands that the bluetooth module get from remote control system such as andoid phone

class CarBluetooth
{
  private:
    SoftwareSerial bluetoothSerial;
	int8_t status;
	String s_connecting;
    String s_connected;
  public:
  	CarBluetooth(int rx, int tx);
	void waitConnected();
	bool renameBLE(String name);
	bool renameSPP(String name);
	bool reset();
	void clearBuffer();
	bool writeAT(String cmd);
	bool testAT();
	char readByte();
	int8_t getStatus();
	
};

#endif
