#include <stdio.h>
#include <stdlib.h>
#include <at89lp51rd2.h>

#define CLK 22118400L
#define BAUD 115200L
#define BRG_VAL (0x100-(CLK/(32L*BAUD)))

#define FREQ 10000L
#define TIMER0_RELOAD_VALUE (65536L-(CLK/(12L*FREQ)))

unsigned char _c51_external_startup(void)
{
	// Configure ports as a bidirectional with internal pull-ups.
	P0M0=0;	P0M1=0;
	P1M0=0;	P1M1=0;
	P2M0=0;	P2M1=0;
	P3M0=0;	P3M1=0;
	AUXR=0B_0001_0001; // 1152 bytes of internal XDATA, P4.4 is a general purpose I/O
	P4M0=0;	P4M1=0;
    
    // Initialize the serial port and baud rate generator
    PCON|=0x80;
	SCON = 0x52;
    BDRCON=0;
    BRL=BRG_VAL;
    BDRCON=BRR|TBCK|RBCK|SPD;
	
	// Initialize timer 0 for ISR 'pwmcounter()' below
	TR0=0; // Stop timer 0
	TMOD=0x01; // 16-bit timer
	// Use the autoreload feature available in the AT89LP51RB2
	// WARNING: There was an error in at89lp51rd2.h that prevents the
	// autoreload feature to work.  Please download a newer at89lp51rd2.h
	// file and copy it to the crosside\call51\include folder.
	TH0=RH0=TIMER0_RELOAD_VALUE/0x100;
	TL0=RL0=TIMER0_RELOAD_VALUE%0x100;
	TR0=1; // Start timer 0 (bit 4 in TCON)
	ET0=1; // Enable timer 0 interrupt
	EA=1;  // Enable global interrupts
    
    return 0;
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

