#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <at89lp51rd2.h>

#define LWP P3_2
#define LWN P3_3
#define RWP P3_4
#define RWN p3_5

#define CLK 22118400L
#define BAUD 115200L
#define BRG_VAL (0x100L-(CLK/(32L*BAUD)))
#define FREQ 100L
#define TIMER0_RELOAD_VALUE (65536L-(CLK/(12L*FREQ)))

#define MOVEMENTSPEED 10 // 10 cm/s
#define TURNSPEED	1	 // Angle / s

double requiredDistance = 1; // Sets the default distance to be roughly 2 meters
//This can be set to a different distance manually
double requiredAngle = 90; //The angle the robot needs to be

//double x=0,y=0;

void startupTest(void); //Tests that the motors and circuit are working properly

unsigned char recieveCommand( int min );

void waitOneAndHalfBitTime( void );

void waitBitTime( void );

double determineDistanceToSignal( void ); // FINISH FINDING IF WE NEED PARAMETERS

double determineAngleToSignal( void ); // FINISH FINDING IF WE NEED PARAMETERS
//**TODO** complete this function - might just be phase shift

void moveForward(void); // Turns on wheels forward

void moveBackward ( void );

void moveDistance( double distanceToSignal ); // Moves designated distance forward

void stopMoving( void );     // Stops the motors from moving

void turnRight( void );      // Moves left wheel forward and right wheel backwards to turn right

void turnLeft( void );       // Moves right wheel forward and left wheel backwards to turn left 

void turnAway( double angleToSignal );     // Takes angle to signal and turns until it is facing away

void turnTo( double angleToSignal);      // Takes angle to signal and turns until it is facing away

void increaseDistance( void ); //Not used

void decreaseDistance( void ); //Not used
 
void properAnglePosition (double angleToSignal);	//move the car to the proper angle

double calculateDistanceMoveTime(double distanceToSignal);
double calculateAngleMoveTime(double differenceInAngle);
//Some functions that will help in finding the Distance as well as the Angle

void spiWrite (unsigned char value);
unsigned int getADC (unsigned char channel);

//Delay function, may have to rewrite
void delay (void);
void testDelay(void);

// Need to replace these with code from lab 5
double getFreq (void);
double testFreq (void);
double getPhase (void);
unsigned int getPeriod (void);

double phaseDifference(void); //  This one is still buggy and doesnt full work.
double period(void); //  Returns the period in us.

double referenceVoltage(void);//**TODO** Not correct, need to replace this.
							  //We can use these functions to help us get the distance.
double signalVoltage(void);  

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
    
    return 0;
    
}

int main( void )
{  
     
	double distanceToSignal,     // Determines the distance the tether is from the signal
			angleToSignal;        // Determines what angle the signal is in relation to the tether's right side
     
	startupTest(); //test the circuit before beginning

     //Nested while loops ensure that the car is in lined up before moving forward or back
     //IMPORTANT: This is assuming that when you change the angle of the car the signal will also change the distance factor
     
	while( 1 )  // Keeps the program running
	{
		// Determine distance and angle function
		angleToSignal = determineAngleToSignal();
		distanceToSignal = determineDistanceToSignal();
               
		while( (abs(signalVoltage()-referenceVoltage()) < 0.2)&&(signalVoltage() > 0.05) )
		{
			stopMoving();
			distanceToSignal = determineDistanceToSignal();
                    	
			//IMPORTANT: This is assuming that when you change the angle of the car the signal will also change the distance factor
			while( ( distanceToSignal > (requiredDistance +0.2 )) || (  distanceToSignal < (requiredDistance-0.2) ) )
			{
				moveDistance( distanceToSignal );     // Moves a distance towards the tether distance
				//delay();
				distanceToSignal = (referenceVoltage() + signalVoltage())/2;
			}
                          
			stopMoving();
			//AngleToSignal = DetermineAngleToSignal();//end of while loop to keep or break the conditions
		}
        //If the car isn't parallel with the transmitter, it turns to adjust itself till it's parallel                  
		if(referenceVoltage() < signalVoltage() )
		{
			while(((signalVoltage() - referenceVoltage()) > 0.2) )
			{
				turnLeft();
			}
              		
			stopMoving();
		}
		
		else if (signalVoltage() < referenceVoltage())
		{
			while(( (referenceVoltage()-signalVoltage()) > 0.2))
			{
				turnRight();
			}
              		
			stopMoving();
		}          
                
		else if(((abs(signalVoltage() - referenceVoltage())) < 0.2) && (signalVoltage() < 0.05 ))
		{
			while((signalVoltage() < 0.1) && (referenceVoltage() < 0.1))
			{
				turnRight();   
			}
                	
			stopMoving();
                
		}    
		//ProperAnglePosition(AngleToSignal); //move vehicle to proper angle
        
        
        //***TODO**** Tasks to be done.
        // **IDEA** Change transmitting frequency briefly as a command
        
        /* **May have to implement different functionality for tasks**
        //Task Move Farther
		if (P2_3 == 0)
		{
			RequiredDistance += 0.5;
               		//increaseDistance();
		}
		//Task Move Closer
		if (P2_4 == 0)
		{
			if (RequiredDistance <= 0.5)
			{
				RequiredDistance -= 0.5;
			}
           			//decreaseDistance();
		}
		//*TODO*: Task 180degrees
		if (P2_5 == 0)
		{
		}
		//*TODO*: Task Parallel Park
		if (P2_6 == 0)
		{
		}
		*/
	}

}

