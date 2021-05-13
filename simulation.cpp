// simulation.cpp - Main func for simulating iot security
// CNS Group 7
// May 12, 2021

#include <iostream>
#include "device.hpp"

using std::cin; using std::cout; using std::endl;
using std::pair; using std::make_pair;

string handleError(int code);
void standardSetup(Network &network, vector<Device*> &iotDevices, Attacker &attacker);

void printSelectOp(string &input);
void printMainOps();
void printNetworkOps();
void printDeviceOps();
void printAttackOps();
void printInvalidOps(string op);
void printExit();

int main()
{
    // Intro
    cout << "\n\n\nWelcome to IoT Security Simulator!\nCreated by: Ahmed Alsaleh, Congwu Li, Chai-Rex Lin & Elliott Ullman\n" << endl;

    // buffers for handling inputs and error throws
    string input1 = "";
    string input2 = "";
    int errorBuffer = 0;

    //network controller
    Network network;
    //iot device(s)
    vector<Device*> iotDevices;
    //attacker device
    Attacker attacker;

    //standard setup = main network, 1 iot device, and 1 attacker
    standardSetup(network, iotDevices, attacker);

    cout << "\n\nStarting simulation..\n\n";

    // Simulator main loop
    //
    while (input1 != "0") {
    
        input1 = "";
        input2 = "";
        errorBuffer = 0;

        printMainOps();
        printSelectOp(input1);

        // network operations
        if (input1 == "1") {
            printNetworkOps();
            printSelectOp(input1);

            if (input1 == "1") {    // connect to a device
                cout << "Which device would you like to connect to?" << endl;
                printSelectOp(input1);

                // ensure device exists
                bool deviceExists = false;
                for (int i = 0; i < static_cast<int>(iotDevices.size()); ++i) {
                    if (iotDevices[i]->getID() == input1) {
                        deviceExists = true;
                        // check the network's list of connections
                        bool connectionExists = false;
                        for (int k = 0; k < static_cast<int>(network.connections.size()); ++k) {
                            if (network.connections[k].first == input1) {
                                connectionExists = true;
                                cout << "Network is already aware of device..." << endl;
                                cout << "Attempting to connect using device's known password: ";
                                cout << network.connections[k].second << endl;
                                cout << "As: " + network.ID + " | With network pass: " + network.password << endl;
                                errorBuffer = iotDevices[i]->connect(network.connections[k].second, network.password, network.ID);
                                if (errorBuffer != 0) {
                                    cout << "Connection REFUSED with code: " + handleError(errorBuffer) << endl;
                                }
                                else {
                                    cout << "Connection SUCCESSFUL" << endl;
                                }
                            }
                        }
                        if (!connectionExists) {
                            cout << "Network is unaware of device..." << endl;
                            cout << "A device password is needed to attempt a connection" << endl;
                            printSelectOp(input2);
                            cout << "Attempting to connect using password: ";
                            cout << input2 << endl;
                            cout << "As: " + network.ID + " | With network pass: " + network.password << endl;
                            errorBuffer = iotDevices[i]->connect(input2, network.password, network.ID);
                            if (errorBuffer != 0) {
                                cout << "Connection REFUSED with code: " + handleError(errorBuffer) << endl;
                            }
                            else {
                                cout << "Connection SUCCESSFUL" << endl;
                                network.connections.push_back(make_pair(input1, input2));
                            }

                        }
                    }
                }

                if (!deviceExists)
                    cout << "Sorry, no '" + input1 + "' device exists..." << endl;

            }

            else if (input1 == "2") {   // disconnect from a device
            
                cout << "Which device would you like to disconnect from?" << endl;
                cout << "(Even if a disconnect is successful, the network will remember the device's ID";
                cout << " and password for future connections)" << endl;
                printSelectOp(input1);

                // ensure device exists
                bool deviceExists = false;
                for (int i = 0; i < static_cast<int>(iotDevices.size()); ++i) {
                    if (iotDevices[i]->getID() == input1) {
                        deviceExists = true;
                        // check the network's list of connections
                        bool connectionExists = false;
                        for (int k = 0; k < static_cast<int>(network.connections.size()); ++k) {
                            if (network.connections[k].first == input1) {
                                connectionExists = true;
                                cout << "Network is aware of device..." << endl;
                                cout << "Attempting to disconnect from: " + input1 << endl;
                                cout << "As: " + network.ID + " | With network pass: " + network.password << endl;
                                errorBuffer = iotDevices[i]->disconnect(network.ID, network.password);
                                if (errorBuffer != 0) {
                                    cout << "Disconnect REFUSED with code: " + handleError(errorBuffer) << endl;
                                }
                                else {
                                    cout << "Disconnect SUCCESSFUL" << endl;
                                }
                            }
                        }
                        if (!connectionExists) {
                            cout << "Network is unaware of device..." << endl;
                            cout << "A device password is needed to attempt a connection" << endl;
                            printSelectOp(input2);
                            cout << "Attempting to connect using password: ";
                            cout << input2 << endl;
                            cout << "As: " + network.ID + " | With network pass: " + network.password << endl;
                            errorBuffer = iotDevices[i]->connect(input2, network.password, network.ID);
                            if (errorBuffer != 0) {
                                cout << "Connection REFUSED with code: " + handleError(errorBuffer) << endl;
                            }
                            else {
                                cout << "Connection SUCCESSFUL" << endl;
                                network.connections.push_back(make_pair(input1, input2));
                            }

                        }
                    }
                }

                if (!deviceExists)
                    cout << "Sorry, no '" + input1 + "' device exists..." << endl;
            
            }

            else if (input1 == "3") {   // send data to a device
            
                cout << "Which device would you like to send data to?" << endl;
                printSelectOp(input1);

                // ensure device exists
                bool deviceExists = false;
                for (int i = 0; i < static_cast<int>(iotDevices.size()); ++i) {
                    if (iotDevices[i]->getID() == input1) {
                        deviceExists = true;
                        cout << "What data would you like to send?" << endl;
                        printSelectOp(input2);

                        // check the network's list of connections
                        bool connectionExists = false;
                        for (int k = 0; k < static_cast<int>(network.connections.size()); ++k) {
                            if (network.connections[k].first == input1) {
                                connectionExists = true;
                                cout << "Network is aware of device..." << endl;
                                cout << "Attempting to send: " + input2 << endl;
                                cout << "As: " + network.ID + " | With network pass: " + network.password << endl;
                                errorBuffer = iotDevices[i]->send(network.ID, network.password, input2);
                                if (errorBuffer != 0) {
                                    cout << "Send REFUSED with code: " + handleError(errorBuffer) << endl;
                                }
                                else {
                                    cout << "Send SUCCESSFUL" << endl;
                                }
                            }
                        }
                        if (!connectionExists) {
                            cout << "Network not aware of device..." << endl;
                            cout << "Attempting send operation regardless..." << endl;
                            cout << "Attempting to send: " + input2 << endl;
                            cout << "As: " + network.ID + " | With network pass: " + network.password << endl;
                            errorBuffer = iotDevices[i]->send(network.ID, network.password, input2);
                            if (errorBuffer != 0) {
                                cout << "Send REFUSED with code: " + handleError(errorBuffer) << endl;
                            }
                            else {
                                cout << "Send SUCCESSFUL" << endl;
                            }

                        }
                    }
                }

                if (!deviceExists)
                    cout << "Sorry, no '" + input1 + "' device exists..." << endl;
            
            }

            else if (input1 == "4") {   // retrieve data from a device
            
                cout << "Which device would you like to retrieve data from?" << endl;
                printSelectOp(input1);

                // ensure device exists
                bool deviceExists = false;
                for (int i = 0; i < static_cast<int>(iotDevices.size()); ++i) {
                    if (iotDevices[i]->getID() == input1) {
                        deviceExists = true;

                        // check the network's list of connections
                        bool connectionExists = false;
                        for (int k = 0; k < static_cast<int>(network.connections.size()); ++k) {
                            if (network.connections[k].first == input1) {
                                connectionExists = true;
                                cout << "Network is aware of device..." << endl;
                                cout << "Attempting to retrieve data from: " + input1 << endl;
                                cout << "As: " + network.ID + " | With network pass: " + network.password << endl;
                                input2 = iotDevices[i]->retrieve(network.ID, network.password);
                                errorBuffer = 0;
                                if (input2 == "e3") errorBuffer = 3;
                                if (input2 == "e6") errorBuffer = 6;
                                if (errorBuffer != 0) {
                                    cout << "Retrieval REFUSED with code: " + handleError(errorBuffer) << endl;
                                }
                                else {
                                    cout << "Retrieval SUCCESSFUL" << endl;
                                    cout << "Data Retrieved: " + input2 << endl;
                                }
                            }
                        }
                        if (!connectionExists) {
                            cout << "Network not aware of device..." << endl;
                            cout << "Attempting send operation regardless..." << endl;
                            cout << "Attempting to send: " + input2 << endl;
                            cout << "As: " + network.ID + " | With network pass: " + network.password << endl;
                            errorBuffer = iotDevices[i]->send(network.ID, network.password, input2);
                            if (errorBuffer != 0) {
                                cout << "Send REFUSED with code: " + handleError(errorBuffer) << endl;
                            }
                            else {
                                cout << "Send SUCCESSFUL" << endl;
                            }

                        }
                    }
                }

                if (!deviceExists)
                    cout << "Sorry, no '" + input1 + "' device exists..." << endl;

            }

            else if (input1 == "0") {   // exit
            
                printExit();

            }

            else {
            
                // 5 = return to main operations
                if (input1 != "5") printInvalidOps(input1);
            
            }

        }


        // iot operations
        else if (input1 == "2") {
            printDeviceOps();
            printSelectOp(input1);

            if (input1 == "1") {    // connect to a device/network
                cout << "Which device/network would you like to connect to?" << endl;
                printSelectOp(input1);

                if (input1 == network.ID) { // connecting to network?
                    cout << "Attempting to connect device to '" + network.ID + "' network..." << endl;
                    cout << "A network password is needed..." << endl;
                    printSelectOp(input2);
                    errorBuffer = iotDevices[0]->connect(iotDevices[0]->getPass(), input2, network.ID);
                    if (errorBuffer != 0) {
                        cout << "Connect REFUSED with code: " + handleError(errorBuffer) << endl;
                    }
                    else {
                        cout << "Connect SUCCESSFUL" << endl;
                        network.connections.push_back(make_pair(iotDevices[0]->getID(), iotDevices[0]->getPass()));
                    }
                }
                else if (input1 == attacker.ID) { // connecting to the attacker
                    cout << "Attempting to connect device to '" + attacker.ID + "' device..." << endl;
                    errorBuffer = iotDevices[0]->connect(iotDevices[0]->getPass(), attacker.networkPass, attacker.ID);
                    if (errorBuffer != 0) {
                        cout << "Connect REFUSED with code: " + handleError(errorBuffer);
                        if (errorBuffer == 3) cout << " (on the end of'" + attacker.ID + "')";
                        cout << endl;
                    }
                    else {
                        cout << "Connect SUCCESSFUL" << endl;
                    }
                }
                else 
                    cout << "Sorry, no other '" + input1 + "' device exists..." << endl;

            }

            else if (input1 == "2") {   // disconnect from a device/network

                cout << "Which device/network would you like to disconnect from?" << endl;
                cout << "(Even if a disconnect is successful, the device will hold the same network key)" << endl;
                printSelectOp(input1);

                if (input1 == network.ID) { // disconnecting from network
                    cout << "Attempting to disconnect from '" + network.ID + "' network..." << endl;
                    errorBuffer = iotDevices[0]->disconnect(network.ID, network.password);
                    if (errorBuffer != 0) {
                        cout << "Disconnect REFUSED with code: " + handleError(errorBuffer) << endl;
                    }
                    else {
                        cout << "Disconnect SUCCESSFUL" << endl;
                    }
                }
                else if (input1 == attacker.ID) { // disconnecting from the attacker
                    cout << "Attempting to disconnect from '" + attacker.ID + "' device..." << endl;
                    if (attacker.ID == network.ID)
                        errorBuffer = 8;
                    else
                        errorBuffer = iotDevices[0]->disconnect(attacker.ID, attacker.networkPass);
                    if (errorBuffer != 0) {
                        cout << "Disconnect REFUSED with code: " + handleError(errorBuffer) << endl;
                    }
                    else {
                        cout << "Disconnect SUCCESSFUL" << endl;
                    }
                }
                else
                    cout << "Sorry, no other '" + input1 + "' device exists..." << endl;

            }

            else if (input1 == "3") {   // send data to a device/network

                cout << "Which device/network would you like to send data to?" << endl;
                printSelectOp(input1);

                if (input1 == network.ID) { // sending to network
                    cout << "What data would you like to send?" << endl;
                    printSelectOp(input2);

                    cout << "Attempting to send '" + input2 + "' to: " + network.ID << endl;
                    errorBuffer = iotDevices[0]->send(network.ID, network.password, input2);
                    if (errorBuffer != 0) {
                        cout << "Send REFUSED with code: " + handleError(errorBuffer) << endl;
                    }
                    else {
                        cout << "Send SUCCESSFUL" << endl;
                    }
                }
                else if (input1 == attacker.ID) { // sending to the attacker
                    cout << "What data would you like to send?" << endl;
                    printSelectOp(input2);

                    cout << "Attempting to send '" + input2 + "' to: " + attacker.ID << endl;
                    if (attacker.ID == network.ID)
                        errorBuffer = 8;
                    else
                        errorBuffer = iotDevices[0]->send(attacker.ID, attacker.networkPass, input2);
                    if (errorBuffer != 0) {
                        cout << "Send REFUSED with code: " + handleError(errorBuffer);
                        if (errorBuffer == 3) cout << " (on the end of'" + attacker.ID + "')";
                        cout << endl;
                    }
                    else {
                        cout << "Send SUCCESSFUL" << endl;
                    }
                }
                else
                    cout << "Sorry, no other '" + input1 + "' device exists..." << endl;

            }

            else if (input1 == "0") {   // exit

                printExit();

            }

            else {

                // 4 = return to main operations
                if (input1 != "4") printInvalidOps(input1);

            }

        }


        // attacker operations
        else if (input1 == "3") {
            printAttackOps();
            printSelectOp(input1);

            if (input1 == "1") {    // change ID
                cout << "Replacing ID of '" + attacker.ID + "' to..." << endl;
                printSelectOp(input1);
                attacker.ID = input1;
                cout << "Done." << endl;
            }

            else if (input1 == "2") {    // change netPass
                cout << "Replacing stored network pass of '" + attacker.ID + "' to..." << endl;
                printSelectOp(input1);
                attacker.networkPass = input1;
                cout << "Done." << endl;
            }

            else if (input1 == "3") {    // change password
                cout << "Replacing stored password of '" + attacker.ID + "' to..." << endl;
                printSelectOp(input1);
                attacker.password = input1;
                cout << "Done." << endl;
            }

            else if (input1 == "4") {   // connect to device/network
                cout << "What would you like to connect to?" << endl;
                printSelectOp(input1);

                if (input1 == iotDevices[0]->getID()) { // attacking iotDevice
                    cout << "Attempting to connect to " + input1 + " using stored network pass and password..." << endl;
                    errorBuffer = iotDevices[0]->connect(attacker.password, attacker.networkPass, attacker.ID);
                    if (errorBuffer != 0) {
                        cout << "Connect REFUSED with code: " + handleError(errorBuffer) << endl;
                    }
                    else {
                        cout << "Connect SUCCESSFUL" << endl;
                    }
                }
                else if (input1 == network.ID) {    // attacking net
                    cout << "Attempting to connect to " + input1 + " using stored network pass..." << endl;
                    errorBuffer = iotDevices[0]->connect(iotDevices[0]->getPass(), attacker.networkPass, attacker.ID);
                    if (errorBuffer != 0) {
                        cout << "Connect REFUSED with code: " + handleError(errorBuffer) << endl;
                    }
                    else {
                        cout << "Connect SUCCESSFUL" << endl;
                        network.connections.push_back(make_pair(attacker.ID, attacker.password));
                        iotDevices[0]->disconnect(attacker.ID, network.password);
                    }
                }
                else {
                    cout << "Sorry, no other '" + input1 + "' device exists..." << endl;
                }

            }

            else if (input1 == "5") {   // disconnect from device/network
                cout << "What would you like to disconnect from" << endl;
                printSelectOp(input1);

                if (input1 == iotDevices[0]->getID()) { // disconnect iotDevice
                    cout << "Attempting disconnect from " + input1 + " using the stored ID & network pass..." << endl;
                    if (attacker.ID == network.ID)
                        errorBuffer = 7;
                    else
                        errorBuffer = iotDevices[0]->disconnect(attacker.ID, attacker.networkPass);
                    if (errorBuffer != 0) {
                        cout << "Disconnect REFUSED with code: " + handleError(errorBuffer) << endl;
                    }
                    else {
                        cout << "Disconnect SUCCESSFUL" << endl;
                    }
                }
                else if (input1 == network.ID) {    // disconnect from net
                    cout << "Attempting disconnect from: " + input1 + " ..." << endl;
                    for (int i = 0; i < static_cast<int>(network.connections.size()); ++i) {
                        if (network.connections[i].first == attacker.ID) {
                            network.connections[i].first = "";
                            network.connections[i].second = "";
                        }
                    }
                    cout << "Done." << endl;

                }
                else {
                    cout << "Sorry, no other '" + input1 + "' device exists..." << endl;
                }
            }

            else if (input1 == "6") {   // send data to device
            
                cout << "What device would you like to send data to?" << endl;
                printSelectOp(input1);

                if (input1 == iotDevices[0]->getID()) {
                    cout << "What data would you like to send?" << endl;
                    printSelectOp(input2);

                    cout << "Attempting to send '" + input2 + "' to: " + input1 << endl;
                    cout << "Using the stored ID and network pass..." << endl;
                    if (attacker.ID == network.ID)
                        errorBuffer = 8;
                    else
                        errorBuffer = iotDevices[0]->send(attacker.ID, attacker.networkPass, input2);

                    if (errorBuffer != 0) {
                        cout << "Send REFUSED with code: " + handleError(errorBuffer) << endl;
                    }
                    else {
                        cout << "Send SUCCESSFUL" << endl;
                    }
                }
                else {
                    cout << "Sorry, no other '" + input1 + "' device exists..." << endl;
                }

            }

            else if (input1 == "7") {   // retrieve data from device
            
                cout << "What device would you like to retrieve data from?" << endl;
                printSelectOp(input1);

                if (input1 == iotDevices[0]->getID()) {

                    cout << "Attempting to retrieve data from: " + input1 << endl;
                    cout << "Using the stored ID and network pass..." << endl;
                    if (attacker.ID == network.ID)
                        errorBuffer = 8;
                    else {
                        input2 = iotDevices[0]->retrieve(attacker.ID, attacker.networkPass);
                        if (input2 == "e3") errorBuffer = 3;
                        if (input2 == "e6") errorBuffer = 6;
                    }

                    if (errorBuffer != 0) {
                        cout << "Retrieve REFUSED with code: " + handleError(errorBuffer) << endl;
                    }
                    else {
                        cout << "Retrieve SUCCESSFUL" << endl;
                        cout << "Data Retrieved: " + input2 << endl;
                    }
                }
                else {
                    cout << "Sorry, no other '" + input1 + "' device exists..." << endl;
                }

            }

            else if (input1 == "0") {   // exit
                printExit();
            }

            else {  // 8 = return to main ops
                if (input1 != "8") printInvalidOps(input1);
            }

        }

        // debug print
        else if (input1 == "4") {
            cout << endl << "NETWORK ID: " + network.ID + " | PASS: " + network.password << endl;
            cout << "IOT DEVICE ID: " + iotDevices[0]->getID() + " | PASSWORD: " + iotDevices[0]->getPass() << endl;
            cout << "ATTACKER DEVICE:" << endl;
            cout << "STORED ID: " + attacker.ID << endl;
            cout << "STORED PASSWORD: " + attacker.password << endl;
            cout << "STORED NETWORK PASS: " + attacker.networkPass << endl << endl;
        }

        // quit simulation
        else if (input1 == "0") {
            printExit();
        }


        // incorrect operation
        else {
            printInvalidOps(input1);
        }
    
    }
    
}



