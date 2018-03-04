#include "Encoder.h"

int Blockstelle = 0;

encD * redptr ;

void EncoR (){
	redptr->R ++;
}

void EncoL (){
	redptr->L ++;
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

