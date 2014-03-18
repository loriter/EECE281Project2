#include <stdio.h>
#include <math.h>
#include <stdlib.h>
//#include <dos.h>
#include <at89lp828.h>

// Left Wheel: Forward = 3.2 ON 3.3 Off Backward = 3.2 Off 3.3 ON
// Right Wheel Forward = 3.4 ON 3.5 OFF Backward = 3.4 Off 3.5 ON

#define CLK 3686400L
#define BAUD 115200L
#define TIMER_2_RELOAD (0x10000L-(CLK/(16L*BAUD)))
#define FREQ 100L
#define TIMER0_RELOAD_VALUE (65536L-(CLK/FREQ))

//#define RequiredDistance 2.0 // Sets the distance to be 2 meters ( for now )
#define MOVEMENTSPEED 10 // 10 cm/s
#define TURNSPEED	1	 // Angle / s
double RequiredDistance =1; // Sets the distance to be 2 meters ( for now )
double RequiredAngle = 90;

double x=0,y=0;

void startupTest(void); //test the circuit before beginning

double DetermineDistanceToSignal( void ); // FINISH FINDING IF WE NEED PARAMETERS

double DetermineAngleToSignal( void ); // FINISH FINDING IF WE NEED PARAMETERS

void MoveForward(void); // Turns on wheels

void MoveBackward ( void );

void MoveDistance( double DistanceToSignal ); // Moves a certain distance in the forward direction

void StopMoving( void );     // Stops the tether from moving

void TurnRight( void );      // Only turns on LEFT wheel to turn right

void TurnLeft( void );       // Only turns on RIGHT wheel to turn left

void TurnAway( double AngleToSignal );     // Takes angle to signal and turns until it is facing away

void TurnTo( double AngleToSignal);      // Takes angle to signal and turns until it is facing away

void increaseDistance( void );

void decreaseDistance( void );
 
void ProperAnglePosition (double AngleToSignal);	//move the car to the proper angle

double CalculateDistanceMoveTime(double DistanceToSignal);
double CalculateAngleMoveTime(double DifferenceInAngle);
//Some functions that will help in finding the Distance as well as the Angle

void SPIWrite (unsigned char value);
unsigned int GetADC (unsigned char channel);
void delay (void);
void testDelay(void);
double GetFreq (void);
double TestFreq (void);
double GetPhase (void);
unsigned int GetPeriod (void);

double PhaseDifference(void); //  This one is still buggy and doesnt full work.
double Period(void); //  Returns the period in us.
double ReferenceVoltage(void);//Gets the peak voltage for the reference signal.
							  //We might have to change some channels for the getADC part.
							  //We can use these functions to help us get the distance.
double SignalVoltage(void);   //Same as above function except for the signal voltage. 


int main( void )
{
	
    int running = 1;     // Keeps the program running
     //setbaud_timer2(TIMER_2_RELOAD); // Initialize the timer
     
     double DistanceToSignal,     // Determines the distance the tether is from the signal
            AngleToSignal;        // Determines what angle the signal is in relation to the tether's right side
     
	 startupTest(); //test the circuit before beginning

     //Nested while loops ensure that the car is in lined up before moving forward or back
     //IMPORTANT: This is assuming that when you change the angle of the car the signal will also change the distance factor
     
     setbaud_timer2(TIMER_2_RELOAD);
     
     while( running )
          {
               // Determine distance and angle function
               AngleToSignal = DetermineAngleToSignal();
               DistanceToSignal = DetermineDistanceToSignal();
               
               while( (abs(SignalVoltage()-ReferenceVoltage()) < 0.2)&&(SignalVoltage() > 0.05) )
               
                    {
                    	StopMoving();
                    	DistanceToSignal = DetermineDistanceToSignal();
                    	
                    		//IMPORTANT: This is assuming that when you change the angle of the car the signal will also change the distance factor
                          while( ( DistanceToSignal > (RequiredDistance +0.2 )) || (  DistanceToSignal < (RequiredDistance-0.2) ) )	{
                          
		                          MoveDistance( DistanceToSignal );     // Moves a distance towards the tether distance
		                          //delay();
				
		                          DistanceToSignal = (ReferenceVoltage() + SignalVoltage())/2;
		                    }
                          
                          StopMoving();
                          //AngleToSignal = DetermineAngleToSignal();//end of while loop to keep or break the conditions
                    }
                          
                if(ReferenceVoltage() < SignalVoltage() )
                {
                	while(((SignalVoltage()-ReferenceVoltage()) > 0.2) ){
              		TurnLeft();
              		}
              		
              		StopMoving();
              	}
              	else if (SignalVoltage()< ReferenceVoltage())
              	{
              		while(( (ReferenceVoltage() -SignalVoltage()) >0.2)){
              		TurnRight();
              		}
              		
              		StopMoving();
              	}  
                        
                
                else if(((abs(SignalVoltage()-ReferenceVoltage())) < 0.2) && (SignalVoltage() < 0.05 ))
                {
                	while((SignalVoltage() < 0.1) &&(ReferenceVoltage() <0.1)){
                	TurnRight();   
                	}
                	
                	StopMoving();
                
                }
                
                
               //ProperAnglePosition(AngleToSignal); //move vehicle to proper angle
               
               if (P2_6 == 0) //increase distance (top left botton pin)
               		RequiredDistance += 0.5;
               		//increaseDistance();
               if (P2_7 == 0) //decrease distance (second pin from top left)
           			if (RequiredDistance <= 0.5)
           				RequiredDistance -= 0.5;
           			//decreaseDistance();
          }
     return 0;
}