void standardSetup(Network& network, vector<Device*>& iotDevices, Attacker& attacker) {

    cout << "Standard Setup: Network + IoT Device + Malicious Device/Attacker\n" << endl;

    // buffers for handling inputs and error throws
    string input1;
    string input2;
    int errorBuffer;

    // Initial the network controller
    cout << "(Identifiers can be IPs or just names for devices, but they should be unique within the simulation)" << endl;
    cout << "Your network identifier:"; cin >> input1;
    network.ID = input1;
    cout << "Your network password (10 digit alpha-numeric highly suggested):"; cin >> input1;
    network.password = input1;
    cout << "Network: " + network.ID + " | Password: " + network.password << endl << endl;


    // Setup the initial iot device, more can be setup later
    iotDevices.push_back(new Device());
    cout << "Your IoT device identifier:"; cin >> input1;
    cout << "Performing initial setup of your IoT device using your network password as the network key..." << endl;
    input2 = iotDevices[0]->initialSetup(input1, network.password);
    cout << "\nID: " + iotDevices[0]->getID() + " | Password: " + input2 << endl << endl;
    cout << "Your IoT device is initialized to connect only with devices on your network, per your network password.\n";
    cout << "However, it is not yet connected, would you like to do so now? (The device's password is not stored, so";
    cout << " if you plan on connecting the device later, you need to have the password memorized.)" << endl;
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
    cout << endl << "Setting up malicious device..." << endl;
    cout << "The malicious device will be completely customizable so that you can test the limits of this IoT security.";
    cout << endl << "For now, we'll just give it an identifier: "; cin >> input1;
    attacker.ID = input1;

}



