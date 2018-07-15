/*
	AT28C16 EEPROM Programmer 
	(C) Frederic Torres 2018

	based on `Build an Arduino EEPROM programmer`
	By Ben Eater
	https://www.youtube.com/watch?v=K88pgWhEb1M

	https://github.com/beneater/eeprom-programmer

*/
#include <fArduino.h>
#include "EEPROM_Programmer.h"

#define APP_TITLE  "AT28C16 EEPROM Programmer Application"

#define ON_BOARD_LED 13
Led _onBoardLed(ON_BOARD_LED);
EEPROM_Programmer ep;

#define MAX_ADDR 16

void WriteEEPROM() {
	Board.Trace("About to Write EEPROM Sequence");
	delay(1000 * 1);
	Board.Trace("Writing EEPROM Sequence...");
	int baseValue = 1;

	for (int addr = 0; addr < MAX_ADDR; addr++) {

		ep.SetAddressBus8bits(addr);
		int val = addr;
		if (addr % 2 == 0) {
			val = 6;
		}
		else {
			val = 14;
		}
		
		ep.SetDataBusWriteData(val);
		Board.Trace(ep.GetStatus());
		Board.Trace("About to initiate the write op");
		delay(100);
		ep.InitiateWriteByteOperation();
		delay(100);
	}
	Board.Trace("Write EEPROM Sequence Done");
	Board.Trace("");
}

void ReadEEPROM() {
	Board.Trace("About to Read EEPROM Sequence");
	delay(1000 * 2);
	Board.Trace("Reading EEPROM Sequence...");
	int baseValue = 1;

	for (int addr = 0; addr < MAX_ADDR; addr++) {

		ep.SetAddressBus8bits(addr);		
		ep.GetDataBusReadData();
		Board.Trace(ep.GetStatus());
		delay(150);
	}
	Board.Trace("Read EEPROM Sequence Done");
	Board.Trace("");
}

void setup() {
	Board.SetPinMode(ON_BOARD_LED, OUTPUT);
	_onBoardLed.SetBlinkMode(250);

	Board.InitializeComputerCommunication(115200, APP_TITLE);
	Board.Trace("Initializing...");
	ep.Init();
	/*
	Board.Trace("AnimationStartSequence...");
	ep.AnimationStartSequence();
	Board.Trace("AnimationWorkProperlySequence...");
	ep.AnimationWorkProperlySequence();
	*/

//	WriteEEPROM();

	//Board.Trace(ep.GetStatus());
	//ep.SetAddressBus8bits(0);
	//ep.SetDataBusWriteData(0); // data gpios are in output mode and low
	//ep.SetOutputEnable();
	//delay(2001);
	//ep.SetOutputDisable();
}

void loop() {
	ReadEEPROM();
}