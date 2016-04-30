/*
Mario Kart Bluetooth Controlled Game
Written by: Yongxuan Li, Sachin Apiah, Michael Ru, Kevin Huo
Group 5
MTE 100 and GENE 121
*/


bool initialize(int & player);
void displayPlayer(int p);
char readBluetooth();
void convertInput(char input, int speed, bool & canShoot, bool speedUp, bool slowDown);
void setMotor(int mA, int mC);
void launchBall();
void checkColour(int & lap, bool & canShoot, int boostTime, int slowTime,
								int & blue, int & yellow, int & red, int & lastValue);
void checkBump(int & numColl, int stunTime);
void outputScore(float dis, float time, float speed, int numColl, int b, int y, int r);


bool initialize(int & player) //Yongxuan and Sachin
{
	setBluetoothRawDataMode(); //change bluetooth to read the raw data sent
	while (!bBTRawMode) //loop while the mode has not changed
	{
		wait1Msec(1);
	}

	if (nBTCurrentStreamIndex >= 0)//check that the bluetooth connection has occured
	{
		//PlaySoundFile("Startup.rso");
		//while (bSoundActive);

		//menu stuff

		nxtDisplayCenteredTextLine(3, "Insert Coin");
		while(nNxtButtonPressed == -1);
		while(nNxtButtonPressed != -1);
		eraseDisplay();

		do
		{
			if (nNxtButtonPressed == 2 && player > 0)
			{
				eraseDisplay();
				player--;
			}
			else if (nNxtButtonPressed == 1 && player < 2)
			{
				eraseDisplay();
				player++;
			}

		 while(nNxtButtonPressed != -1);
			displayPlayer(player);

		} while (nNxtButtonPressed != 3);
			while(nNxtButtonPressed != -1);

			eraseDisplay();
		//PlaySoundFile("speedup.rso");
		//while (bSoundActive);
		return true;
	}
	else
	{
		//PlaySoundFile("Whoops.rso");
		//while (bSoundActive);
		return false;
	}
}

/*
Players:
0-Peach: Increased boost time, decreased banana slow time
1-Mario: Increased base speed
2-Bowser: Decreased bump stun time
*/
void displayPlayer(int p)
{
	if (p == 0) //peach
	{
		nxtDisplayCenteredTextLine(0, "PEACH");
		nxtDisplayCenteredTextLine(2, "+ mushroom boost");
		nxtDisplayCenteredTextLine(3, "- banana slow");

		///right arrow
		nxtDrawLine(90, 20, 75, 20);
		nxtDrawLine(90, 20, 85, 25);
		nxtDrawLine(90, 20, 85, 15);
	}
	else if (p == 1) //mario
	{
		nxtDisplayCenteredTextLine(0, "MARIO");
		nxtDisplayCenteredTextLine(2, "+ base speed");

		//left arrow
		nxtDrawLine(10, 20, 25, 20);
		nxtDrawLine(10, 20, 15, 25);
		nxtDrawLine(10, 20, 15, 15);

		///right arrow
		nxtDrawLine(90, 20, 75, 20);
		nxtDrawLine(90, 20, 85, 25);
		nxtDrawLine(90, 20, 85, 15);
	}
	else
	{
		nxtDisplayCenteredTextLine(0, "BOWSER");
		nxtDisplayCenteredTextLine(2, "- stun time");

		//left arrow
		nxtDrawLine(10, 20, 25, 20);
		nxtDrawLine(10, 20, 15, 25);
		nxtDrawLine(10, 20, 15, 15);
	}

}

char readBluetooth()// Jerry
{
	ubyte receive[1];
	nxtReadRawBluetooth(receive, 1);
	return (char)receive[0];
}

