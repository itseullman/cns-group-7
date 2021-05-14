# cns-group-7
- Ahmed Alsaleh, Congwu Li, Chai-Rex Lin & Elliott Ullman
- Final Project for Spring 2021 Computer Network Security
- Professor Maha Allouzi
# IoT Security Simulator
**Version 1.0.0**

This program meant to demonstrate a simple security implementation that can be applied to most IoT devices and their network. The program provides an interface for manipulating a network, a connected IoT device, and an attacker/malicious device which the simulation user can utilize to test the overall security of the system.
This is a command line simulation and requires a C++ compiler to build and run.

---

## Setup

To get a local repo of the project, run:
* `git clone https://github.com/itseullman/cns-group-7.git`

To build the simulation, compile the following files with a C++ compiler:
* `g++ simulation.cpp device.cpp`

Or:
* `clang++ simulation.cpp device.cpp`

Finally, to start running the simulation, simply run the resulting executable, ie:
* `./a.out`

---

## Usage
> This IoT security simulator is built on the premise that all devices in a network have both a randomly generated 10-digit alpha-numeric password and a network key. The password is meant to restrict access to the device to only those who know that device’s password. In addition to this, the network is meant to prevent any unwanted communication and access to the device by rejecting any communications that come from another source that does not also hold the same network key, working on the idea that any device with the network key is a trusted part of the network.
> 
> Each device will also have an ID, which it will use to recognise other devices and connections.

* The program starts off with walking you through the standard setup, which includes a network, one IoT device which is configured to connect to and trust devices on that network, and an attacker device. There are no other setup options currently implemented in this build.
* The simulator will note that device IDs should be unique, as they will be used as device and connection identifiers. Later, however, you will be able to change the attacker device ID to whatever you wish, including copying the IDs of the other devices. The simulator should handle these situations regardless, and is meant to simulate ID/IP spoofing.
* Once configuring your network and IoT device, you will be asked if you want to connect your IoT device to your network now. If done immediately, the network will connect to the IoT device using its password that was just generated, and the network will remember this password incase it needs to connect again. However, if you choose not to connect at this point, you will need to remember the device's generated password so that it can make a connection later. Note that regardless of your choice, the device will always be configured with you network's key, and therefore will only connect to a device that also shares that key. This is meant to simulate the idea that an owner of an IoT device will have control over its initial setup, and will therefore be able to define the trustworthy network from the beginning.
* After this, you will be asked to give your malicious device an identifier. No other initial setup is needed for this device because all of its stored information can be altered during the simualtion.
* Now the simulation has begun!
* Following the prompts, you will see that you can perform operations as either the network, the IoT device, or the attacker. Each of which is described below:
### Network Operations
1. Connect to a device
   * > Attempt a connection to a device. The network stores a list of device IDs and associated passwords, so if it recognizes the device you are attempting to connect to, it will use its associated password. If the network does not recognize the device/connection, a device password will need to input manually. The network will always use its own network key when attempting to perform an operation
2. Disconnect from a device
   * > Attempt to disconnect from a device. The connection which you attempting to end needs to be specified.
3. Send data to a device
   * > Attempt to send some random data to a device. An existing connection to the device is needed, and you provide the data to be sent.
4. Retrieve data from a device
   * > Attempt to retrieve data from a device. An existing connection is needed, and expect the data to be essentially random. It can be nothing or could be something previously sent to the device.

### Device Operations
1. Connect to a device/network
   * > Attempt a connection to another device or the network. You will need to specify which device/network you wish to connect to, and the stored network pass on the device will be used. **Because you are acting as the root IoT device in this instance, the other device will not need to know this device's password. However, the other device/network will need to share the same network key as this device.**
2. Disconnect from a device/network
   * > Attempt to disconnect from another device or network. You will need to specify which device/network you wish to disconnect from, but no other information will be used besides the stored network pass.
3. Send data to a device/network
   * > Attempt to send data from this device to another device or even to the network. You are allowed to specify the data being sent, and an existing connection is needed.

### Attacker Operations
1. Change attacker ID
   * > Change the stored ID of this attacker device. This is the "**stored ID**"
2. Change stored network pass
   * > Change the network pass that the attacker will use in attempted operations. This is the "**stored net pass**"
3. Change stored password
   * > Change the password that the attacker will use in attempted operations that require the attacker to know the target device's password. **This password does not pertain to the attacker device itself**. This is the "**stored password**"
4. Connect to a device/network
   * > Attempt a connection using the stored ID, net pass and stored password if connecting to another device.
5. Disconnect from a device/network
   * > Attempt to disconnect from a device from a device or network using the stored ID and net pass. An existing connection is required. ID spoofing is checked against.
6. Send data to a device
   * > Attempt to send some data to a device using the stored ID, net pass, and some provided data. An existing connection is required. ID spoofing is checked against.
7. Retrieve data from a device
   * > Attempt to retrieve some data from a device's output buffer. Expect the data to be nothing, random, or based on previously sent data. The retrieval attempt will be made using the stored attacker ID and net pass. An existing connection is required. ID spoofing is checked against.
