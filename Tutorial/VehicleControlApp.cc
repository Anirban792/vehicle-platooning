//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANT//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have rece//
// network description file for your Veins Application. Add parameters here
//
#include "VehicleControlApp.h"

#include "veins/modules/application/traci/MyVeinsApp.h"
using namespace veins;
Define_Module(veins::VehicleControlApp);


VehicleControlApp::VehicleControlApp() {
    // TODO Auto-generated constructor stub

}

VehicleControlApp::~VehicleControlApp() {
    // TODO Auto-generated destructor stub
}




void VehicleControlApp::initialize(int stage)
{
    DemoBaseApplLayer::initialize(stage);
    if (stage == 0) {
        // Initializing members and pointers of your application goes here
        EV << "Initializing " << par("appName").stringValue() << std::endl;
        mobility = TraCIMobilityAccess().get(getParentModule());
        //traci = mobility->getCommandInterface();
        traciVehicle = mobility->getVehicleCommandInterface();
        //findHost()->subscribe(mobilityStateChangedSignal, this);
        //subscribedServiceId = -1;
        currentOfferedServiceId = 7;
        wsaInterval = 5;
        beaconInterval = 0.1;
    }
    else if (stage == 1) {
        // Initializing members that require initialized other modules goes here
        int idDebug = getId();
        if (getId() == 13){
        // this is the head vehicle
        startService(Channel::sch2, currentOfferedServiceId, "Platoon Lead Vehicle Service");
        //scheduleAt()
        scheduleAt(computeAsynchronousSendingTime(beaconInterval, ChannelType::control),sendBeaconEvt);
        }
    }
}

void VehicleControlApp::finish()
{
    DemoBaseApplLayer::finish();
    // statistics recording goes here

}

void VehicleControlApp::onBSM(DemoSafetyMessage* bsm)
{
    // Your application has received a beacon message from another car or RSU
    // code for handling the message goes here
    Coord& leadVehicleSpeed = bsm->getSenderSpeed();
    traciVehicle->setSpeedMode(0x19);
    traciVehicle->setSpeed(leadVehicleSpeed.length());

    int senderId = bsm->getSenderAddress();
    bool fromPrecedingVehicle = false;
    switch (this->myId){
    case 13:
    break;
    case 19:
    if (senderId == 13 ) fromPrecedingVehicle = true;
    break;
    case 25:
    if (senderId == 19 ) fromPrecedingVehicle = true;
    break;
    case 31:
    if (senderId == 25 ) fromPrecedingVehicle = true;
    break;
    case 37:
    if (senderId == 31 ) fromPrecedingVehicle = true;
    break;
    default:
    ASSERT(0); // no other ids should exist in the simulation
    break;
    }
    double desiredDistance = 6.0;
    double coeff = 1;
    if (fromPrecedingVehicle)
    {
    double distance = (precedingVehiclePos- curPosition).length();
    double acc = coeff * (distance - desiredDistance);
    std::cout << "t" << simTime() << ": Distance [" << senderId << "]-[" << myId << "]: " << distance <<
    " acc: " << acc << "\n";
    if ( acc > 0){
    traciVehicle->setAccel(acc);
    traciVehicle->setSpeed(100);
    }
    else {
    traciVehicle->setDecel(-acc);
    traciVehicle->setSpeed(0);
    }
}

void VehicleControlApp::onWSM(BaseFrame1609_4* wsm)
{
    // Your application has received a data message from another car or RSU
    // code for handling the message goes here, see TraciDemo11p.cc for examples
}

void VehicleControlApp::onWSA(DemoServiceAdvertisment* wsa)
{
    // Your application has received a service advertisement from another car or RSU
    // code for handling the message goes here, see TraciDemo11p.cc for examples
}

void VehicleControlApp::handleSelfMsg(cMessage* msg)
{
    DemoBaseApplLayer::handleSelfMsg(msg);
    // this method is for self messages (mostly timers)
    // it is important to call the DemoBaseApplLayer function for BSM and WSM transmission
}

void VehicleControlApp::handlePositionUpdate(cObject* obj)
{
    DemoBaseApplLayer::handlePositionUpdate(obj);
 //   BaseWaveApplLayer::handlePositionUpdate(obj);
    if ( this->getId() == 14 ){
        const simtime_t t = simTime();
        if ( t == 10 ) {
            traciVehicle->setSpeedMode(0x19);
            traciVehicle->setSpeed(0);
        }
        else if ( t == 20 ) {
            traciVehicle->setSpeedMode(0x19);
            traciVehicle->setSpeed(20);
        }
    }
    // the vehicle has moved. Code that reacts to new positions goes here.
    // member variables such as currentPosition and currentSpeed are updated in the parent class
}

