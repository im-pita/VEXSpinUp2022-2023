/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       arpita_gupta                                              */
/*    Created:      Wed Jul 06 2022                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// Drivetrain           drivetrain    5, 7, 10, 8     
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;
vex::competition    Competition;

vex::motor rightFront = vex::motor(vex::PORT10);
vex::motor rightBack = vex::motor(vex::PORT8);
vex::motor leftFront = vex::motor(vex::PORT13, true);
vex::motor leftBack = vex::motor(vex::PORT7, true);

int axis3 = 0;
int axis1 = 0;
int axis4 = 0;

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
}

void usercontrol(void) {
  // User control code here, inside the loop
  int X1 = 0, X2 = 0, Y1 = 0, threshold = 30;

  while (1) {
    axis3 = Controller1.Axis3.position();
    axis1 = Controller1.Axis1.position();
    axis4 = Controller1.Axis4.position();
    
    if(abs(axis3)>threshold)
    {
      Y1=axis3;
    }
    if(abs(axis4)>threshold)
    {
      X1=axis4;
    }
    if(abs(axis1)>threshold)
    {
      X2=axis1;
    }

    rightFront.spin(vex::directionType::fwd,Y1-X2-X1,vex::velocityUnits::pct);
    rightBack.spin(vex::directionType::fwd,Y1-X2+X1,vex::velocityUnits::pct);
    leftFront.spin(vex::directionType::fwd,Y1+X2+X1,vex::velocityUnits::pct);
    leftBack.spin(vex::directionType::fwd,Y1+X2-X1,vex::velocityUnits::pct);
    
     wait(20,msec);
    }
 
}


int main() {
  // Set up callbacks for autonomous and driver control periods.
  //Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }

  
}