void convertInput(char input, int speed, bool & canShoot, bool speedUp, bool slowDown) // Michael and Jerry
{
	if (speedUp)
		speed += 40;
	if (slowDown)
		speed -= 40;

		nxtDisplayString(0,"***%c***",input);

	if (input == 'z')
		setMotor(0, 0);
	else if (input == 'p' && canShoot)
	{
		launchBall();
		canShoot = false;
	}
	switch(input)
	{
		//left turns
		case 'q':
			setMotor(speed-40,speed +40);
			nxtDisplayString(1,"0");
			break;
		case 'w':
			setMotor(speed-30,speed +30);
			nxtDisplayString(1,"1");
			break;
		case 'e':
			setMotor(speed-20,speed+20);
			nxtDisplayString(1,"2");
			break;
		case 'r':
			setMotor(speed-10,speed +10);
			nxtDisplayString(1,"3");
			break;

		case 't':
			setMotor(speed,speed);
			nxtDisplayString(1,"4");
			break;

			//left turns
		case 'y':
			setMotor(speed+10,speed-10);
			nxtDisplayString(1,"4");
			break;
		case 'u':
			setMotor(speed+20,speed-20);
			nxtDisplayString(1,"4");
			break;
		case 'i':
			setMotor(speed+30,speed-30);
			nxtDisplayString(1,"4");
			break;
		case 'o':
			setMotor(speed+40,speed-40);
			nxtDisplayString(1,"4");
			break;

			//backwards
		case 'a':
			setMotor(-(speed-40),-(speed +40));
			nxtDisplayString(1,"5");
			break;
		case 's':
			setMotor(-(speed-30),-(speed +30));
			nxtDisplayString(1,"0");
			break;
		case 'd':
			setMotor(-(speed-20),-(speed+20));
			break;
		case 'f':
			setMotor(-(speed -10),-(speed +10));
			break;

			//straight
		case 'g':
			setMotor(-speed, -speed);
			break;

			//right
		case 'h':
			setMotor(-(speed+10),-(speed -10));
			break;
		case 'j':
			setMotor(-(speed+20),-(speed -20));
			break;
		case 'k':
			setMotor(-(speed+30),-(speed-30));
			break;
		case 'l':
			setMotor(-(speed+40),-(speed -40));
			break;
	}

	/*else
	{
		string s = input;
		int num = atoi(s);

		if (num <= 4)
		{
			num -= 2;
		}
		else
		{
			num -= 7;
			speed *= -1;
		}

		if (num < 0)
			setMotor(speed + num * 15, speed - num * 15);
		else
			setMotor(speed - num * 15, speed + num * 15);
	}*/
}

void setMotor(int mA, int mC) //Sachin
{
	motor[motorA] = mA;   //Left Motor
	motor[motorC] = mC;   //Right Motor
}

void launchBall() //Sachin
{
	nMotorEncoder[motorB] = 0;

	motor[motorB] = 50;
	while (nMotorEncoder[motorB] < 350);  //shooting a ball in every revolution of the Motor
	motor[motorB] = 0;

}

void checkColour(int & lap, bool &canShoot, int boostTime, int slowTime,
	int & blue, int & yellow, int & red, int & lastValue) //Michael
{
	int senValue = SensorValue[S1];
	if (SensorValue[S1] != lastValue) //proceed if the current colour is different from the last colour
	{
		lastValue = SensorValue[S1];
	if (senValue != 1 && senValue != 6)
	{
		wait1Msec(50);
		if (SensorValue[S1] == senValue)
		{
				if (senValue == 2) //blue - speedboost
				{
					//speedUp = true;
					//time1[T2] = 0; //reset timer
				//motor[motorA] = 100;
				//motor[motorC] = 100;
				//wait1Msec(1000);
					nxtDisplayString(2,"BLUE");
					blue++;
					motor[motorA] = 100;
					motor[motorC] = 100;
				PlaySoundFile("speedup.rso");
				wait1Msec(boostTime);
				motor[motorA] =0;
				motor[motorC] = 0;
				}

				else if (SensorValue[S1] == 3) //green - finish line
				{
					lap += 1;
					nxtDisplayString(3, "GREEN");

				}

				else if (SensorValue[S1] == 4) //yellow - banana
				{
					//slowDown = true;
					//time1[T3] = 0; //reset timer
					nxtDisplayString(4,"YELLOW");
					yellow++;
							motor[motorA] = 20;
					motor[motorC] = 20;
				PlaySoundFile("banana.rso");
				wait1Msec(slowTime);
								motor[motorA] =0;
				motor[motorC] = 0;
				}

				else //red - ballshooter
				{
					canShoot = true;
					nxtDisplayString(5, "RED");
					red++;
				PlaySoundFile("! Attention.rso");
				while (bSoundActive);
				}
				eraseDisplay();
			}
		}
	}
}


void checkBump(int & numColl, int stunTime) //Kevin
{
	if(time1[T4] > 2000)
	if(SensorValue[S3] == 1 || SensorValue[S4] == 1)
	{
		motor[motorA] = 0;
		motor[motorC] = 0;
		wait1Msec(stunTime);

		time1[T4] = 0;
		numColl++;
	}
}

