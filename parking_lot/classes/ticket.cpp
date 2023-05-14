
#include "parkingSlot.cpp"

class Vehicle;
class ParkingSlot;

class Ticket{

    int id;

    int beginTime, endTime, entryGateID, exitGateID;
    Vehicle *vehicle;
    ParkingSlot *parkingSlot;

    bool isPaid;

    int GetTotalCost(){
        (endTime - beginTime) * (parkingSlot->costPerMinute);
    }

};