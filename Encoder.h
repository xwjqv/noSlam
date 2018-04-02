#pragma once

#include "Arduino.h"
#include "SPI.h"

const int nss=11; //Slave select

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