// print operatoration selection
void printSelectOp(string &input) {
    cout << "Select: ";
    cin >> input;
}

// print main options
void printMainOps() {

    cout << endl << endl << "MAIN OPERATIONS:" << endl;
    cout << "0: Exit" << endl;
    cout << "1: Perform operations as the network" << endl;
    cout << "2: Perform operations as the IoT device" << endl;
    cout << "3: Perform operations as the attacker" << endl;
    cout << "4: DEBUG: Print devices and passwords" << endl << endl;

}

// print network operations
void printNetworkOps() {
    cout << endl << endl << "NETWORK OPERATIONS:" << endl;
    cout << "0: Exit" << endl;
    cout << "1: Connect to a device" << endl;
    cout << "2: Disconnect from a device" << endl;
    cout << "3: Send data to a device" << endl;
    cout << "4: Retrieve data from a device" << endl;
    cout << "5: Return to MAIN OPERATIONS" << endl << endl;
}

// print iot device operations
void printDeviceOps() {
    cout << endl << endl << "DEVICE OPERATIONS:" << endl;
    cout << "0: Exit" << endl;
    cout << "1: Connect to a device/network" << endl;
    cout << "2: Disconnect from a device/network" << endl;
    cout << "3: Send data to a device/network" << endl;
    cout << "4: Return to MAIN OPERATIONS" << endl << endl;
}

