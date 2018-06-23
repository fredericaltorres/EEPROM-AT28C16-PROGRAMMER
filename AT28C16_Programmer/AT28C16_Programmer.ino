/*

*/

#include <fArduino.h>
#include "EEPROM_Programmer.h"

#define APP_TITLE  "AT28C16 EEPROM Programmer Application"

#define ON_BOARD_LED 13

Led _onBoardLed(ON_BOARD_LED);

#define TEST_LED 22
Led _testLed(TEST_LED);

EEPROM_Programmer ep;

void WriteEEPROM() {
	Board.Trace("About to Write EEPROM Sequence");
	delay(1000 * 4);
	Board.Trace("Writing EEPROM Sequence...");

	for (int addr = 0; addr < 256; addr++) {
		ep.SetAddressBus8bits(addr);
		ep.SetDataBusWriteData(addr);
		ep.InitiateWriteByteOperation();
		Board.Trace(ep.GetStatus());
		delay(100);
	}
	Board.Trace("Write EEPROM Sequence Done");
}

// the setup function runs once when you press reset or power the board
void setup() {
	// initialize digital pin 13 as an output.
	pinMode(TEST_LED, OUTPUT);
	pinMode(ON_BOARD_LED, OUTPUT);
	Board.SetPinMode(ON_BOARD_LED, OUTPUT);
	_onBoardLed.SetBlinkMode(250);
	_testLed.SetBlinkMode(100);

	Board.InitializeComputerCommunication(115200, APP_TITLE);
	Board.Trace("Initializing...");
	ep.Init();
	ep.AnimationStartSequence();
	ep.AnimationWorkProperlySequence();
	WriteEEPROM();
}


void loop() {

}