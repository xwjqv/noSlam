#pragma once

#include "Arduino.h"

const int encWerte = 510;

struct encD {
	int R;
	int L;
};

struct DBlock{
	DBlock * ptrP;
	encD enc[encWerte];
	DBlock * ptrN;
};

static DBlock * currentBlock;


void EncoR();
void EncoL();

void TimerInit();