// print attacker/malicious device operations
void printAttackOps() {
    cout << endl << endl << "ATTACKER OPERATIONS:" << endl;
    cout << "0: Exit" << endl;
    cout << "1: Change attacker ID" << endl;
    cout << "2: Change stored network pass" << endl;
    cout << "3: Change stored password" << endl;
    cout << "4: Connect to a device/network" << endl;
    cout << "5: Disconnect from a device/network" << endl;
    cout << "6: Send data to a device" << endl;
    cout << "7: Retrieve data from a device" << endl;
    cout << "8: Return to MAIN OPERATIONS" << endl << endl;
}

// print incorrect operations
void printInvalidOps(string op) {

    cout << endl << endl << "INCORRECT OPERATION: '" + op + "'";
    cout << endl << "Refer to the list of operations and use the corresponding number to select an operation.";
    cout << endl << endl;

}

// print exit text
void printExit() {
    cout << endl << endl << "Exiting simulation..." << endl << endl;
}



// function for handling errors
string handleError(int code) {

    if (code == 0)
        return "0:OPERATION SUCCESSFUL";
    else if (code == 1)
        return "1:DEVICE HAS ALREADY BEEN SETUP";
    else if (code == 2)
        return "2:INCORRECT DEVICE PASSWORD";
    else if (code == 3)
        return "3:INCORRECT NETWORK PASS";
    else if (code == 4)
        return "4:NO MORE AVAILABLE CONNECTIONS";
    else if (code == 5)
        return "5:SPECIFIED CONNECTION HAS ALREADY BEEN MADE";
    else if (code == 6)
        return "6:SPECIFIED CONNECTION DOES NOT EXIST";
    else if (code == 7)
        return "7:DISCONNECT CALL MUST COME FROM CONNECTION ORIGIN";
    else if (code == 8)
        return "7:CONFLICTING CONNECTION IDS";
    else
        return "x:AN UNKNOWN ERROR HAS OCCURRED";

}
