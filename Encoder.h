#pragma once

#include "Arduino.h"
#include "SPI.h"
#include "SD.h"


const int encWerte = 248;

struct encD {
	int R;
	int L;
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
