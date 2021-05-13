// device.cpp - Class definition for IoT Device
// CNS Group 7
// May 12, 2021

#include "device.hpp"
#include <stdlib.h>
#include <time.h>


// Intializers
//
Device::Device() {
	ID = "";
	password = "";
	networkPass = "";
	inputBuffer = "";
	outputBuffer = "";
	holdableConnections = 3;
	for (int i = 0; i < holdableConnections; ++i)
		connectionIDs.push_back("");
	setup = false;
}

Device::Device(int holdableConns) {
	ID = "";
	password = "";
	networkPass = "";
	inputBuffer = "";
	outputBuffer = "";
	holdableConnections = holdableConns;
	for (int i = 0; i < holdableConnections; ++i)
		connectionIDs.push_back("");
	setup = false;
}



// Setup IoT device method
// like turning the device on for the first time, returns device's password
string Device::initialSetup(string id, string netPass) {

	if (!setup) {
		srand(time(NULL)); // seed random based on time for unique password

		ID = id;
		password = generatePassword();
		networkPass = netPass;
		outputBuffer = "ID: " + ID + "| Network Key: " + netPass;
		setup = true;

		return password;
	}

	return "e1";		// error code 1: device already setup
	
}



// Connect to Device
// attempts connection to iot device
int Device::connect(string pass, string netPass, string connection) {
	
	if (pass != password) // if incorrect password
		return 2;	// error code 2: incorrect password
	if (netPass != networkPass) // if incorrect network key
		return 3;	// error code 3: incorrect network

	// ensure connection not already made
	for (int i = 0; i < holdableConnections; ++i) {
		if (connectionIDs[i] == connection) {
			return 5;	// error code 5: specified connection already made
		}
	}

	// ensure device can hold another connection
	for (int i = 0; i < holdableConnections; ++i) {
		if (connectionIDs[i] == "") {
			connectionIDs[i] = connection;
			return 0;	// connection successful
		}
	}

	return 4;	// error code 4: no more connection slots

}



// Disconnect from Device
// 
int Device::disconnect(string connection, string netPass) {
	
	if (netPass != networkPass) // if incorrect network key
		return 3;	// error code 3: incorrect network

	// ensure connection is already made
	for (int i = 0; i < holdableConnections; ++i) {
		if (connectionIDs[i] == connection) {
			connectionIDs[i] = "";
			return 0;
		}
	}

	return 6;	// error code 6: connection does not exist

}



// Send to Device
// send some data to this device's input
int Device::send(string connection, string netPass, string data) {

	if (netPass != networkPass) // if incorrect network key
		return 3;	// error code 3: incorrect network

	// ensure connection exists
	for (int i = 0; i < holdableConnections; ++i) {
		if (connectionIDs[i] == connection) {
			outputBuffer = inputBuffer;
			inputBuffer = data;
			return 0; // data send successful
		}
	}

	return 6; // error code 6: connection does not exist

}



// Retrieve from Device
// gets data from output buffer
string Device::retrieve(string connection, string netPass) {
	
	if (netPass != networkPass) // if incorrect network key
		return "e3";	// error code 3: incorrect network

	// ensure connection exists
	for (int i = 0; i < holdableConnections; ++i) {
		if (connectionIDs[i] == connection) {
			return outputBuffer; // successful retrieval
			outputBuffer = inputBuffer;
		}
	}

	return "e6"; // error code 6: connection does not exist

}



// Generate Device Password
// random 10 digit alpha-numeric
string Device::generatePassword() {

	string newPass = "";

	for (int i = 0; i < 10; ++i) {
	
		// 50/50 for number or letter
		int numOrLet = rand() % 2;

		// number
		if (numOrLet == 0) {
			newPass = newPass + std::to_string(rand() % 10);
		}
		// letter
		else {
			int randLet = rand() % 26;
			// select random letter
			if (randLet == 0) newPass += 'a';
			if (randLet == 1) newPass += 'b';
			if (randLet == 2) newPass += 'c';
			if (randLet == 3) newPass += 'd';
			if (randLet == 4) newPass += 'e';
			if (randLet == 5) newPass += 'f';
			if (randLet == 6) newPass += 'g';
			if (randLet == 7) newPass += 'h';
			if (randLet == 8) newPass += 'i';
			if (randLet == 9) newPass += 'j';
			if (randLet == 10) newPass += 'k';
			if (randLet == 11) newPass += 'l';
			if (randLet == 12) newPass += 'm';
			if (randLet == 13) newPass += 'n';
			if (randLet == 14) newPass += 'o';
			if (randLet == 15) newPass += 'p';
			if (randLet == 16) newPass += 'q';
			if (randLet == 17) newPass += 'r';
			if (randLet == 18) newPass += 's';
			if (randLet == 19) newPass += 't';
			if (randLet == 20) newPass += 'u';
			if (randLet == 21) newPass += 'v';
			if (randLet == 22) newPass += 'w';
			if (randLet == 23) newPass += 'x';
			if (randLet == 24) newPass += 'y';
			if (randLet == 25) newPass += 'z';
			if (randLet >= 26) newPass += 'A';
		}
	
	}

	return newPass;

}



// ID Getter
// so that other network devices can see this one
string Device::getID() { return ID; }

// Pass Getter
// so that, in this simulator, device can use its own password in the connect call if needed
string Device::getPass() { return password; }