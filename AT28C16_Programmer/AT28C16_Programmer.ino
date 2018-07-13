/*
	AT28C16 EEPROM Programmer 
	(C) Frederic Torres 2018
*/
#include <fArduino.h>
#include "EEPROM_Programmer.h"

#define APP_TITLE  "AT28C16 EEPROM Programmer Application"

#define ON_BOARD_LED 13
Led _onBoardLed(ON_BOARD_LED);
EEPROM_Programmer ep;

void WriteEEPROM() {
	Board.Trace("About to Write EEPROM Sequence");
	delay(1000 * 4);
	Board.Trace("Writing EEPROM Sequence...");
	int baseValue = 1;

	for (int addr = 0; addr < 8; addr++) {
		ep.SetAddressBus8bits(addr);

		int val = baseValue << addr;
		ep.SetDataBusWriteData(val);

		ep.InitiateWriteByteOperation();
		Board.Trace(ep.GetStatus());
		delay(1000);
	}
	Board.Trace("Write EEPROM Sequence Done");
	Board.Trace("");
}

void ReadEEPROM() {
	Board.Trace("About to Read EEPROM Sequence");
	delay(1000 * 4);
	Board.Trace("Reading EEPROM Sequence...");
	int baseValue = 1;

	for (int addr = 0; addr < 8; addr++) {

		ep.SetAddressBus8bits(addr);
		ep.GetDataBusReadData();
		Board.Trace(ep.GetStatus());
		delay(1000);
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
	Board.Trace("AnimationStartSequence...");
	ep.AnimationStartSequence();
	// Board.Trace("AnimationWorkProperlySequence...");
	// ep.AnimationWorkProperlySequence();
	// WriteEEPROM();
	Board.Trace(ep.GetStatus());
}


void loop() {
	ReadEEPROM();
}