#pragma once

#include "Arduino.h"
#include "SPI.h"
#include "SD.h"


const int encWerte = 252;

struct encD {
	uint8_t R;
	uint8_t L;
};

struct DBlock{
	DBlock * ptrP;
	encD enc[encWerte];
	DBlock * ptrN;
};

//DBlock * currentBlock ;//= new DBlock;


void EncoR();
void EncoL();

void initSD();

void TimerInit();
