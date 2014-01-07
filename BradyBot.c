#pragma config(Hubs,  S1, HTMotor,  HTMotor,  none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Motor,  mtr_S1_C1_1,     Right,         tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     Left,          tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C2_1,     Spinner,       tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     Hang,          tmotorTetrix, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "JoystickDriver.c"
bool plowForward = true;
task main()
{
	while(true)
	{
		getJoystickSettings(joystick);
if (plowForward)
{
		motor[Left] = joystick.joy1_y1;
		motor[Right] = joystick.joy1_y2;
}
else
{
		motor[Right] = -1*joystick.joy1_y1;
		motor[Left] = -1*joystick.joy1_y2;
}
if(joy1Btn(4))
{
	plowForward = true;
}
else if(joy1Btn(3))
{
	plowForward = false;
}
if (joy1Btn(8))
		{
			motor[Spinner] = 100;
		}
		else if (joy1Btn(7))
		{
			motor[Spinner] = -100;
		}
		else
		{
			motor[Spinner] = 0;
			if (joy1Btn(1))
			{
				motor[Hang]= 75;
			}
			else if (joy1Btn(5))
			{
				motor[Hang] = -100;
			}
			else if (joy1Btn(6))
{
motor[Hang] = 100;
}
else
{
motor[Hang] = 0;}}}
}
