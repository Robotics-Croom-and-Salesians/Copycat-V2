/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       ME                                                        */
/*    Created:      Wed Jan 15 2020                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
#include "vex.h"
#include <vector>
#include <fstream>

vex::controller Controller = vex::controller();

vex::motor LeftMotor2 = vex::motor( vex::PORT2 , true);
vex::motor RightMotor = vex::motor( vex::PORT1 );
vex::motor LeftMotor = vex::motor( vex::PORT10, true );
vex::motor RightMotor2 = vex::motor( vex::PORT9);

vex::motor BlockCollector = vex::motor( vex::PORT6, true );
vex::motor BlockCollector2 = vex::motor( vex::PORT7);

vex::motor DropBlock = vex::motor( vex::PORT3);
// ---- END VEXCODE CONFIGURED DEVICES ----


// ---- START OF PROGRAM FUNCTIONS ----

int divide = 4;

void moveOnAxisThreesChange(){

  int Axis3Val = Controller.Axis3.position() / divide;
  int Axis1Val = Controller.Axis1.position() / divide;

  if(Axis1Val == 0){
    LeftMotor.setVelocity(Axis3Val, vex::velocityUnits::pct );
    RightMotor.setVelocity(Axis3Val, vex::velocityUnits::pct );
    RightMotor2.setVelocity(Axis3Val, vex::velocityUnits::pct );
    LeftMotor2.setVelocity(Axis3Val, vex::velocityUnits::pct );


    LeftMotor.spin( vex::directionType::fwd );
    RightMotor.spin( vex::directionType::fwd );
    LeftMotor2.spin( vex::directionType::fwd );
    RightMotor2.spin( vex::directionType::fwd );  

  }else if(Axis1Val != 0 && Axis3Val != 0){

    if(Axis1Val < 0){
      LeftMotor.setVelocity(Axis3Val - Axis1Val, vex::velocityUnits::pct );
      RightMotor.setVelocity(Axis3Val + Axis1Val, vex::velocityUnits::pct );
      RightMotor2.setVelocity(Axis3Val + Axis1Val, vex::velocityUnits::pct );
      LeftMotor2.setVelocity(Axis3Val - Axis1Val, vex::velocityUnits::pct );

    }else{
      LeftMotor.setVelocity(Axis3Val - Axis1Val, vex::velocityUnits::pct );
      RightMotor.setVelocity(Axis3Val + Axis1Val, vex::velocityUnits::pct );
      RightMotor2.setVelocity(Axis3Val + Axis1Val, vex::velocityUnits::pct );
      LeftMotor2.setVelocity(Axis3Val - Axis1Val, vex::velocityUnits::pct );

    }
    LeftMotor.spin( vex::directionType::fwd );
    RightMotor.spin( vex::directionType::fwd );
    LeftMotor2.spin( vex::directionType::fwd );
    RightMotor2.spin( vex::directionType::fwd );  


  }else if( Axis3Val == 0){

    if(Axis1Val > 0){ 
      LeftMotor.setVelocity(-Axis1Val, vex::velocityUnits::pct );
      RightMotor.setVelocity(Axis1Val, vex::velocityUnits::pct );
      RightMotor2.setVelocity(Axis1Val, vex::velocityUnits::pct );
      LeftMotor2.setVelocity(-Axis1Val, vex::velocityUnits::pct );


      LeftMotor.spin( vex::directionType::fwd );
      RightMotor.spin( vex::directionType::fwd );
      LeftMotor2.spin( vex::directionType::fwd );
      RightMotor2.spin( vex::directionType::fwd );    
    }else{
      LeftMotor.setVelocity(-Axis1Val, vex::velocityUnits::pct );
      RightMotor.setVelocity(Axis1Val, vex::velocityUnits::pct );
      RightMotor2.setVelocity(Axis1Val, vex::velocityUnits::pct );
      LeftMotor2.setVelocity(-Axis1Val, vex::velocityUnits::pct );

      LeftMotor.spin( vex::directionType::fwd );
      RightMotor.spin( vex::directionType::fwd );
      LeftMotor2.spin( vex::directionType::fwd );
      RightMotor2.spin( vex::directionType::fwd ); 
      
    }
  }
}

void collectBlock(){

  BlockCollector.setVelocity(127 / divide, vex::velocityUnits::pct );
  BlockCollector2.setVelocity(127 / divide, vex::velocityUnits::pct );

  BlockCollector2.spin( vex::directionType::fwd );  
  BlockCollector.spin( vex::directionType::fwd );  

}

void spitBlock(){

  BlockCollector.setVelocity(-127 / divide, vex::velocityUnits::pct );
  BlockCollector2.setVelocity(-127 / divide, vex::velocityUnits::pct );

  BlockCollector2.spin( vex::directionType::fwd );  
  BlockCollector.spin( vex::directionType::fwd );  

}

void dropBlock(int fastness, int degrees){

  DropBlock.setVelocity(fastness / divide, vex::velocityUnits::pct);
  //DropBlock.spin(vex::directionType::fwd);

  DropBlock.rotateTo(degrees, vex::rotationUnits::deg, false);

}

// ---- END OF PROGRAM FUNCTIONS ----

int main() {
  // Initializing Robot Configuration.
  vexcodeInit();
  std::ofstream myfile;
  myfile.open ("ProjectCopyCatValue.txt", std::ofstream::out);
  // ---- START OF MAIN PROGRAM LOOP ----
  while(1){


    Controller.Screen.setCursor(1,1);
    Controller.Screen.print("%d%% -- Brain", Brain.Battery.capacity());
    Controller.Screen.newLine();
    // Controller.Screen.print("Controller Battery Capacity: %d%%", Controller.Battery.capacity());
    Controller.Screen.newLine();

    if(Controller.ButtonB.pressing()){
      myfile.close();
      break;
    }
    else if(Controller.ButtonL2.pressing()){

      dropBlock(35, 600);
    }else if(Controller.ButtonR1.pressing()){

      spitBlock();

    }else if(Controller.ButtonR2.pressing()){

      collectBlock();
      
    }else if(Controller.ButtonL1.pressing()){

      dropBlock(-35, 0);
    }else{
      BlockCollector.stop();
      BlockCollector2.stop();
      DropBlock.stop();

    }

    Controller.Axis3.changed(moveOnAxisThreesChange);
    Controller.Axis1.changed(moveOnAxisThreesChange);

    myfile << LeftMotor.velocity(vex::velocityUnits::pct) << " ";
    myfile << RightMotor.velocity(vex::velocityUnits::pct) << " ";
    myfile << RightMotor2.velocity(vex::velocityUnits::pct) << " ";
    myfile << LeftMotor2.velocity(vex::velocityUnits::pct) << " ";

    myfile << BlockCollector.velocity(vex::velocityUnits::pct) << " ";
    myfile << BlockCollector2.velocity(vex::velocityUnits::pct) << " ";
    myfile << DropBlock.velocity(vex::velocityUnits::pct) << " \n";

    Controller.Screen.clearScreen();

  }
  // ---- END OF MAIN PROGRAM LOOP ----
 
}
