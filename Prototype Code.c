/*---------------------------------------------------------------------------*/
/*                                                                           */
/*        Description: Competition template for VEX EDR                      */
/*                                                                           */
/*---------------------------------------------------------------------------*/

// This code is for the VEX cortex platform
#pragma platform(VEX2)

// Select Download method as "competition"
#pragma competitionControl(Competition)
#pragma config(UART_Usage, UART2, uartNotUsed, baudRate4800, IOPins, None, None)
#pragma config(Sensor, in1,    pot,            sensorPotentiometer)
#pragma config(Sensor, dgtl6,  quadL,          sensorQuadEncoder)
#pragma config(Sensor, dgtl8,  quadR,          sensorQuadEncoder)
#pragma config(Motor,  port1,           clawL,         tmotorVex393_HBridge, openLoop)
#pragma config(Motor,  port2,           dLeftF,        tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port3,           dLeftB,        tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           armL1,         tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port5,           armL2,         tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port6,           armR1,         tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port7,           armR2,         tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port8,           dRightF,       tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port9,           dRightB,       tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port10,          clawR,         tmotorVex393_HBridge, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

// to turn left, motors are negative
//to turn right, motors are positive


/* NOTES

Potentiometer key:
Closed: ~3900
180 Degrees: ~2660
45 degrees (facing towards stars but not closed): ~1700
Fully closed: ~1000, 1100



*/



#pragma platform(VEX)

//Competition Control and Duration Settings
#pragma competitionControl(Competition)

#define LOOPSPEED 50 //Time between user control loops in milliseconds - time alloted to other tasks while usercontrol is idle
#define DEADZONE 20 //Deadzone for joystick control
#define m_clawL 1
#define m_dLeftF 2
#define m_dLeftB 3
#define m_armL1 4
#define m_armL2 5
#define m_armR1 6
#define m_armR2 7
#define m_dRightF 8
#define m_dRightB 9
#define m_clawR 10

#define joy_left_vertical "Ch3"
#define joy_left_horizontal "Ch4"
#define joy_right_vertical "Ch2"
#define joy_right_horizontal "Ch1"

//GLOBAL VARIABLES
float powerExpanderBatteryV;
//Control variables
int armC, clawC,musicCtrl, openSlow, openFast, closeSlow, closeFast;
int armMotors;


#include "Vex_Competition_Includes.c"

//#include "music.h"
//#include "StarstruckIncludes.h"
//#include "motor.c"





void pre_auton()
{
	// Set bStopTasksBetweenModes to false if you want to keep user created tasks running between
	// Autonomous and Tele-Op modes. You will need to manage all user created tasks if set to false.
	bStopTasksBetweenModes = true;
}

task autonomous()
{
  // ..........................................................................
  // Insert user code here.
  // ..........................................................................

  // Remove this function call once you have "real" code.
  AutonomousCodePlaceholderForTesting();
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

task usercontrol()
{
 	nSchedulePriority = 10;
	//Math variables

	int mReqLF, mReqRF, mReqLB, mReqRB, clawValue;
	while(true){

		//int joyLV = vexRT[Ch3];
		//int joyLH = vexRT[Ch4];
		//int joyRV = vexRT[Ch2];
		//int joyRH = vexRT[Ch1];

		armC = vexRT[Ch2];
		openSlow = vexRT[Btn6U] * 80;
		closeSlow = vexRT[Btn6D] * -80;


		if(abs(SensorValue(armEncoder)) < 256){
				openFast = vexRT[Btn5U] * 120;
		} else {
				openFast = vexRT[Btn5U] * -120;
		}


		closeFast = vexRT[Btn5D] * -120;
		clawC = vexRT[Ch1];


		musicCtrl = vexRT[Btn7UXmtr2];

		forwardVector = vexRT[Ch3];
		horizontalVector = vexRT[Ch4];
		rotationVector = vexRT[Ch1];

	mReqLF = forwardVector + rotationVector + horizontalVector;
	mReqRF = forwardVector - rotationVector - horizontalVector;
	mReqLB = forwardVector + rotationVector - horizontalVector;
	mReqRB = forwardVector - rotationVector + horizontalVector;

	if(abs(mReqLF) > DEADZONE)
		motor[dLeftF] = mReqLF;
	else
		motor[dLeftF] = 0;

	if(abs(mReqRF) > DEADZONE)
		motor[dRightF] = mReqRF;
	else
		motor[dRightF] = 0;

	if(abs(mReqLB) > DEADZONE)
		motor[dLeftB] = mReqLB;
	else
		motor[dLeftB] = 0;

	if(abs(mReqRB) > DEADZONE)
		motor[dRightB] = mReqRB;
	else
		motor[dRightB] = 0;


		if(abs(armC) > DEADZONE) {
			armMotors = armC;
			} else {
			armMotors = 0;
		}


		clawValue = openSlow + closeSlow + openFast + closeFast;
		motor[clawL] = clawValue;
		motor[clawR] = clawValue;

		//Set Motors
		motor[armL1] = armMotors;
		motor[armL2] = armMotors;
		motor[armR1] = armMotors;
		motor[armR2] = armMotors;



		//Displays Battery Levels to VEX Remote Screen
		powerExpanderBatteryV = SensorValue[in1]/.28;
		clearLCDLine(0);
		clearLCDLine(1);
		displayLCDPos(0,0);
		displayNextLCDString("C Bat:");
		displayNextLCDNumber(nAvgBatteryLevel);
		displayLCDPos(1,0);
		displayNextLCDString("P.E Bat:");
		displayNextLCDNumber(powerExpanderBatteryV);

		datalogDataGroupStart();
		datalogAddValueWithTimeStamp(0, armMotors);
		datalogAddValueWithTimeStamp(1, clawValue);

		datalogAddValueWithTimeStamp(2,
		datalogAddValueWithTimeStamp(3,
		datalogAddValueWithTimeStamp(4,
		datalogAddValueWithTimeStamp(5,

		wait1Msec(LOOPSPEED);
	}
}
