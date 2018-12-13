/*
 * \file SimplePerceptionStudy.cpp  --  EXTENSION RIGHT AND LEFT
 * \brief Experiment to evaluate what cues people perceive from simple haptic device
 * \communitates with arduino through serial port, use with file simple_perception_study.ino
 
*/

 // **************** //
 // **** INCLUDE *** //
 // **************** //
#include "stdafx.h"
//#include <unistd.h>


#ifdef _WIN32
#include <winsock2.h>

#elif __unix__
#include <sys/types.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h> 
#include <fcntl.h>
#include <errno.h>
#include <termios.h>
#define WSAGetLastError() errno
#endif




// ********************* //
// *** OTHER HEADERS *** //
// ********************* //
#include "SerialClass.h"
#include "data_storage.h"


// ************************** //
// ** ARDUINO COMMAND VALS ** //
// ************************** //
const int UP_INDEX = 6;
const int DOWN_INDEX = 7;
const int UP_THUMB = 8;
const int DOWN_THUMB = 9;
const int START_TRIALS = 1;


// *************************** //
// *** Function Prototypes *** //
// *************************** //
int keyboardHandler(int key);
int evaluate_selection(int key);
void trackerErrorHandler(int error);

// Serial port for communicating with Arduino
Serial* SP = new Serial("\\\\.\\COM3");

// timers
clock_t trialStartTime;
clock_t trialEndTime;
clock_t magTrackerTime;
clock_t lastRecording;

// magnetic tracker
bool trackingOn = true;
int errorCode;
int sensorID = 2;
FILE *rptr;
char trackerFilename[24];
DOUBLE_POSITION_ANGLES_RECORD magT, *pmagT = &magT;
CSystem			ATC3DG;
CSensor			*pSensor;
CXmtr			*pXmtr;
short id; 

// shared between keyboard and main
int user_response = 0;
int numPlays = 1;
int trialNum = -1; // start at -1 to press spacebar to get to 0
int orderNum = 0;
int participantNum;
int cues[TRIALS_MAX];
bool quit = false;
int cue = 0;
int state = SETUP;
int nextCommand = 0;


int evaluate_selection(int key) {
	switch (key) {
	case '1':
		//printf("	Forward.	 Press Enter to Submit.\n");
		printf("	Unclear.	 Press Enter to Submit.\n");
		state = WAITING_FOR_ENTER;
		return 1;
		break;

	case '2':
		printf("	Backward.	 Press Enter to Submit.\n");
		state = WAITING_FOR_ENTER;
		return 2;
		break;

	case '3':
		printf("	Tilt Up.	 Press Enter to Submit.\n");
		state = WAITING_FOR_ENTER;
		return 3;
		break;

	case '4':
		printf("	Tilt Down. 	 Press Enter to Submit.\n");
		state = WAITING_FOR_ENTER;
		return 4;
		break;

	case '5':
		printf("	Twist Left.	 Press Enter to Submit.\n");
		state = WAITING_FOR_ENTER;
		return 5;
		break;

	case '6':
		printf("	Twist Right. Press Enter to Submit.\n");
		state = WAITING_FOR_ENTER;
		return 6;
		break;

	case '7':
		printf("	Right >>>	 Press Enter to Submit.\n");
		state = WAITING_FOR_ENTER;
		return 7;
		break;
	
	case '8':
		printf("	<<< Left	 Press Enter to Submit.\n");
		state = WAITING_FOR_ENTER;
		return 8;
		break;

	default:
		printf("	Invalid entry.\n");
		break;
	}

	return 0;
}