void startupTest(void)
{
	
	moveForward();
	testDelay();
	stopMoving();
    moveBackward();
	testDelay();
	stopMoving();
    turnRight();
	testDelay();
	stopMoving();
    turnLeft(); 
	testDelay();
	stopMoving();
}

void moveForward( void )
{
	P3_2 = 1;
	P3_3 = 0;
	P3_4 = 0;
	P3_5 = 1;


	//Unknown commands. Can be used for extra features.
	P1_1 = 1;	// Front On
	P2_0 = 0;	// Left off
	P1_0 = 0;	// Back off
	P3_7 = 0;	// Right off
}

void moveBackward( void )
{
	P3_2 = 0;
	P3_3 = 1;
	P3_4 = 1;
	P3_5 = 0;
	
	P1_1 = 0;	// Front on
	P2_0 = 0;	// Left off
	P3_7 = 0;	// Right off
	P1_0 = 1;	// Back on
}

void stopMoving( void )
{
	P3_2 = 0;
	P3_3 = 0;
	P3_4 = 0;
	P3_5 = 0;

	P1_1 = 0;	// Front off
	P2_0 = 0;	// Left off
	P1_0 = 0;	// Back off
	P3_7 = 0;	// Right off
}

void turnRight( void )
{
	P3_2 = 1;
	P3_3 = 0;
	P3_4 = 1;
	P3_5 = 0;

	P1_1 = 0;	// Front off
	P3_7 = 1;	// Right on
	P2_0 = 0;	// Left off
	P1_0 = 0;	// back off
}

void turnLeft( void )
{
	P3_2 = 0;
	P3_3 = 1;
	P3_4 = 0;
	P3_5 = 1;

	P1_1 = 0;	// Front off
	P2_0 = 1;	// Left on
	P1_0 = 0;	// back off
	P3_7 = 0;	// Right off
} 

unsigned char recieveCommand( int min )
{
	unsigned char i, val;
	int v;
	
	val = 0;
	waitOneAndHalfBitTime();
	for(i = 0; i < 3; i++)
	{
		v = signalVoltage(); //May need to change to find peak voltage
		val |= (v>min)?(0x01<<i):0x00;
		waitBitTime();
	}
	
	waitOneAndHalfBitTime();
	
	return val;
}

void waitOneAndHalfBitTime( void )
{
	//** TODO ** Implement same way as wait_bit_time in transmitter
}

void waitBitTime ( void )
{
	//** TODO ** Implement as above
}

void moveDistance( double distanceToSignal )
{
          
	if( distanceToSignal > requiredDistance )
	{
		moveForward();// Move towards the signal
		//delay( MovementTimeRequired);//this might have to be inside the moving functions
		//stopMoving();
	}
	else if( distanceToSignal < requiredDistance )
	{
		moveBackward();// Move away from signal
		//delay( MovementTimeRequired);//this might have to be inside the moving functions
		//stopMoving();
	}
	                  
}

void turnTo( double angleToSignal )
{
	if( (angleToSignal > 90) && (angleToSignal < 180 ))
	{
		turnRight();
		stopMoving();
	}
	else if ( ((angleToSignal < 90)&&(angleToSignal > 0)) || (angleToSignal > 180 ))
	{
		turnLeft();
		stopMoving();
	}
}   

          
void properAnglePosition( double angleToSignal)
{
	double differenceInAngle, movementTimeRequired;
          
	//following if statement for the car to be facing the tramsitter
	if(angleToSignal > 90)
	{
		//turn right
		differenceInAngle = (angleToSignal - requiredAngle);
	}
	else //**MaybeRequired**if (angleToSignal < 90)
	{
		//turn left
		differenceInAngle = (requiredAngle - angleToSignal);
	}

	movementTimeRequired = calculateAngleMoveTime(differenceInAngle);

	turnTo(angleToSignal);// left and right may need to be swapped
                		              
}   
	
