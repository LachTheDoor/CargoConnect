//----------------------------------------------------------------------------------------------------
// Name: encoderTurnFunctions
//----------------------------------------------------------------------------------------------------
// Description: Finds how much we want to move (in degrees). Gets rid of the brakes if they are on.
// resets the moter encoder. Check if we want to turn left or right by seeing if the degreesToTurn is 
// greater than or equal to 0. If we are turning to the right, the right wheel isn't moving and the
// left wheel is moving at the speed we want it to. If we are turning to the left, the left wheel is 
// stopped and the right wheel is moving at the speed we want. We wait for the left motor encoder to 
// be greater than or equal to the degreesToMove. Because we are stopped on the left or right encoder,
// we can add them together because one will always be zero. Turns off motors.
//----------------------------------------------------------------------------------------------------
//Inputs:
//	speed   	Float	Speed of the right wheel
//	degreesToTurn	Float	Distance to move
//	brakeMode	Bool	True = Turn on brakes at the end;  False = Coast at the end
//----------------------------------------------------------------------------------------------------
void sideTurnEncoder(float speed, float degreesToTurn, bool brakeMode)
{

	float degreesToMove;

	// Compute the degrees to move
	degreesToMove = abs(degreesToTurn) * 3.376162;

	// Remove the brakes if they are applied
	setDriveMotorsToCoast();

	// Reset the Motor Encoders
	resetDriveMotorEncoders();


	// Check if turning to the left or to the right

	if (degreesToTurn >= 0)					// Turning to the right  - right wheel stopped left wheel set to speed
	{

		setMotorSpeed(leftDrive, speed);
		setMotorSpeed(rightDrive, 0);

	}
	else														// Turning to the left  - left wheel stopped right wheel set to speed
	{
		setMotorSpeed(leftDrive, 0);
		setMotorSpeed(rightDrive, speed);

	}


	// Wait until the left motor encoder is greater than or equal to the degrees to move.
	// Because we are stopped on the left or right encoder, we can add them together because one will always be zero.
	while (abs(getLeftMotorEncoder()) + abs(getRightMotorEncoder()) <= degreesToMove)
	{

	}


	turnOffDriveMotors();

	setBrakeMode(brakeMode);

}
//----------------------------------------------------------------------------------------------------
// Name: centerTurnEncoder
//----------------------------------------------------------------------------------------------------
// Description: 
// Finds how much we want to move (in degrees). Gets rid of the brakes if they are on. Resets the motor
// encoder. Check if we want to turn left or right by seeing if the degreesToTurn is greater than or
// equal to 0. If we are turning to the right, the left motor is forward and the right motor is going 
// backwards. If we are turning to the left, the left motor is backwards and the right motor is going 
// forwards. Wait until the left motor encoder is greater than or equal to the degrees to move. Turns
// off motors.
//----------------------------------------------------------------------------------------------------
//Inputs:
//	speed   	Float	Speed of the right wheel
//	degreesToTurn	Float	Distance to move
//	brakeMode	Bool	True = Turn on brakes at the end;  False = Coast at the end
//----------------------------------------------------------------------------------------------------
void centerTurnEncoder(float speed, float degreesToTurn, bool brakeMode)
{

	float degreesToMove;

	// Compute the degrees to move
	degreesToMove = abs(degreesToTurn) * 1.688081;

	// Remove the brakes if they are applied
	setDriveMotorsToCoast();

	// Reset the Motor Encoders
	resetDriveMotorEncoders();


	// Check if turning to the left or to the right
	if (degreesToTurn >= 0)					// Turning to the right  - Left motor forward; right motor backward
	{

		setMotorSpeed(leftDrive, speed);
		setMotorSpeed(rightDrive, -speed);

	}
	else														// Turning to the left  - Left motor backward; right motor forward
	{
		setMotorSpeed(leftDrive, -speed);
		setMotorSpeed(rightDrive, speed);


	}

	// Wait until the left motor encoder is greater than or equal to the degrees to move.
	while (abs(getLeftMotorEncoder()) <= degreesToMove)
	{

	}


	turnOffDriveMotors();


	setBrakeMode(brakeMode);


}
