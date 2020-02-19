#pragma config(Sensor, S2,     rightlinedetect, sensorEV3_Color)
#pragma config(Sensor, S3,     leftlinedetect, sensorEV3_Color)
#pragma config(Sensor, S4,     Ultrasonic,     sensorEV3_Ultrasonic)
#pragma config(Motor,  motorA,          claw,          tmotorEV3_Large, PIDControl, encoder)
#pragma config(Motor,  motorB,          rightmotor,    tmotorEV3_Large, PIDControl, reversed, encoder)
#pragma config(Motor,  motorC,          leftmotor,     tmotorEV3_Large, PIDControl, reversed, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//


/*
Things I need to fix:

Replace the Brick with another one
*/
int usvalue = 7;


//int taskNo = 1;
int blackR = 24; //Right Sensor (S2)
int blackL = 24; //Left Sensor (S3)
int silver = 65;
/*
void inverttile()
{
	while(true)
	{
		if(getColorReflected(S2)< blackR)
			{
			  if(getColorReflected(S3)< blackL)
				{
					setMotorSpeed(motorB,30);//double white
					setMotorSpeed(motorC,30);//forward
				}
				else
				{
					setMotorSpeed(motorB,100);//left black
					setMotorSpeed(motorC,-65);//turn right
				}
			}
			else if(getColorReflected(S2)>blackR)
			{
				if(getColorReflected(S3)<blackL)
				{
					setMotorSpeed(motorB,-65);//left black
					setMotorSpeed(motorC,100);//turn right
				}
				else
				{
					break;
				}
			}
		}
	}
	*/
void lineFollow()
{
	if (getColorReflected(S2)> blackR)//if see white
	{
		if (getColorReflected(S3)> blackL)//if see white
		{
			setMotorSpeed(motorB,40);//double white
			setMotorSpeed(motorC,40);//forward
		}
		else
		{
			setMotorSpeed(motorB,75);//left black
			setMotorSpeed(motorC,-35);//turn right
		}
	}
	else if(getColorReflected(S2)< blackR)
	{
		if (getColorReflected(S3)> blackL)//if see white
		{
			setMotorSpeed(motorB,-35);//left black
			setMotorSpeed(motorC,75);//turn right
		}
		else
		{
			if (getColorName(S2)==colorGreen)
			{
				setMotorSpeed(motorB,5);
				setMotorSpeed(motorC,60);
			}
			else if (getColorName(S3)==colorGreen)
			{
				setMotorSpeed(motorB,60);
				setMotorSpeed(motorC,5);
			}
			else
			{
				setMotorSpeed(motorB,20);
				setMotorSpeed(motorC,20);
			}
		}
	}
}
void red()
{
	if (getColorName(S1) == colorRed)
	{
		setMotorSpeed(motorB,0);//double white
		setMotorSpeed(motorC,0);//forward
		delay(2500);
		playSound(soundBeepBeep);
		while(getColorReflected(S2)>blackL)
		{
			setMotorSpeed(motorB,40);
			setMotorSpeed(motorC,-10);
		}
		while(getColorReflected(S3)>blackR)
		{
			setMotorSpeed(motorB,-10);
			setMotorSpeed(motorC,40);
		}
	}
}