double calculateDistanceMoveTime(double distanceToSignal)
{
	return (abs(distanceToSignal - requiredDistance) / MOVEMENTSPEED);
	//some shit that looks at the amplitude and phases and periods and shit
}
	
double calculateAngleMoveTime(double differenceInAngle)
{
	//Determines the time for the car to turn to face the transmitter
	return (differenceInAngle/TURNSPEED*1000); //assumming the time is in Seconds
}
	

double determineDistanceToSignal( void )
{

//	return (signalVoltage() + referenceVoltage())/2;
	return signalVoltage();
}

double determineAngleToSignal( void )
{
	//return 90; //For testing, just tells it that its always in the right angle.
	return phaseDifference();//**TODO** May not work, may require a fix.
}
	
double getPhase (void)
{
	double phase;
		
	TR0=0; 							// Stop timer 0
	TMOD=0B_0000_0001; 				// Set timer 0 as 16- // Set timer 0 as 16---bit timer bit timer
	TH0=0; TL0=0;					// Reset the timer
	while (P2_0==1); 	// Wait for the both signal to be zero
	while (P2_0==0); 				// Wait for the ref signal to be one
	TR0=1; 							// Start timing
	while (P3_7==0); 				// Wait for the test signal to be one
	TR0=0; 							// Stop timer 0
	// [TH0,TL0] is half the period in multiples of 271ns, so:
	phase=((TH0*0x100)+TL0); 		// Assume Period is unsigned int
	
	return phase;
}

unsigned int getPeriod (void)
{
	unsigned int period;
		
	TR0=0; 							// Stop timer 0
	TMOD=0B_0000_0001; 				// Set timer 0 as 16- // Set timer 0 as 16---bit timer bit timer
	TH0=0; TL0=0;					// Reset the timer
	while (P2_0==1); 				// Wait for the signal to be zero
	while (P2_0==0);				// Wait for the signal to be one
	TR0=1; 							// Start timing
	while (P2_0==1); 				// Wait for the signal to be zero
	TR0=0; 							// Stop timer 0
	// [TH0,TL0] is half the period in multiples of 271ns, so:
	period=((TH0*0x100)+TL0)*2; 	// Assume Period is unsigned int	

	return period;
}

double getFreq (void)
{
	unsigned int period;
		
	TR0=0; 							// Stop timer 0
	TMOD=0B_0000_0001; 				// Set timer 0 as 16- // Set timer 0 as 16---bit timer bit timer
	TH0=0; TL0=0;					// Reset the timer
	while (P2_0==1); 				// Wait for the signal to be zero
	while (P2_0==0); 				// Wait for the signal to be one
	TR0=1; 							// Start timing
	while (P2_0==1); 				// Wait for the signal to be zero
	TR0=0; 							// Stop timer 0
	// [TH0,TL0] is half the period in multiples of 271ns, so:
	period=((TH0*0x100)+TL0)*2; 	// Assume Period is unsigned int
		
	return 1.0/(period*271.e-9);
}

void delay (void) 
{ 
   volatile unsigned int j; //does this work?
   for (j=0; j<50000; j++); 
}

void testDelay(void){
	volatile unsigned int j;
    for (j=0; j<30000; j++); 
}

void spiWrite(unsigned char value)
{
	SPSTA&=(~SPIF); // Clear the SPIF flag in SPSTA
	SPDAT=value;
	while((SPSTA & SPIF)!=SPIF); //Wait for transmission to end
}

unsigned int getADC(unsigned char channel)
{
	unsigned int adc;

	// initialize the SPI port to read the MCP3004 ADC attached to it.
	SPCON&=(~SPEN); // Disable SPI
	SPCON=MSTR|CPOL|CPHA|SPR1|SPR0|SSDIS;
	SPCON|=SPEN; // Enable SPI
	
	P1_4=0; // Activate the MCP3004 ADC.
	spiWrite(channel|0x18);	// Send start bit, single/diff* bit, D2, D1, and D0 bits.
	for(adc=0; adc<10; adc++); // Wait for S/H to setup
	spiWrite(0x55); // Read bits 9 down to 4
	adc=((SPDAT&0x3f)*0x100);
	spiWrite(0x55);// Read bits 3 down to 0
	P1_4=1; // Deactivate the MCP3004 ADC.
	adc+=(SPDAT&0xf0); // SPDR contains the low part of the result. 
	adc>>=4;
	

		
	return adc;
}

double phaseDifference(void)
{ 
	return (getPhase()*360.0/getPeriod());
}

double period(void)
{ 	
	return ((getPeriod()*271.e-3));
}

double referenceVoltage(void)
{
	return ((5.*getADC(0))/1023.);
}

double signalVoltage(void)
{
	return ((5.*getADC(1))/1023.);
}
