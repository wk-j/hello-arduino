#include "car_bluetooth.h"

CarBluetooth::CarBluetooth(int rx, int tx): bluetoothSerial(rx,tx){
  s_connecting = "CONNECTING";
  s_connected  = "CONNECTED";
  status = 0;
  bluetoothSerial.begin(9600);
}

void CarBluetooth::waitConnected(){
  char recvChar;
  while(status != CONNECTED){
    
		if(testAT()) status = PAIRABLE;
		else{ 
			delay(200);
			if(testAT()) status = PAIRABLE;
			else status = CONNECTED;
		}
  }
}
bool CarBluetooth::renameBLE(String name){
  clearBuffer();
  String renameCmd;
  renameCmd = "AT+NAME";
  renameCmd += name;
  return writeAT(renameCmd);
}
bool CarBluetooth::renameSPP(String name){
  clearBuffer();
  String renameCmd;
  renameCmd = "AT+NAMES";
  renameCmd += name;
  return writeAT(renameCmd);
}

bool CarBluetooth::reset(){
  clearBuffer();
  return writeAT("AT+RST");
 
}

/*Clear the receiver buffer of the bluetooth serial object*/
void CarBluetooth::clearBuffer(){
  char recvChar;
  while(bluetoothSerial.available())recvChar = bluetoothSerial.read();
}

/*Write AT command to bluetooth module*/
bool CarBluetooth::writeAT(String cmd){
  bluetoothSerial.println(cmd);
  delay(500);
  if(bluetoothSerial.available() > 1){
    String recvString;
	char recvChar;
	recvChar = bluetoothSerial.read();
    recvString += recvChar;
    recvChar = bluetoothSerial.read();
    recvString += recvChar;
    if(recvString == "OK")return true;
    else return false;
  }
  else return false;
}
bool CarBluetooth::testAT(){
  clearBuffer();
  return writeAT("AT+RST");
}


char CarBluetooth::readByte(){
  if(status != CONNECTED) return 0xff;
  if(bluetoothSerial.available())
  {
  	char recvChar;
	recvChar = bluetoothSerial.read();
  	return recvChar;
  }
  else return 0xff;
}

int8_t CarBluetooth::getStatus(){
  return status;
}


