#include <stdio.h>
#include <stdlib.h>
#include <at89lp828.h>

#define CLK 3686400L
#define BAUD 115200L
#define TIMER_2_RELOAD (0x10000L-(CLK/(16L*BAUD)))

#define FREQ 15000L
#define TIMER0_RELOAD_VALUE (65536L-(CLK/(2L*FREQ)))

void InitTimer0 (void)
{
	// Initialize timer 0 for ISR 'pwmcounter' below
	TR0=0; // Stop timer 0
	TMOD=(TMOD&0xf0)|0x01; // 16-bit timer
	RH0=TIMER0_RELOAD_VALUE/0x100;
	RL0=TIMER0_RELOAD_VALUE%0x100;
	TR0=1; // Start timer 0 (bit 4 in TCON)
	ET0=1; // Enable timer 0 interrupt
	EA=1;  // Enable global interrupts
}


// Interrupt 1 is for timer 0.  This function is executed every time
// timer 0 overflows: 100 us.
void tx_frequency (void) interrupt 1
{
	if(P2_0==0)
	{
	 P2_0=1;
	 P2_1=0;
	}
	else
	{
	 P2_1=1;
	 P2_0=0;
	}
}
 
int test (unsigned char testNum) {
	if(testNum>100 || testNum<1) return 1;
	return 0;
}

void main (void)
{
	unsigned int f=15000, reload;
    setbaud_timer2(TIMER_2_RELOAD); // Initialize serial port using timer 2 
	InitTimer0(); // Initialize timer 0 and its interrupt
	printf("\nFrequency test program\n");
	while(1)
	{	
		printf( "\rf(%5d)=       \b\b\b\b\b\b\b", f );
		scanf("%ud",&f);
		reload=65536L-(CLK/(2L*f));
		RH0=reload/0x100;
		RL0=reload%0x100;
	}		
}

