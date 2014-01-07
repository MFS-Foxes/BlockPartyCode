#pragma config(Sensor, S1,     MSTMUX,              sensorLightInactive)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*
 * $Id: mindsensors-touchmux-test1.c 109 2012-09-25 17:10:26Z xander $
 */

/**
 * mindsensors-touchmux.h provides an API for the Mindsensors Touch Sensor MUX.  This program
 * demonstrates how to use that API.
 *
 * Changelog:
 * - 0.1: Initial release
 *
 * Credits:
 * - Big thanks to Mindsensors for providing me with the hardware necessary to write and test this.
 *
 * License: You may use this code as you wish, provided you give credit where it's due.
 *
 * THIS CODE WILL ONLY WORK WITH ROBOTC VERSION 3.51 AND HIGHER.
 * Xander Soldaat (mightor_at_gmail.com)
 * 11-May-2010
 * version 0.1
 */

#include "drivers/mindsensors-touchmux.h"

task main () {
  nxtDisplayCenteredTextLine(0, "Mindsensors");
  nxtDisplayCenteredBigTextLine(1, "TMUX");
  nxtDisplayCenteredTextLine(3, "Test 1");
  nxtDisplayCenteredTextLine(5, "This is for the");
  nxtDisplayCenteredTextLine(6, "Touch MUX");
  wait1Msec(2000);
  while (true) {
    eraseDisplay();
    nxtDisplayTextLine(0, "MS Touch MUX");

    // Get the raw data from the sensor, this is not processed
    // by the driver in any way.
    nxtDisplayTextLine(1, "Raw: %d", SensorRaw[MSTMUX]);

    // Go through each possible touch switch attached to the TMUX
    // and display whether or not is active (pressed)
    for (int i = 1; i < 4; i++) {
      if (MSTMUXisActive(MSTMUX, i))
        nxtDisplayTextLine(i+2, "Touch %d: on", i);
      else
        nxtDisplayTextLine(i+2, "Touch %d: off", i);
    }

    // Display the binary value of the active touch switches
    // 0 = no touch, 1 = touch 1 active, 2 = touch 2 active, etc.
    // touch 1 + touch 2 active = 1 + 2 = 3.
    nxtDisplayTextLine(7, "Status: %d", MSTMUXgetActive(MSTMUX));
    wait1Msec(50);
  }
}

/*
 * $Id: mindsensors-touchmux-test1.c 109 2012-09-25 17:10:26Z xander $
 */
