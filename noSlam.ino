#include "Encoder.h"
#include "SPI.h"

const int PSR=2; //Pin Sensor Rechts
const int PSL=3; //Pin Sensor Links

const int PMR=4; //Pin Motor Rechts
const int PML=5; //Pin Motor Links

const int pwmR=6;
const int pwmL=7;

const int ER=8; //Encoder Rechts
const int EL=9; //Encoder Links


const int pwmDuty=0xaf; //x0 bedeutet hexadezimal

void setup()
{
	pinMode(LED_BUILTIN, OUTPUT);
	digitalWrite(LED_BUILTIN, LOW);

	initSD();
	
	//currentBlock = new DBlock;

	TimerInit();

	pinMode(PSR, INPUT);
	pinMode(PSL, INPUT);

	
	attachInterrupt(digitalPinToInterrupt(PSL), Lenkunglinks, CHANGE);
	attachInterrupt(digitalPinToInterrupt(PSR), Lenkungrechts, CHANGE);
	
	pinMode(PMR, OUTPUT);
	pinMode(PML, OUTPUT);
	
	pinMode(pwmR, OUTPUT);
	pinMode(pwmL, OUTPUT);

	analogWrite(pwmR, pwmDuty);
	analogWrite(pwmL, pwmDuty);

}

void loop()
{

}

void Lenkunglinks()
{
	if(digitalRead(PSL)== LOW){
		digitalWrite(PML, HIGH);
	}else{
		if(digitalRead(PSR)== LOW){
			digitalWrite(PML, LOW);
		}else{
			digitalWrite(PML, HIGH);
		}
	}

}

void Lenkungrechts()
{
	if(digitalRead(PSR)== LOW){
		digitalWrite(PMR, HIGH);
	}else{
		if(digitalRead(PSL)== LOW){
			digitalWrite(PMR, LOW);
		}else{
			digitalWrite(PMR, HIGH);
		}
	}

}

