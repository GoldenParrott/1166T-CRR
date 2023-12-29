#include "api.h"

pros::Controller Master(pros::E_CONTROLLER_MASTER);
pros::Controller Partner(pros::E_CONTROLLER_PARTNER);

pros::Motor ArmLeft(2,1);
pros::Motor ArmRight(3,0);
pros::Motor_Group Arm({ArmLeft, ArmRight});

pros::Motor Indexer(999);

pros::Motor Intake(20);

pros::Motor FrontLeft(1,1);
pros::Motor BackLeft(7,1);
pros::Motor_Group LeftWheels({FrontLeft, BackLeft});

pros::Motor FrontRight(19,0);
pros::Motor BackRight(8,0);
pros::Motor_Group RightWheels({FrontRight, BackRight});

pros::Motor_Group AllWheels({FrontRight, BackRight, FrontLeft, BackLeft});

pros::ADIDigitalOut PlowLeft(1);
pros::ADIDigitalOut PlowRight(8);

pros::ADIDigitalOut ShieldLeft(2);
pros::ADIDigitalOut ShieldRight(3);

pros::ADIDigitalOut Tether(4);



int drvtrDZ = 10;
int drvtrFB;
int drvtrLR;
bool pl = false;
bool pr = false;
bool shieldRaised = false;
bool thr = false;