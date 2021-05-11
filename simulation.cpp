// simulation.cpp - Main func for simulating iot security
// CNS Group 7
// May 12, 2021

#include <iostream>
#include "device.hpp"

using std::cin; using std::cout; using std::endl;
using std::pair; using std::make_pair;

string handleError(int code);

int main()
{
    // Intro
    cout << "\n\n\nWelcome to IoT Security Simulator!\nCreated by: Ahmed Alsaleh, Congwu Li, Chai-Rex Lin & Elliott Ullman\n" << endl;
    cout << "Standard Setup: Network + IoT Device + Malicious Device/Attacker\n" << endl;

    // buffers for handling inputs and error throws
    string input1;
    string input2;
    int errorBuffer;

    // Initial the network controller
    Network network;
    cout << "(Identifiers can be IPs or just names for devices, but they should be unique within the simulation)" << endl;
    cout << "Your network identifier:"; cin >> input1;
    network.ID = input1;
    cout << "Your network password (10 digit alpha-numeric highly suggested):"; cin >> input1;
    network.password = input1;
    cout << "Network: " + network.ID + " | Password: " + network.password << endl << endl;

    // Setup the initial iot device, more can be setup later
    vector<Device*> iotDevices;
    iotDevices.push_back(new Device());
    cout << "Your IoT device identifier:"; cin >> input1;
    cout << "Performing initial setup of your IoT device using your network password as the network key..." << endl;
    input2 = iotDevices[0]->initialSetup(input1, network.password);
    cout << "\nID: " + iotDevices[0]->getID() + " | Password: " + input2 << endl << endl;
    cout << "Your IoT device is initialized to connect only with devices on your network, per your network password.\n";
    cout << "However, it is not yet connected, would you like to do so now? (The device's password is not stored, so";
    cout << " if you plan on connecting the device later, you need to have the password memorized." << endl;
    cout << "Type 'y' to connect now: "; cin >> input1;
    if (input1 == "y") {
        cout << endl << "Connecting your device to " + network.ID << " ..." << endl;
        errorBuffer = iotDevices[0]->connect(input2, network.password, network.ID);
        if (errorBuffer != 0)
            cout << "Connection refused with code: " + handleError(errorBuffer) << endl;
        else {
            network.connections.push_back(make_pair(iotDevices[0]->getID(), input2));
            cout << iotDevices[0]->getID() + " connected to " + network.ID << endl;
        }
    }

    // Setup of attacker device
    Attacker attacker;
    cout << endl << "Setting up malicious device..." << endl;
    cout << "The malicious device will be completely customizable so that you can test the limits of this IoT security.";
    cout << endl << "For now, we'll just give it an identifier: "; cin >> input1;
    attacker.ID = input1;

    
}



// function for handling errors
string handleError(int code) {

    if (code == 0)
        return "0:Operation Successful";
    else if (code == 1)
        return "1:Device has already been setup";
    else if (code == 2)
        return "2:Incorrect device password";
    else if (code == 3)
        return "3:Incorrect network pass";
    else if (code == 4)
        return "4:No more connections available";
    else if (code == 5)
        return "5:Specified connection has already been made";
    else if (code == 6)
        return "6:Specified connection does not exist";
    else
        return "x:Unknown error";

}
