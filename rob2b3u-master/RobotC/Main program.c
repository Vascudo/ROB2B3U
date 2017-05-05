#pragma config(Sensor, dgtl1,  leftSonar,      sensorSONAR_cm)
#pragma config(Sensor, dgtl3,  rightSonar,     sensorSONAR_cm)
#pragma config(Motor,  port2,           leftMotor,     tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port3,           rightMotor,    tmotorServoContinuousRotation, openLoop, reversed)
#pragma config(Motor,  port4,           aftMotor,      tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port5,           armMotor,      tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port6,           clawMotor,     tmotorServoContinuousRotation, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

int rotSpeed = 127, forwdSpeed = 127, sfArmSpeed = 63;
int tIntvl = 62, pickupTime = 2000;
int surround1[30];
int surround2[30];
int min1  = 9000, min2 = 9000;
int minNum1, minNum2;



task main()
{
	int i = 0;
		ClearTimer(T1);
		ClearTimer(T2);
		do{

			if(time1[T1] > tIntvl)
			{
				surround1[i] = SensorValue[leftSonar];
				surround2[i] = SensorValue[rightSonar];


				i++;
				ClearTimer(T1);
			}

			motor[leftMotor] = rotSpeed;
			motor[rightMotor] = -rotSpeed;
			motor[aftMotor] = rotSpeed;

	}while(surround1[29] == 0);

			motor[leftMotor] = 0;
			motor[rightMotor] = 0;
			motor[aftMotor] = 0;

			wait1Msec(100);


for(int i = 0; i < (sizeof(surround1)/2); i++)
	{
		if(min1 >= surround1[i] && surround1[i] != -1)
		{
			min1 = surround1[i];
			minNum1 = i;
		}
	}

for(int i = 0; i < (sizeof(surround2)/2); i++)
	{
		if(min2 >= surround2[i] && surround2[i] != -1)
		{
			min2 = surround2[i];
			minNum2 = i;
		}
	}


wait1Msec(200);

bool one = true;

if(min1 <= min2){
			one = true;
			motor[leftMotor] = rotSpeed;
			motor[rightMotor] = -rotSpeed;
			motor[aftMotor] = rotSpeed;
			wait1Msec(minNum1*tIntvl);

}
else if(min2 <= min1){
			one = false;
			motor[leftMotor] = rotSpeed;
			motor[rightMotor] = -rotSpeed;
			motor[aftMotor] = rotSpeed;
			wait1Msec(minNum2*tIntvl);

}

			motor[leftMotor] = 0;
			motor[rightMotor] = 0;
			motor[aftMotor] = 0;

			wait1Msec(100);


motor[leftMotor] = forwdSpeed;
motor[rightMotor] = forwdSpeed;
if(one)
{
	wait1Msec(min1*25);
}

else if(!one)
{
	wait1Msec(min2*25);
}


motor[leftMotor] = 0;
motor[rightMotor] = 0;
	wait1Msec(1000);

motor[clawMotor] = 127;
motor[armMotor] = sfArmSpeed;
wait1Msec(pickupTime);

motor[clawMotor] = -127;
motor[armMotor] = -sfArmSpeed;
wait1Msec(pickupTime);

motor[clawMotor] = -127;

motor[leftMotor] = rotSpeed;
motor[rightMotor] = -rotSpeed;
motor[aftMotor] = rotSpeed;
wait1Msec(tIntvl*20);

motor[aftMotor] = 0;

motor[leftMotor] = forwdSpeed;
motor[rightMotor] = forwdSpeed;

if(one)
	wait1Msec(min1*25);

else
	wait1Msec(min2*25);


motor[leftMotor] = 0;
motor[rightMotor] = 0;

motor[clawMotor] = 127;

wait1Msec(3000);

}
