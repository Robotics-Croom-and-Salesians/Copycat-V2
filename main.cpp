/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\35383                                            */
/*    Created:      Fri Jan 24 2020                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#include <string>
#include <fstream>
#include <vector>

vex::controller Controller = vex::controller();

vex::motor LeftMotor2 = vex::motor( vex::PORT2 , true);
vex::motor RightMotor = vex::motor( vex::PORT1 );
vex::motor LeftMotor = vex::motor( vex::PORT10, true );
vex::motor RightMotor2 = vex::motor( vex::PORT9);

vex::motor BlockCollector = vex::motor( vex::PORT6, true );
vex::motor BlockCollector2 = vex::motor( vex::PORT7);

vex::motor DropBlock = vex::motor( vex::PORT3);

std::vector<std::vector<double>> Values;

int divide = 4;


std::vector<double> split(std::string toSplit){

  std::vector<double> toReturn;
  std::string currentWorkingNum;

  for(int i = 0;i < toSplit.size(); i++){
    
    if(toSplit[i] == ' '){
      //Brain.Screen.print("got \n");
      double temp = ::atof(currentWorkingNum.c_str());
      Brain.Screen.print(currentWorkingNum.c_str());
      toReturn.push_back(temp);
      currentWorkingNum = "";
      

    }else{
      currentWorkingNum += toSplit[i];
    }

  }

  return toReturn;
}

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  std::string line2;
  std::ifstream myfile ("ProjectCopyCatValue.txt");
  if (myfile.is_open())
  {
    while ( getline (myfile,line2) )
    {
      Brain.Screen.print(line2.c_str());
      std::vector<double> CurrentWorkingVector = split(line2);
      Brain.Screen.newLine();
      Values.push_back(CurrentWorkingVector);

    }
    myfile.close();
  }else{
    Brain.Screen.print("NO!!");
  }
  Brain.Screen.print(Values[0].size());
  Brain.Screen.newLine();
  Brain.Screen.print(Values.size());
  for(int i = 0;i < Values.size(); i++){

    
      LeftMotor.setVelocity(Values[i][0], vex::velocityUnits::pct);
      RightMotor.setVelocity(Values[i][1], vex::velocityUnits::pct);
      RightMotor2.setVelocity(Values[i][2], vex::velocityUnits::pct);
      LeftMotor2.setVelocity(Values[i][3], vex::velocityUnits::pct);
      BlockCollector.setVelocity(Values[i][4], vex::velocityUnits::pct);
      BlockCollector2.setVelocity(Values[i][5], vex::velocityUnits::pct);
      DropBlock.setVelocity(Values[i][6], vex::velocityUnits::pct);

    
    LeftMotor.spin( vex::directionType::fwd );
    RightMotor.spin( vex::directionType::fwd );
    LeftMotor2.spin( vex::directionType::fwd );
    RightMotor2.spin( vex::directionType::fwd );  

    BlockCollector.spin( vex::directionType::fwd );
    BlockCollector2.spin( vex::directionType::fwd );
    DropBlock.spin( vex::directionType::fwd );  

    vex::task::sleep(100/divide);

  }

  
}
