#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTServo,  none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     IR,             sensorHiTechnicIRSeeker1200)
#pragma config(Sensor, S3,     gyro,           sensorI2CHiTechnicGyro)
#pragma config(Motor,  motorA,          Spinner,       tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  motorC,           ,             tmotorNXT, openLoop)
#pragma config(Motor,  mtr_S1_C1_1,     Left,          tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     Right,         tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C2_1,     Wrist,         tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C2_2,     Lift,          tmotorTetrix, openLoop, reversed)
#pragma config(Servo,  srvo_S1_C3_1,    Flag,                 tServoContinuousRotation)
#pragma config(Servo,  srvo_S1_C3_2,    Flag2,                tServoContinuousRotation)
#pragma config(Servo,  srvo_S1_C3_3,    aarm,                 tServoStandard)
#pragma config(Servo,  srvo_S1_C3_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "JoystickDriver.c";

task main()
{
	waitForStart();
	while (true)
	{
		getJoystickSettings(joystick);
		motor[Left] = joystick.joy1_y1;		//Left Drive
		motor[Right] = joystick.joy1_y2;		//Right Drive
		motor[Lift] = joystick.joy2_y1;		//Both Lift Motors
		motor[Wrist] = joystick.joy2_y2*0.5;		//Wrist Motor
		if (joy2Btn(8))
		{
			motor[Spinner] = 100;		//Spins block intake
		}
		else if(joy2Btn(7))
		{
			motor[Spinner] = -100;		//Reverses the spin
		}
		else
		{
			motor[Spinner] = 0;		//Prevents spontaneous movement
		}
		if (joy1Btn(8)||joy2Btn(6))
		{
			servo[Flag] = 255;		//Spins Flag
			servo[Flag2] = 255;
		}
		else if(joy1Btn(7)||joy2Btn(5))
		{
			servo[Flag] = 0;		//Reverses the spin
			servo[Flag2] = 0;
		}
		else
		{
			servo[Flag] = 128;		//Prevents spontaneous movement
			servo[Flag2] = 128;
		}
		if (joy2Btn(3))
		{
			servo[aarm] = 60;
		}
		else if (joy2Btn(1))
		{
			servo[aarm] = 0;
		}
	}
}
