/*
AT28C16 EEPROM Programmer
(C) Frederic Torres 2018
*/
#include <fArduino.h>
#include "EEPROM_Programmer.h"

void EEPROM_Programmer::Init() {

	// By default we are always in read mode
	pinMode(EEPROM_OUTPUT_ENABLE, OUTPUT);
	pinMode(EEPROM_WRITE_ENABLE, OUTPUT);
	this->SetOutputEnable();

	Board.Trace("EEPROM_Programmer Initialization");
	this->_dataMode = DATA_MODE::READ;
	this->SetPinsForAddressBus8Bits();
	this->SetAddressBus8bits(0);
	this->SetDataBusPinsForWriteMode();
	this->SetDataBusWriteData(0);
}
EEPROM_Programmer::EEPROM_Programmer() {

}
EEPROM_Programmer::~EEPROM_Programmer() {

}

void EEPROM_Programmer::CheckForReadMode()
{
	if (this->_dataMode != DATA_MODE::READ)
		this->SetDataBusPinsForReadMode();
}

void EEPROM_Programmer::CheckForWriteMode()
{
	if (this->_dataMode != DATA_MODE::WRITE)
		this->SetDataBusPinsForWriteMode();
}

void EEPROM_Programmer::SetDataBusWriteData(byte data)
{
	this->DataValue = data;
	this->CheckForWriteMode();
	for (int pin = EEPROM_D0; pin <= EEPROM_D7; pin += 1)
	{
		byte bit = data & 1;
		digitalWrite(pin, bit);
		data = data >> 1;
	}
}

void EEPROM_Programmer::SetDataBusAndAddressBus8bitWriteData(byte data, byte addr) {
	this->SetAddressBus8bits(addr);
	this->SetDataBusWriteData(data);
}

void EEPROM_Programmer::SetDataBusPinsForReadMode()
{
	this->_dataMode = DATA_MODE::READ;
	for (int pin = EEPROM_D0; pin <= EEPROM_D7; pin += 1)
	{
		pinMode(pin, INPUT);
	}
}

void EEPROM_Programmer::SetDataBusPinsForWriteMode()
{
	this->_dataMode = DATA_MODE::WRITE;
	for (int pin = EEPROM_D0; pin <= EEPROM_D7; pin += 1)
	{
		pinMode(pin, OUTPUT);
		digitalWrite(pin, LOW);
	}
}


void EEPROM_Programmer::SetPinsForAddressBus8Bits()
{
	for (int pin = EEPROM_A0; pin <= EEPROM_A7; pin += 1)
	{
		pinMode(pin, OUTPUT);
		digitalWrite(pin, LOW);
	}
}

void EEPROM_Programmer::SetAddressBus8bits(byte addr8bit) {
	this->AddrValue = addr8bit;
	for (int pin = EEPROM_A0; pin <= EEPROM_A7; pin += 1)
	{
		byte bit = addr8bit & 1;
		digitalWrite(pin, bit);
		addr8bit = addr8bit >> 1;
	}
}

String EEPROM_Programmer::GetStatus() {
	String s = "Mode:";
	if (this->_dataMode == DATA_MODE::READ)
		s.concat("Read, ");
	else
		s.concat("Write, ");

	String ss = StringFormat.Format("Data:%d, Addr:%d", this->DataValue, this->AddrValue);
	s.concat(ss);
	return s;
}


void EEPROM_Programmer::AnimationStartSequence() {
	int wait = 125;
	this->SetDataBusAndAddressBus8bitWriteData(255, 255);
	delay(wait);
	for (int i = 0; i < 4; i++) {
		this->SetDataBusAndAddressBus8bitWriteData(0, 255);
		delay(wait);
		this->SetDataBusAndAddressBus8bitWriteData(255, 0);
		delay(wait);
	}
	this->SetDataBusAndAddressBus8bitWriteData(0, 0);
	delay(wait * 4);
}

void EEPROM_Programmer::AnimationWorkProperlySequence() {
	int wait = 250;
	this->SetDataBusAndAddressBus8bitWriteData(1, 1);
	delay(wait);
	for (int i = 0; i < 8; i++) {
		this->SetDataBusAndAddressBus8bitWriteData(this->DataValue << 1, this->AddrValue << 1);
		delay(wait);
	}
	this->SetDataBusAndAddressBus8bitWriteData(0, 0);
}

void EEPROM_Programmer::SetOutputEnable() {
	digitalWrite(EEPROM_OUTPUT_ENABLE, LOW); // Active Low
	digitalWrite(EEPROM_WRITE_ENABLE, HIGH); // Active Low, no write operation
	this->SetDataBusPinsForReadMode();
}
void EEPROM_Programmer::InitiateWriteByteOperation() {

	digitalWrite(EEPROM_OUTPUT_ENABLE, HIGH); // Output disable 
	digitalWrite(EEPROM_WRITE_ENABLE, LOW); // Write enable

	cli(); sei(); // delayMicroseconds(1);
	//_delay_us(300);
	//asm("nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;");   
	delay(50);

	this->SetOutputEnable();
}