void startupTest(void){
	
	MoveForward();
	testDelay();
	StopMoving();
    MoveBackward();
	testDelay();
	StopMoving();
    TurnRight();
	testDelay();
	StopMoving();
    TurnLeft(); 
	testDelay();
	StopMoving();
}

void MoveForward( void )
{
	P3_2 = 1;
	P3_3 = 0;
	P3_4 = 0;
	P3_5 = 1;

	P1_1 = 1;	// Front On
	P2_0 = 0;	// Left off
	P1_0 = 0;	// Back off
	P3_7 = 0;	// Right off
}

void MoveBackward( void )
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

void StopMoving( void )
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

void TurnRight( void )
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

void TurnLeft( void )
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

void MoveDistance( double DistanceToSignal )
     {
          
          if( DistanceToSignal > RequiredDistance )
	              {
	                   MoveForward();// Move towards the signal
	                   //delay( MovementTimeRequired);//this might have to be inside the moving functions
					   //StopMoving();
	              }
	         else if( DistanceToSignal < RequiredDistance )
	              {
	              	   MoveBackward();// Move away from signal
	                   //delay( MovementTimeRequired);//this might have to be inside the moving functions
					   //StopMoving();
	              }
	                  
     }

void TurnTo( double AngleToSignal )
{
	if( (AngleToSignal > 90) && (AngleToSignal < 180 ))
	{
		TurnRight();
		StopMoving();
	}
	else if ( ((AngleToSignal < 90)&&(AngleToSignal > 0)) || (AngleToSignal > 180 ))
	{
		TurnLeft();
		StopMoving();
	}
}   

          
void ProperAnglePosition( double AngleToSignal) {
		double DifferenceInAngle,
               MovementTimeRequired;
          
		//following if statement for the car to be facing the tramsitter
		  if(AngleToSignal > 90)
			//turn right
			DifferenceInAngle = (AngleToSignal - RequiredAngle);
		  else if (AngleToSignal < 90)
			//turn left
			DifferenceInAngle = (RequiredAngle - AngleToSignal);

		  MovementTimeRequired = CalculateAngleMoveTime(DifferenceInAngle);

          TurnTo(AngleToSignal);// left and right may need to be swapped
                		              
	}   
	
double CalculateDistanceMoveTime(double DistanceToSignal){

		return (abs(DistanceToSignal - RequiredDistance) / MOVEMENTSPEED);
		//some shit that looks at the amplitude and phases and periods and shit
	}
	
double CalculateAngleMoveTime(double DifferenceInAngle){
		//car is facing the tramsitter
		return (DifferenceInAngle/TURNSPEED*1000); //assumming the time is in Seconds
	}
	

double DetermineDistanceToSignal( void )
{

//	return (SignalVoltage() + ReferenceVoltage())/2;
	return SignalVoltage();
}

double DetermineAngleToSignal( void )
{
	return 90; //For testing, just tells it that its always in the right angle.
}
	
double GetPhase (void)
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

unsigned int GetPeriod (void)
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

double GetFreq (void)
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

unsigned int GetADC (unsigned char channel)
{
	unsigned int adc;
	
	SSIG=1;
	SPCR=SPE|MSTR|CPOL|CPHA|SPR1|SPR0;
	P1_4=0;
	SPIWrite(0X01);
	SPIWrite((channel*0x10)|0x80);
	adc=((SPDR & 0x03)*0x100);
	SPIWrite(0x55);
	adc+=SPDR;
	P1_4=1;
	
	return adc;
}

void SPIWrite (unsigned char value)
{
	SPIF=0;
	SPDR=value;
	while (SPIF==0);
}

double PhaseDifference(void)
{ 
	return (GetPhase()*360.0/GetPeriod());
}

double Period(void)
{ 	
	return ((GetPeriod()*271.e-3));
}

double ReferenceVoltage(void)
{
	return ((5.*GetADC(0))/1023.);
}

double SignalVoltage(void)
{
	return ((5.*GetADC(1))/1023.);
}