int keyboardHandler(int key) {

	if (key == 'z') {
		printf("Quitting.\n");
		quit = true;
		return 0;
	}

	if (state == SETUP) {
		char message = 0;

		switch (key) {
		case 'o':
			printf("Increasing Index Finger Centerpoint.\n");
			//writeIntToSerialPort(serialConnection, UP_INDEX);
			message = UP_INDEX;
			break;
		case 'l':
			printf("Decreasing Index Finger Centerpoint.\n");
			//writeIntToSerialPort(serialConnection, DOWN_INDEX);
			message = DOWN_INDEX;
			break;
		case 'i':
			printf("Increasing Thumb Centerpoint.\n");
			//writeIntToSerialPort(serialConnection, DOWN_THUMB);
			message = DOWN_THUMB;
			break;
		case 'k':
			printf("Decreasing Thumb Centerpoint.\n");
			//writeIntToSerialPort(serialConnection, UP_THUMB);
			message = UP_THUMB;
			break;
		case ' ':
		case '+':
			state = BETWEEN_TRIALS;
			//writeIntToSerialPort(serialConnection, START_TRIALS);
			message = START_TRIALS;

			printf("\n\n--------------------------------------------------\n");
			printf("Beginning trials.");
			printf("\n--------------------------------------------------\n\n");

			printf("\n\nPress Spacebar to advance trials.\n");
			printf("Select response with number keys.\n");
			printf("Press Enter to submit final answer.\n");
			printf("Press Q to quit.\n\n\n");
		}

		// send to serial port
		SP->WriteData(message, 1);

		/// check response
		//char incomingData[256] = "";
		//int dataLength = 255;
		//int readResult = 0;
		//readResult = SP->ReadData(incomingData, dataLength);
		//printf("\n\nBytes read: (0 means no data available) %i\n", readResult);
		//printf("Arduino received: ");
		//printf(incomingData);
		//printf("\n");

	} //END OF: if (state == SETUP)

	else if (state == BETWEEN_TRIALS && (key == ' ' || key == '+')) {		// start next trial
		state = WAITING_FOR_INPUT;
		trialNum++;
		if (trialNum == TRIALS_MAX) {
			quit = true;
		}
		else {
			printf("Trial %d: \n", trialNum + 1);
			trialStartTime = clock();
			numPlays = 1;
			//// debuging
			////printf("VARIABLE trialNum +1: %d \n", trialNum + 1);
			////printf("OUTPUT SERIAL: %d\n", cues[trialNum]);
			SP->WriteData(cues[trialNum], 1);

			// Open new file to record tracked transformation matrix
			sprintf(trackerFilename, "user_movement_%d_%d_%d.txt", participantNum, trialNum, cues[trialNum]);
			if ((rptr = fopen(trackerFilename, "w")) == NULL)
			{
				printf("error: %s\n", strerror(WSAGetLastError()));
				exit(EXIT_FAILURE);
			}
		}

		return 0;
	}

	else if (state == WAITING_FOR_INPUT) {
		switch (key) {
		case ' ':
		case '+':
			SP->WriteData(cues[trialNum], 1);
			numPlays++;
			break;

		case '\n':
			printf("Please enter a response.\n");
			break;

		default:
			user_response = evaluate_selection(key);
			break;


		}
		return 0;
	}

	else if (state == WAITING_FOR_ENTER) {
		switch (key) {
		case '\n':
		case '\r':
		//case '8':
			if (trialNum == BREAK1 || trialNum == BREAK2) {
				printf("\nTake a break! \n\n");
			}
			state = BETWEEN_TRIALS;
			fclose(rptr);					// close magnetic tracker recording file
			trialEndTime = clock();
			return user_response;
			break;

		case ' ':
		case '+':
			//writeIntToSerialPort(serialConnection, cues[orderNum][trialNum]); 
			SP->WriteData(cues[trialNum], 1);
			numPlays++;
			break;

		default:
			user_response = evaluate_selection(key);

		}
		return 0;
	}

	return 0;

}


void trackerErrorHandler(int error)
{
	char			buffer[1024];
	char			*pBuffer = &buffer[0];
	int				numberBytes;

	while (error != BIRD_ERROR_SUCCESS)
	{
		error = GetErrorText(error, pBuffer, sizeof(buffer), SIMPLE_MESSAGE);
		numberBytes = strlen(buffer);
		buffer[numberBytes] = '\n';		// append a newline to buffer
		printf("%s", buffer);
		trackingOn = false;
	}
	//exit(0);
}