void obstacleNavigation()
{
	//Obstacle Code
	setMotorSpeed(motorB,-20);//reverse for 0.5 seconds
	setMotorSpeed(motorC,-20);
	delay(800);
	setMotorSpeed(motorB,20);//turn	  for 1 second
	setMotorSpeed(motorC,-20);
	delay(1700);
	while (getColorReflected(S2)> blackR)//while all colours but black
	{
		setMotorSpeed(motorB,30);//go around tower
		setMotorSpeed(motorC,70);
	}
	if (getColorReflected(S2)< blackR)//if see line
	{
		setMotorSpeed(motorB,20);//go forward for 0.5 secoonds
		setMotorSpeed(motorC,20);
		delay(500);
		setMotorSpeed(motorB,20);
		setMotorSpeed(motorC,-20);//turn left for 0.5 seconds
		delay(500);
	}
}
/*
void detectObstacle()
{
{
if (SensorValue[S4]<5)//If detects obstacle less than or greater than 5cm away
{
taskNo = 2; //Switch to obstacleNavigation
}
else
{
taskNo = 1; // Keep Line Following Code runnning
}
}
}
*/
void rescue()
{
	long rotatesecond;
	bool leftSeenWhite, rightSeenWhite = false;
	setMotorSpeed(motorB,-20);
	setMotorSpeed(motorB,20);
	setMotorSpeed(motorC,20);
	wait1Msec(5000);
	clearTimer(T1);
	playSound(soundBeepBeep);
	setMotorSpeed(motorB,-52);
	setMotorSpeed(motorC,52);
	delay(333);
	while(getUSDistance(S4)>28)
	{
		setMotorSpeed(motorB,-52);
		setMotorSpeed(motorC,52);
	}
	/*
	if(getUSDistance(S4)>29)
	{
	setMotorSpeed(motorB, 50);
	setMotorSpeed(motorC,-50);
	delay(370);
	}
	*/
	setMotorSpeed(motorB, 0);
	setMotorSpeed(motorC, 0);
	//Get the time taken to find the can
	rotatesecond = time1[T1];
	playSound(soundBeepBeep);
	clearTimer(T1);
	while(getUSDistance(S4)>=usvalue)
	{
		setMotorSpeed(motorB,20);
		setMotorSpeed(motorC,20);
		long int timeMovingForwardF = time1[T1];
		if(getUSDistance(S4)>=31)
		{
			setMotorSpeed(motorB,-20);
			setMotorSpeed(motorC,-20);
			delay(timeMovingForwardF);
			setMotorSpeed(motorB,52);
			setMotorSpeed(motorC,-52);
			delay(rotatesecond);
			clearTimer(T1);
			while(getUSDistance(S4)>35)
			{
				setMotorSpeed(motorB,-52);
				setMotorSpeed(motorC,52);
			}
			int rotatesecond = time1[T1];
			clearTimer(T1);
			while(getUSDistance(S4)>=6)
			{
				setMotorSpeed(motorB,20);
				setMotorSpeed(motorC,20);
			}
			long int timeMovingForward = time1[T1];
		}
	}
	/*int canDist = getUSDistance(S4);
	displayTextLine(2, "us read: %d", canDist);
	setMotorSpeed(motorB,0);
	setMotorSpeed(motorC,0);
	delay(5000);
	playSound(soundBeepBeep);*/
	setMotorSpeed(motorB,20);
	setMotorSpeed(motorC,20);
	delay(950);
	setMotorSpeed(motorA,10);//close claw
	setMotorSpeed(motorB,0);
	setMotorSpeed(motorC,0);
	delay(1200);
	setMotorSpeed(motorA, 0); //Stop the motor from smashing into the ground
	while(!(leftSeenWhite) || !(rightSeenWhite))
	{
		if(getColorReflected(S2)> blackR)
		{
			leftSeenWhite = true;
		}
		if(getColorReflected(S3)> blackL)
		{
			rightSeenWhite = true;
		}
		setMotorSpeed(motorB,20);
		setMotorSpeed(motorC,20);
		delay(50);
	}
	long int timeMovingForward = time1[T1];
	setMotorSpeed(motorB,0);
	setMotorSpeed(motorC,0);
	setMotorSpeed(motorA,-20);//open claw
	delay(650);
	setMotorSpeed(motorA,0);
	setMotorSpeed(motorB,-20);
	setMotorSpeed(motorC,-20);
	delay(timeMovingForward - 1200);
	setMotorSpeed(motorB,52);
	setMotorSpeed(motorC,-52);
	delay(rotatesecond);
	setMotorSpeed(motorB,-20);
	setMotorSpeed(motorC,-20);
	delay(4600);
	setMotorSpeed(motorB,50);
	setMotorSpeed(motorC,-50);
	delay(1600);
	while(getColorName(S2)==colorBlack)
	{
		setMotorSpeed(motorB,50);
		setMotorSpeed(motorC,-50);
	}
	setMotorSpeed(motorB,0);
	setMotorSpeed(motorC,0);
	delay(300);
}

void alignatsilver()
{
	setMotorSpeed(motorB,10);
	setMotorSpeed(motorC,10);
	delay(150);
	while(getColorReflected(S2)> blackL && getColorReflected(S3)> blackR)
	{
		setMotorSpeed(motorB,10);
		setMotorSpeed(motorC,10);
	}
	setMotorSpeed(motorB,0);
	setMotorSpeed(motorC,0);
	if(getColorReflected(S2)< blackL && getColorReflected(S3)< blackL)
	{
		while(getColorReflected(S2)< blackL && getColorReflected(S3)< blackL)
		{
			setMotorSpeed(motorB,-10);
			setMotorSpeed(motorC,-10);
		}
	}
	else if(getColorReflected(S2)< silver)
	{
		while(getColorReflected(S2)< silver)
		{
			setMotorSpeed(motorB,-20);
			setMotorSpeed(motorC,0);
		}
		setMotorSpeed(motorB,-20);
		delay(200);
	}
	else if(getColorReflected(S3)< silver)
	{
		while(getColorReflected(S3)< silver)
		{
			setMotorSpeed(motorB,0);
			setMotorSpeed(motorC,-20);
		}
		setMotorSpeed(motorC,-20);
		delay(200);
	}
	rescue();
}

task main()
{
	while(true) {
		if(SensorValue(Ultrasonic) < 5) {
			obstacleNavigation();
			}	else {
				if(getColorReflected(S2) > silver && getColorReflected(S3) > silver) { //Checks for silver strip
					alignatsilver(); // Runs Rescue Function
					/*int canDist;
					while(true) {
						canDist = getUSDistance(S4);
						setMotorSpeed(motorB,0);
						setMotorSpeed(motorC,0);
						displayTextLine(2, "us read: %d", canDist);
					}*/
				}
				lineFollow();
				red();// Runs Line Follow Function
			}
		}
	}
