#include "Encoder.h"

DBlock * currentBlock = new DBlock;

int SDblock = 5;

int Blockstelle = 0;

encD * redptr ;

void EncoR (){
	redptr->R ++;
}

void EncoL (){
	redptr->L ++;
}



uint8_t wait4r(){
	digitalWrite(LED_BUILTIN, HIGH);
	uint8_t resp;
	do{
		resp = SPI.transfer(0xff);
	}while(resp == 0xff);
	digitalWrite(LED_BUILTIN, LOW);
	return resp;
}

void initSD(){
	SPISettings SPIset(200000, MSBFIRST, SPI_MODE0);
	SPI.beginTransaction(SPIset);
	SPI.begin();
	
	pinMode(nss, OUTPUT);
	digitalWrite(nss, HIGH);
	

	for(int i=0; i == 5;i++) SPI.transfer16(0xffff);

	//Software Reset
	digitalWrite(nss, LOW);
	SPI.transfer(0xffff);

	SPI.transfer(0x40);
	SPI.transfer16(0x0000);
	SPI.transfer16(0x0000);
	SPI.transfer(0x95);

	wait4r();

	delay(4000);
	
	do{
		delay(1000);
		//cmd55
		SPI.transfer(0x77);
		SPI.transfer16(0x0000);
		SPI.transfer16(0x0000);
		SPI.transfer(0x01);
	
		//acmd41
		SPI.transfer(0x69);
		SPI.transfer16(0x4000);
		SPI.transfer16(0x0000);
		SPI.transfer(0x01);
	}while(wait4r() != 0x00);

	SPI.setClockDivider(21);
}

void sendsbSD(DBlock * Data){
	while(SPI.transfer(0xff) == 0);//wait until not busy

	//cmd24
	SPI.transfer(0x58);
	SPI.transfer16(0x0000);
	SPI.transfer16(SDblock);
	SPI.transfer(0x00);
	
	wait4r();
	SPI.transfer(0x00);
	
	//Data Packet
	SPI.transfer(0xfe);
	SPI.transfer(Data, 512);
	SPI.transfer16(0x0000);

	if(( 0b00011111 & SPI.transfer(0xff)) != 0b00101) /*bad*/;
	
	delete Data;
	SDblock++;

}

void TC7_Handler()
{
	// We need to get the status to clear it and allow the interrupt to fire again
	TC_GetStatus(TC2, 1);
	
	if(Blockstelle < encWerte){
		redptr = &(currentBlock->enc[Blockstelle]);
	}else{
		//neuen Block erstellen
		DBlock * DBtempPtr = new DBlock;

		//Blöcke verknüpfen
		currentBlock->ptrN = DBtempPtr;
		DBtempPtr->ptrP = currentBlock;

		//sendsbSD(currentBlock);

		//aktuellen Block auswechseln
		currentBlock = DBtempPtr;

		Blockstelle = 0;

		redptr = &(currentBlock->enc[Blockstelle]);
	}
	Blockstelle ++;
}

void TimerInit(){
	//von http://2manyprojects.net/timer-interrupts
	
	/* turn on the timer clock in the power management controller */
	pmc_set_writeprotect(false);		 // disable write protection for pmc registers
	pmc_enable_periph_clk(ID_TC7);	 // enable peripheral clock TC7
	
	/* we want wavesel 01 with RC */
	TC_Configure(/* clock */TC2,/* channel */1, TC_CMR_WAVE | TC_CMR_WAVSEL_UP_RC | TC_CMR_TCCLKS_TIMER_CLOCK4); 
	TC_SetRC(TC2, 1, 65600);
	TC_Start(TC2, 1);
	
	// enable timer interrupts on the timer
	TC2->TC_CHANNEL[1].TC_IER=TC_IER_CPCS;   // IER = interrupt enable register
	TC2->TC_CHANNEL[1].TC_IDR=~TC_IER_CPCS;  // IDR = interrupt disable register
	
	/* Enable the interrupt in the nested vector interrupt controller */
	/* TC4_IRQn where 4 is the timer number * timer channels (3) + the channel number (=(1*3)+1) for timer1 channel1 */
	NVIC_EnableIRQ(TC7_IRQn);
}