int main(void) 
{
	// keyboard and timer variables
	int c;

	clock_t clockTicksTaken;
	double trialTimeInSeconds;
	double magTrackerTimeout = 0.01;

	// SETUP  TASKS /////////////////////////
	printf("Enter Participant Number: ");
	participantNum = _getch() - '0';
	printf("%d\n", participantNum);				// which participant is being tested

	// create vector of cues 
	int row = 0; 
	int col, set;
	for ( set = 0; set < 5; set++) {
		row = orders[orderVec[participantNum]][set];
		for (col = 0; col < NUM_CONDITIONS; col++) {
			cues[NUM_CONDITIONS * set + col] = conditionOrders[row][col];
		}
	}

	orderNum = orderVec[participantNum]; 		// which row of sequences to call from for this participant
	printf("\n\n");

	printf("Do you want to use the magnetic tracker? (y/n)\n");		// is the magnetic tracker begin used?
	if (_getch() == 'y') {
		trackingOn = true;
		printf("Tracking On.\n");
	}
	else {
		trackingOn = false;
		printf("Tracking Off.");
	}
	printf("\n\n");

	// Initialize Serial Port connection to Arduino 
	printf("Confirming Serial Port...");
	if (SP->IsConnected()) {
		printf("OK\n");
	}
	else {
		printf("ERROR Connecting to Serial Port\n");
	}

	//Test serial connection by reading 
	char incomingData[361] = ""; //256
	int dataLength = 255;
	int readResult = 0;
	//printf("Test serial connection by reading\n");
	readResult = SP->ReadData(incomingData, dataLength);
	printf(incomingData);
	printf("\n");

	// Initialize Magnetic Tracker
	if (trackingOn) {
		printf("Initializing Magnetic Tracker");
		errorCode = InitializeBIRDSystem();
		if (errorCode != BIRD_ERROR_SUCCESS) trackerErrorHandler(errorCode);
		errorCode = GetBIRDSystemConfiguration(&ATC3DG.m_config);
		if (errorCode != BIRD_ERROR_SUCCESS) trackerErrorHandler(errorCode);

		pSensor = new CSensor[ATC3DG.m_config.numberSensors];
		for (int i = 0; i<ATC3DG.m_config.numberSensors; i++)
		{
			errorCode = GetSensorConfiguration(i, &(pSensor + i)->m_config);
			if (errorCode != BIRD_ERROR_SUCCESS) trackerErrorHandler(errorCode);
		}

		pXmtr = new CXmtr[ATC3DG.m_config.numberTransmitters];
		for (int i = 0; i<ATC3DG.m_config.numberTransmitters; i++)
		{
			errorCode = GetTransmitterConfiguration(i, &(pXmtr + i)->m_config);
			if (errorCode != BIRD_ERROR_SUCCESS) trackerErrorHandler(errorCode);
		}

		// Search for the first attached transmitter and turn it on
		for ( id = 0; id<ATC3DG.m_config.numberTransmitters; id++)
		{
			if ((pXmtr + id)->m_config.attached)
			{
				errorCode = SetSystemParameter(SELECT_TRANSMITTER, &id, sizeof(id));
				if (errorCode != BIRD_ERROR_SUCCESS) trackerErrorHandler(errorCode);
				break;
			}
		}
		printf("...OK\n");

	}

	// Open file to write user responses
	printf("Opening file... ");
	FILE *fptr;
	char filename[24];
	sprintf(filename, "user_responses_%d_%d.txt", participantNum, orderNum);

	if ((fptr = fopen(filename, "w")) == NULL)
	{
		printf("error: %s\n", strerror(WSAGetLastError()));
		exit(EXIT_FAILURE);
	}
	printf("OK\n");

	//fprintf(fptr, "Trial\t");
	//fprintf(fptr, "Time (s)\t");
	//fprintf(fptr, "Plays\t");
	//fprintf(fptr, "Cue Num\t");
	//fprintf(fptr, "Response");
	//fprintf(fptr, "\n");



	// START EXPERIMENT /////////////////////////////////////////////////////////
	printf("\n\n--------------------------------------------------\n");
	printf("Centering finger contacts.");
	printf("\n--------------------------------------------------\n\n");

	printf("\n\nPress I/K to adjust Index Finger, O/L to adjust Thumb.\n");
	printf("Press Spacebar when finished.\n");


	// Wait for user to advance trials and respond to cues
	while (!quit)
	{
		// respond to key presses (next trial, replay cue, or input selected direction)
		if (_kbhit()) {

			c = _getch();
			int response = keyboardHandler(c);

			if (response > 0) {

				clockTicksTaken = trialEndTime - trialStartTime;
				trialTimeInSeconds = clockTicksTaken / (double)CLOCKS_PER_SEC;


				fprintf(fptr, "%d\t", trialNum);
				fprintf(fptr, "%f\t", trialTimeInSeconds);
				fprintf(fptr, "%d\t", numPlays);
				fprintf(fptr, "%d\t", cues[trialNum]);
				fprintf(fptr, "%d\t", response);
				fprintf(fptr, "\n");

			}

		}

		// record transformation matrix periodically during trial
		if (trackingOn && (state == WAITING_FOR_INPUT || state == WAITING_FOR_ENTER) && !quit) {
			magTrackerTime = clock();

			// sensor attached so get record
			errorCode = GetAsynchronousRecord(sensorID, pmagT, sizeof(magT));
			if (errorCode != BIRD_ERROR_SUCCESS) { trackerErrorHandler(errorCode); }

			// get the status of the last data record
			// only report the data if everything is okay
			unsigned int status = GetSensorStatus(sensorID);

			if (status == VALID_STATUS)
			{

				if (((magTrackerTime - lastRecording) / (double)CLOCKS_PER_SEC) >= magTrackerTimeout) {
					lastRecording = magTrackerTime;
					errorCode = GetAsynchronousRecord(sensorID, pmagT, sizeof(magT));
					// print recording time
					fprintf(rptr, "%f\t", (double)magTrackerTime);
					// print position
					fprintf(rptr, "%f\t %f\t %f\t", magT.x, magT.y, magT.z);
					// print angles
					fprintf(rptr, "%f\t %f\t %f\t", magT.a, magT.e, magT.r);
					fprintf(rptr, "\n");
				}
			}

		}

	}


	if (trialNum == TRIALS_MAX) {
		printf("\n--------------------------------------------------\n");
		printf("Trials completed.");
		printf("\n--------------------------------------------------\n\n");
	}
	else {
		printf("\n--------------------------------------------------\n");
		printf("Closing program on trial number %d.", trialNum);
		printf("\n--------------------------------------------------\n\n");
	}


	// Close serial port   	
	//close(serialConnection);

	if (trackingOn) {
		// Turn off the transmitter before exiting
		id = -1;
		errorCode = SetSystemParameter(SELECT_TRANSMITTER, &id, sizeof(id));
		if (errorCode != BIRD_ERROR_SUCCESS) trackerErrorHandler(errorCode);
		//  Free memory allocations before exiting
		delete[] pSensor;
		delete[] pXmtr;
	}

	// Close file
	fclose(fptr);

	//changemode(0);

	return EXIT_SUCCESS;
}
