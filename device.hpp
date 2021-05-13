// device header file
// CNS Group 7
// May 12, 2021

#ifndef DEVICE_HPP
#define DEVICE_HPP

#include <iostream>
#include <string>
#include <vector>
#include <Utility>

using std::string; using std::vector;
using std::pair; using std::make_pair;

class Device {
public:

	// Methods
	Device();
	Device(int holdableConns);

	string initialSetup(string id, string netPass);
	string getID();
	string getPass();
	int   connect(string pass, string netPass, string connection);
	int   disconnect(string connection, string netPass);
	int   send(string connection, string netPass, string data);
	string retrieve(string connection, string netPass);
	

private:

	// Properties
	std::string ID;
	string password;
	string networkPass;
	string inputBuffer;
	string outputBuffer;
	vector<string> connectionIDs;

	int holdableConnections;
	bool setup;

	// Methods
	string generatePassword();

};



struct Network {
public:

	// properties
	vector<pair<string, string>> connections;
	string ID;
	string password;

};

struct Attacker {
public:

	// properties
	string ID;
	string networkPass;
	string password;

};



#endif // !DEVICE_HPP

