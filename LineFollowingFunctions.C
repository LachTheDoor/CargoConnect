//----------------------------------------------------------------------------------------------------
// Name: 
//----------------------------------------------------------------------------------------------------
// Description:
//
//----------------------------------------------------------------------------------------------------
//Inputs:
//
//----------------------------------------------------------------------------------------------------
void lineFollowForDistance(float rotations, float speed, int colorSensorToUse, int edgeToUse, bool brakeMode)

{

	// Dimensioning variables
	float error;
	float correctionFactor;
	float speedLeft;
	float speedRight;
	float degreesToMove;
	float gain;
	float colorSensorReading;
	float midPoint;


	midPoint = 55;
	gain = .01 * speed;


	// set motor encoder to 0
	resetMotorEncoder(leftDrive);
	resetMotorEncoder(rightDrive);

	// compute degrees wheel needs to move
	degreesToMove = rotations * 360;

	// move forward until the encoder value is greater then the degrees to move
	while (abs(getLeftMotorEncoder()) <= degreesToMove)
	{

		if (colorSensorToUse == 1)				// Use the left color sensor
		{
			colorSensorReading = getColorReflected(leftColor);
		}
		else														// Use the right color sensor
		{
			colorSensorReading = getColorReflected(rightColor);
		}


		// Setpoint that we want to go in - actual current reading
		error = midPoint - colorSensorReading;

		// Compute the correction factor
		correctionFactor = error * gain;

		// detecting what edge you are on
		if (edgeToUse == 1)		// 1 = left edge
		{
			speedLeft = speed - correctionFactor;
			speedRight = speed + correctionFactor;
		}
		else
		{
			speedLeft = speed + correctionFactor;
			speedRight = speed - correctionFactor;

		}

		setMotorSpeed(leftDrive, speedLeft);
		setMotorSpeed(rightDrive, speedRight);

	}


	turnOffDriveMotors();

	setBrakeMode(brakeMode);


}
