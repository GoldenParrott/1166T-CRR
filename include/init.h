#include "api.h"


//Controllers
pros::Controller Master(pros::E_CONTROLLER_MASTER);
pros::Controller Partner(pros::E_CONTROLLER_PARTNER);


//Motors
pros::Motor ArmLeft(4,0);
pros::Motor ArmRight(3,1);
pros::Motor_Group Arm({ArmLeft, ArmRight});

pros::Motor Indexer(5);

pros::Motor Intake(20);

pros::Motor FrontLeft(1,1);
pros::Motor BackLeft(7,1);
pros::Motor_Group LeftWheels({FrontLeft, BackLeft});

pros::Motor FrontRight(19,0);
pros::Motor BackRight(8,0);
pros::Motor_Group RightWheels({FrontRight, BackRight});

pros::Motor_Group AllWheels({FrontRight, BackRight, FrontLeft, BackLeft});


//Pnuematics
pros::ADIDigitalOut PlowLeft(1);
pros::ADIDigitalOut PlowRight(8);

pros::ADIDigitalOut ShieldLeft(4);
pros::ADIDigitalOut ShieldRight(6);

pros::ADIDigitalOut Tether(7);


//Sensors
pros::ADIDigitalOut Alpha(12);
pros::ADIDigitalOut Beta(6);
pros::ADIDigitalOut Gamma(13);
pros::ADIDigitalOut Delta(14);
pros::ADIDigitalOut Epsilon(999);

pros::Imu Inertial(18);


//Variables
int drvtrDZ = 10;
int drvtrFB;
int drvtrLR;
int auton;
bool pl = false;
bool pr = false;
bool shieldRaised = false;
bool thr = false;