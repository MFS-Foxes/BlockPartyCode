#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTServo,  none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     IR,             sensorHiTechnicIRSeeker1200)
#pragma config(Sensor, S3,     gyro,           sensorI2CHiTechnicGyro)
#pragma config(Motor,  motorA,          Spinner,       tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  motorC,           ,             tmotorNXT, openLoop)
#pragma config(Motor,  mtr_S1_C1_1,     Left,          tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     Right,         tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S1_C2_1,     Wrist,         tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C2_2,     Lift,          tmotorTetrix, openLoop, reversed)
#pragma config(Servo,  srvo_S1_C3_1,    Flag,                 tServoContinuousRotation)
#pragma config(Servo,  srvo_S1_C3_2,    Flag2,                tServoContinuousRotation)
#pragma config(Servo,  srvo_S1_C3_3,    aarm,                 tServoStandard)
#pragma config(Servo,  srvo_S1_C3_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

//Last Edit: Armon 12-29-13
//Driving and Turning finished 12-29-13

#include "drivers/hitechnic-sensormux.h"
#include "drivers/hitechnic-protoboard.h"
#include "drivers/hitechnic-accelerometer.h"
#include "drivers/hitechnic-eopd.h"
#include "drivers/hitechnic-irseeker-v2.h"
#include "JoystickDriver.c"
#include "drivers/gyro.h"
#include "Functions.h"

#define irpower 20
#define dslope 30/720
#define maxPwr 10
#define dminPwr 7
#define minPwr 35
#define BOUND(n, l, h) (((n) < (l))? (l): ((n) > (h))? (h): (n))

#define eopd        msensor_s4_1
#define accel       msensor_s4_2
#define sonar       msensor_s4_3

GYRO  g_Gyro;
float g_turnTarget = 0.0;
bool  g_turnEnabled = false;
float g_tolerance = 0.5;  //needs to be tuned
float Kp = 0.1;           //needs to be tuned
bool g_driveEnabled = false;
float g_driveTarget;
float buffer = 5;
bool irseek = true;
int irval;
int i;

void SetTurnTarget(float angle)
{
	g_turnTarget = GyroGetHeading(g_Gyro) + angle;
	g_turnEnabled = true;
}

void TurnTask()
{
	if (g_turnEnabled)
	{
		float error = g_turnTarget - GyroGetHeading(g_Gyro);
		if (abs(error) > g_tolerance)
		{
			//
			// Simple proportional PID control.
			// Limit the outpout to the range of -100 to 100.
			//
			int turnPower = maxPwr*error*Kp + abs(error)/error*minPwr;
			motor[Left] = turnPower;
			motor[Right] = -turnPower;
		}
		else
		{
			motor[Left] = 0;
			motor[Right] = 0;
			g_turnEnabled = false;
		}
	}
}

void initializeRobot()
{
	GyroInit(g_Gyro, gyro, 0);
	return;
}

void setDistance(float target)
{
	g_driveTarget = target + nMotorEncoder[Right];
	g_driveEnabled = true;
}
float driveError;
#define drivePower 100

void driveForDistance()
{
	driveError = g_driveTarget - nMotorEncoder[Right];
	if(abs(driveError) > buffer)
	{
		motor[Left] = driveError*dslope + abs(driveError)/driveError*dminPwr;
		motor[Right] = driveError*dslope + abs(driveError)/driveError*dminPwr;
		if (motor[Left] <= 5)
		{
			g_driveEnabled = false;
		}
	}
	else
	{
		motor[Left] = 0;
		motor[Right] = 0;
		g_driveEnabled = false;
	}
}

void IRseeker()
{
	while(irseek) //Fix the coming up short problem
	{
		irval = SensorValue[IR];
		if(irval != 5)
		{
			motor[Left] = irpower;
			motor[Right] = irpower;
		}
		else
		{
			i = 0;
			while(irseek)
			{
				irval = SensorValue[IR];
				if(irval != 6 || irval != 4)
				{
					i++;
					motor[Left] = irpower/2;
					motor[Right] = irpower/2;
					if (i <= 0)
					{
						i = i / 2;
						irseek = false;
					}
				}
				else
				{
					motor[Left] = 0;
					motor[Right] = 0;
					i = i / 2;
					irseek = false;
				}
			}
			/*while(i != 0)
			{
				motor[Left] = 10;
				motor[Right] = 10;
				i--;
				if (i == 1)
				{
					motor[Left] = 0;
					motor[Right] = 0;
				}
			}*/
			irseek = false;
			//nxtDisplayString( 1, "%d", irval);
		}
	}
}

task main()
{
	waitForStart();
	getJoystickSettings(joystick);
	initializeRobot();
	setDistance(520);
	while(g_driveEnabled)
	{
		driveForDistance();
	}
	SetTurnTarget(82.0);
	while(g_turnEnabled)
	{
		GyroTask(g_Gyro);
		TurnTask();
		wait1Msec(10);
	}
	wait1Msec(500);
	IRseeker();
	motor[Right] = 0;
	motor[Left] = 0;
	/*motor[Left] = 20;
	motor[Right] = 20;
	wait1Msec(500);
	motor[Right] = 0;
	motor[Left] = 0;*/
	servo[aarm] = 200;
	wait1Msec(2000);
	servo[aarm] = 0;
	wait1Msec(2000);
	motor[Left] = 50;
	motor[Right] = -50;
	wait1Msec(1000);
	motor[Left] = 100;
	motor[Right] = 100;
	wait1Msec(1350);
	motor[Left] = 0;
	motor[Right] = 0;
	servo[aarm] = 60;
	wait1Msec(2000);
}