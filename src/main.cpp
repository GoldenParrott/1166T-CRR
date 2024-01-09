#include "main.h"
#include "init.h"

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	pros::lcd::initialize();
	
	pros::lcd::set_text(0, "1166T - Technically Legal");

	Intake.move_velocity(100);
	AllWheels.move_velocity(100);
	Arm.move_velocity(100);
	PlowLeft.set_value(false);
	PlowRight.set_value(false);
	ShieldLeft.set_value(false);
	ShieldRight.set_value(false);


}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {
	PlowLeft.set_value(false);
	PlowRight.set_value(false);
	ShieldLeft.set_value(false);
	ShieldRight.set_value(false);
}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {

	Inertial.reset();
	pros::lcd::set_text(0, "1166T - Technically Legal");
	pros::lcd::set_text(1, "Current: None Selected");
	pros::lcd::set_text(2, "Press the left button for near");
	pros::lcd::set_text(3, "autonomous");
	pros::lcd::set_text(4, "Press the middle button for far");
	pros::lcd::set_text(5, "autonomous");
	pros::lcd::set_text(6, "Press the right button for");
	pros::lcd::set_text(7, "autonomous skills");
	autonnumber = 3;
  //Selector for Multuple Autons
	while(true){
		if (pros::lcd::read_buttons() == 2){
			//Far Auton
			autonnumber = 1;
			pros::lcd::set_text(1, "Current: Far Autonomous");
			Inertial.reset();
		}else if(pros::lcd::read_buttons() == 4){
			//Near Auton
			autonnumber = 2;
			pros::lcd::set_text(1, "Current: Near Autonomous");
			Inertial.reset();
		}else if(pros::lcd::read_buttons() == 1){
			//Skills Auton
			autonnumber = 3;
			pros::lcd::set_text(1, "Current: Autonomous Skills");
			Inertial.reset();
		}
		pros::delay(50);
	}
}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
	AllWheels.set_brake_modes(MOTOR_BRAKE_HOLD);
	Arm.tare_position();
	/*
	ShieldLeft.set_value(true);
	pros::delay(50);
	ShieldLeft.set_value(false);
	*/
	if(autonnumber == 1){

		//Far Auton

	}else if(autonnumber == 2){

		//Near Auton

	}else if(autonnumber == 3){

		//Skills Auton
		AllWheels.set_brake_modes(MOTOR_BRAKE_COAST);
		Arm.move(128);
		LeftWheels.move(-128);
		waitUntil((Inertial.get_heading() > 340)&&(Inertial.get_heading() < 350));
		AllWheels.brake();
	//Line up to shoot triballs
		waitUntil(ArmLeft.get_position()>(13*360));
		Arm.brake();
	//Shooting triballs
		//Indexer.move(128);
		//waitUntil(Indexer.get_position()>(168*360));
		//Indexer.brake();
	//Putting the arm back to a lowered position
		Arm.move(-128);
		waitUntil(ArmLeft.get_position()<(0.25*360));
		Arm.brake();
	//Lining up to drive underneath the elvation bar
		LeftWheels.move(64);
		waitUntil((Inertial.get_heading() > 25)&&(Inertial.get_heading() < 30));
		RightWheels.move(64);
		LeftWheels.brake();
		waitUntil((Inertial.get_heading() > 0)&&(Inertial.get_heading() < 10));
		AllWheels.brake();
		pros::delay(100);
	//Driving underneath the elevation bar
		AllWheels.move(128);
		AllWheels.set_brake_modes(MOTOR_BRAKE_HOLD);
	  //Checks to see if we pass the vertical pole
		waitUntil(Delta.get()<300);
	  //Looks forward to know when to stop
		waitUntil(Alpha.get()<1000);
		AllWheels.move(64);
		waitUntil(Alpha.get()<600);
		AllWheels.brake();
	//Drives diagonally to the goal
		PlowLeft.set_value(true);
		RightWheels.move(64);
		waitUntil((Inertial.get_heading() > 310)&&(Inertial.get_heading() < 315));
		AllWheels.brake();
		AllWheels.move(128);
		waitUntil(Beta.get()>685)
	//Drives into the side of the goal
		RightWheels.move(64);
		waitUntil((Inertial.get_heading() > 270)&&(Inertial.get_heading() < 273));
		AllWheels.brake();
		PlowLeft.set_value(false);
	//Repeatedly (twice) driveing into the goal to push triballs in
		AllWheels.move(128);
		pros::delay(1500);
		AllWheels.move(-128);
		pros::delay(1500);
		AllWheels.move(128);
		pros::delay(1500);
		AllWheels.move(-128);
		pros::delay(750);
		AllWheels.brake();

		
	}
}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {

	AllWheels.set_brake_modes(MOTOR_BRAKE_COAST);
	
	while (true) {

	//Drivetrain
    	drvtrFB = Master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
    	drvtrLR = Master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

		if((abs(drvtrFB) > drvtrDZ) || (abs(drvtrLR) > drvtrDZ)) {
      		// ^^ Checks to see if either joystick has moved out of the deadzone
      		RightWheels.move((drvtrFB-drvtrLR));
      		LeftWheels.move((drvtrFB+drvtrLR));
    	} else {
      		RightWheels.brake();
      		LeftWheels.brake();
    	}  

	//Indexer
		int cancelShot;
		if (Epsilon.get() <= 120) {
			cancelShot = false;
		} else {
			cancelShot = true;
		}

	  //Single-Shot
		if(Master.get_digital(DIGITAL_X)==true){
			Indexer.move_relative(360,100);
		}

	  //Rapid-Fire
	  	if(Master.get_digital(DIGITAL_Y)==true){
			Indexer.move(128);
			waitUntil(Master.get_digital(DIGITAL_Y)==false);
			Indexer.brake();
		}

	
	  //Rapid-Fire With Check
	  	if(Master.get_digital(DIGITAL_B)==true){
			Indexer.move(128);
			waitUntil(Master.get_digital(DIGITAL_Y)==false);
			Indexer.brake();
		}

	  //Rewind
		if(Master.get_digital(DIGITAL_A)==true){
			Indexer.move(-128);
			waitUntil(Master.get_digital(DIGITAL_A)==false);
			Indexer.brake();
		}

	//Arm
		if(Master.get_digital(DIGITAL_DOWN)==true){
			Arm.move(-128);
		}else if(Master.get_digital(DIGITAL_UP)==true){
			Arm.move(128);
		} else {
			Arm.brake();
		}

	//Intake
		if(Master.get_digital(DIGITAL_RIGHT)==true){
			Intake.move(-128);
		} else if(Master.get_digital(DIGITAL_LEFT)==true){
			Intake.move(128);
		} else {
			Intake.brake();
		}

	//Plows
	  //Left plow
		if((Master.get_digital(DIGITAL_L2)==true)&&(pl==false)){
			PlowLeft.set_value(true);
			waitUntil(Master.get_digital(DIGITAL_L2)==false);
			pl = true;
		}
		if((Master.get_digital(DIGITAL_L2)==true)&&(pl==true)){
			PlowLeft.set_value(false);
			waitUntil(Master.get_digital(DIGITAL_L2)==false);
			pl = false;
		}

	  //Right plow
		if((Master.get_digital(DIGITAL_R2)==true)&&(pr==false)){
			PlowRight.set_value(true);
			waitUntil(Master.get_digital(DIGITAL_R2)==false);
			pr = true;
		}
		if((Master.get_digital(DIGITAL_R2)==true)&&(pr==true)){
			PlowRight.set_value(false);
			waitUntil(Master.get_digital(DIGITAL_R2)==false);
			pr = false;
		}

	//Shield
		if((Master.get_digital(DIGITAL_L1)==true)&&(shieldRaised==false)){
			ShieldLeft.set_value(true);
			ShieldRight.set_value(true);
			waitUntil(Master.get_digital(DIGITAL_L1)==false);
			shieldRaised = true;
		}else if((Master.get_digital(DIGITAL_L1)==true)&&(shieldRaised==true)){
			ShieldLeft.set_value(false);
			ShieldRight.set_value(false);
			waitUntil(Master.get_digital(DIGITAL_L1)==false);
			shieldRaised = false;
		}

	//Tether
		if ((Master.get_digital(DIGITAL_R1)==true)&&(thr==false)){
			Tether.set_value(true);
			waitUntil(Master.get_digital(DIGITAL_R1)==false);
			thr = true;
		}else if ((Master.get_digital(DIGITAL_R1)==true)&&(thr==true)){
			Tether.set_value(false);
			waitUntil(Master.get_digital(DIGITAL_R1)==false);
			thr = false;
		}
		
	//
	
	pros::delay(50);
	}
}