void outputScore(float dis, float time, float speed, int numColl, int b, int y, int r) // Kevin
{
	PlaySoundFile("! Attention.rso");
	while(bSoundActive);
	nxtDisplayString(0, "Crashes: %d", numColl);
	wait10Msec(50);

	PlaySoundFile("! Attention.rso");
	while(bSoundActive);
	nxtDisplayString(1, "Bananas: %d", y);
	wait10Msec(50);

	PlaySoundFile("! Attention.rso");
	while(bSoundActive);
	nxtDisplayString(2, "Mushrooms: %d", b);
	wait10Msec(50);

	PlaySoundFile("! Attention.rso");
	while(bSoundActive);
	nxtDisplayString(3, "Green Shells: %d", r);
	wait10Msec(50);

	nxtDisplayString(7, "PRESS BUTTON...");
	while (nNxtButtonPressed == -1);
	while (nNxtButtonPressed != -1);
	eraseDisplay();

	PlaySoundFile("! Attention.rso");
	while(bSoundActive);
	nxtDisplayString(0, "Time Taken:");
	nxtDisplayString(1, "%.2f s", time);
	wait10Msec(50);

	PlaySoundFile("! Attention.rso");
	while(bSoundActive);
	nxtDisplayString(2, "Total Distance:");
	nxtDisplayString(3, "%.2f cm", dis);
	wait10Msec(50);

	PlaySoundFile("! Attention.rso");
	while(bSoundActive);
	nxtDisplayString(5,"Average Speed:");
	nxtDisplayString(6,"%.2f cm/s",speed);
	wait10Msec(50);

	nxtDisplayString(7, "PRESS BUTTON...");
	while (nNxtButtonPressed == -1);
	while (nNxtButtonPressed != -1);
	eraseDisplay();

	nxtDisplayCenteredBigTextLine(4,"TALLYING SCORE...");
	PlaySoundFile("! Startup.rso");
	while(bSoundActive);
	eraseDisplay();

	nxtDisplayCenteredTextLine(1,"TOTAL SCORE:");
	nxtDisplayCenteredBigTextLine(3,"%.2f", speed + b + r - y - numColl);
	nxtDisplayCenteredTextLine(6, "THANKS 4 PLAYING");
	nxtDisplayCenteredTextLine(7, "Group5Games");

	while(nNxtButtonPressed == -1);
}

/*
Players:
0-Peach: Increased boost time, decreased banana slow time
1-Mario: Increased base speed
2-Bowser: Decreased bump stun time
*/


task main()
{

	int blue = 0, yellow = 0, red = 0, numColl = 0, ; //keep track of how many colours and collisions hit
	int lap = 1, player = 1;//default to mario
	int bananaSlow = 2000, speedBoost = 2000, stunTime = 1500; //timings for special events
	int defaultSpeed = 50;
	int lastColour = 1; //last colour initialized at black

	float totDis = 0, totTime = 0;
	float avgSpeed = 0;

	bool canShoot = false, speedUp = false, slowDown = false, canStun = true;

	SensorType[S1] = sensorCOLORFULL;
	SensorType[S3] = sensorTouch;
	SensorType[S4] = sensorTouch;

	nMotorEncoder[motorA] = 0;
	nMotorEncoder[motorB] = 0;

	time1[T1] = 0; //for total race length
	time1[T2] = 0; //for speedup
	time1[T3] = 0; //for slowdown
	time1[T4] = 0; //for bump

	if (initialize(player))
	{
		//setup each player's abilities

		if (player == 0)//peach
		{
			bananaSlow -= 500;
			speedBoost += 500;
		}
		else if (player == 1)//mario
			defaultSpeed = 60;
		else //bowser
			stunTime -= 500;

		nxtDisplayCenteredBigTextLine(3,"3");
		PlaySoundFile("! Click.rso");
		wait1Msec(1000);
		nxtDisplayCenteredBigTextLine(3,"2");
		PlaySoundFile("! Click.rso");
		wait1Msec(1000);
		nxtDisplayCenteredBigTextLine(3,"1");
		PlaySoundFile("! Click.rso");
		wait1Msec(1000);
		nxtDisplayCenteredBigTextLine(3,"Go");
		PlaySoundFile("! Attention.rso");
		eraseDisplay();

			time1[T1] = 0;
		do
		{
		if(slowDown)
			nxtDisplayString(6,"SLOW");
		if(speedUp)
			nxtDisplayString(6,"FAST");

			if (time1[T2] > speedBoost)
				speedUp = false;
			if (time1[T3] > bananaSlow)
				slowDown = false;

			if (time10[T1] > 32000)
			{
				totTime += time10[T1]/100.0;
				time10[T1] = 0;
			}

			if (nMotorEncoder[motorA] > 32000)
			{
				totDis += (8.2 * PI / 360.0) * nMotorEncoder[motorA];
				nMotorEncoder[motorA] = 0;
			}

			//game loop
			convertInput(readBluetooth(), defaultSpeed, canShoot, speedUp, slowDown);

			checkColour(lap, canShoot, speedBoost, bananaSlow, blue, yellow, red, lastColour);

			checkBump(numColl, stunTime);

			nxtDisplayString(7, "lap %d",lap);

		} while (lap <= 3);

		setMotor(0, 0);

		totTime += time10[T1]/100.0;
		totDis += (42.37 / 360.0) * nMotorEncoder[motorA];
		avgSpeed = totDis / totTime;

		nxtDisplayString(0, "Press Button!");
		while (nNxtButtonPressed == -1);
		while (nNxtButtonPressed != -1);
		eraseDisplay();

		outputScore(totDis, totTime, avgSpeed, numColl, blue, yellow, red);
		wait10Msec(100);
	}

	else
	{
		nxtDisplayString(4, "No Connection");
		PlaySoundFile("Woops.rso");
	  while(bSoundActive);
		while(nNxtButtonPressed == -1);
		while(nNxtButtonPressed != -1);
	}
}
