
#include<iostream>
#include<vector>
#include <ctime>
#include <map>

using namespace std;


enum VehicleType{
    Bike,
    HatchBack,
    Suv,
    Bus
};

class Ticket;

class Vehicle{
    public:

    static int nextID;

    int id;
    VehicleType type;
    string regNo,color;
    Ticket* ticket;

    Vehicle(string reg_no, VehicleType ty){
        id = nextID ++;
        regNo = reg_no;
        type = ty;
    }

    void addTicket(Ticket* t){
        ticket = t;
    }
};

class ParkingSlot{

    public:
    int id,floorNumber;
    VehicleType capacity;
    bool isVacant;
    int costPerMinute;
    
    static int nextID;

    ParkingSlot(VehicleType cap,int floorNum){
        id = nextID ++;
        costPerMinute = 10;
        capacity = cap;
        floorNumber = floorNum;
        isVacant = true;
    }

    void bookParkingSlot(){
        isVacant = false;
    }
    void releaseParkingSlot(){
        isVacant = true;
    }

    
};

class Ticket{

    public:

    int id;
    static int nextID;

    time_t beginTime, endTime;
    int entryGateID, exitGateID;
    Vehicle *vehicle;
    ParkingSlot *parkingSlot;
    bool isPaid;

    Ticket(){}

    Ticket(Vehicle *v, ParkingSlot *p){
        vehicle = v;
        parkingSlot = p;
        isPaid = false;
        time_t beginTime = time(nullptr);
    }
    
    void closeTicket(){
        endTime = time(nullptr);
    }

    int getTotalCost(){
        return (endTime - beginTime) * (parkingSlot->costPerMinute);
    }

    void updatePayment(int exitGateID){
        isPaid = true;
        exitGateID = exitGateID;
    }

};


class Entry{

    public:
    int id;
    static int nextID;

    Ticket* issueTicket(Vehicle *v, ParkingSlot *p){
        p->bookParkingSlot();
        Ticket *t = new Ticket(v, p);
        return t;
    }

};

class Exit{
    public :
    int id;
    static int nextID;

    Exit(){
        id = nextID ++;
    }

    void acceptPaymentAndCloseTicket(Ticket *t){
        t->closeTicket();
        int ticketPrice = t->getTotalCost();

        cout<<"processing payment of "<<ticketPrice<<"from vehicle = "<<t->vehicle->regNo<<"\n";
        
        t->updatePayment(this->id);
    }  

};

class DisplayBoard{

    public:
    int id;
    static int nextID;
    map<VehicleType, int> vacancies;

    DisplayBoard(){
        id = nextID++;
    }

    void printDetails(){

        cout<<"vacancies:\n ";
        for(pair<VehicleType,int> p : vacancies){
            cout<<p.first<<" "<<p.second<<"\n";
        }
        cout<<"\n";
    }
};

class ParkingFloor{
    
    public:
    int id,numSlots;
    static int nextID;
    DisplayBoard displayBoard;
    vector<ParkingSlot*> parkingSlots;

    ParkingFloor(int n){
        id = nextID++;
        displayBoard = DisplayBoard();
        numSlots = n;

        int small = n/3, medium = n/3, large = n/3;
        int extraLarge = n -(small + medium + large);

        initialiseSlotsFor(small,medium,large,extraLarge);

    }

    ParkingFloor(int n, int small,int medium, int large,int extraLarge){
        id = nextID++;
        displayBoard = DisplayBoard();
        initialiseSlotsFor(small,medium,large,extraLarge);
    }

    void initialiseSlotsFor(int small,int medium, int large, int extraLarge){
        displayBoard.vacancies[Bike] = small;
        displayBoard.vacancies[HatchBack] = medium;
        displayBoard.vacancies[Suv] = large;
        displayBoard.vacancies[Bus] = extraLarge;

        int idx = 0;
        for(int i =0;i<small;i++){
            parkingSlots.push_back(new ParkingSlot(Bike, this->id));
        }

        for(int i =0;i<medium;i++){
            parkingSlots.push_back(new ParkingSlot(HatchBack, this->id));
        }

        for(int i =0;i<large;i++){
            parkingSlots.push_back(new ParkingSlot(Suv, this->id));
        }

        for(int i =0;i<extraLarge;i++){
            parkingSlots.push_back(new ParkingSlot(Bus, this->id));
        }

    }   

    ParkingSlot* getAnEmptySlot(Vehicle *v){
            
            for(ParkingSlot *p : this->parkingSlots){

                if(p->capacity == v->type && p->isVacant){
                    return p;
                }
            }
            return nullptr;
    }

    void addNewParkingSlot( VehicleType capacity){
        parkingSlots.push_back(new ParkingSlot(capacity,this->id));
        displayBoard.vacancies[capacity]++;
    }

    void showFloorInfo(){
        displayBoard.printDetails();
    }

    ParkingSlot* getSlotByID(int targetSlotID){

            for(ParkingSlot *p : parkingSlots){
                if(p->id == targetSlotID){
                    return p;
                }
            }
        return nullptr;
    }

};

class ParkingLot{
    public:
    int id;
    static int nextID;

    string name, address;
    vector<ParkingFloor*> parkingFloors;

    DisplayBoard* globalBoard;

    vector<Entry*> entries;
    vector<Exit*> exits;

    ParkingLot(string name, string address){
        this->name = name;
        this->address = address;
    }

    void addEntry(){
        entries.push_back(new Entry());
    }

    void addExit(){
        exits.push_back(new Exit());
    }

    void addParkingFloor(int n){
        parkingFloors.push_back(new ParkingFloor(n));
    }

    void showParkingLotInfo(){
        globalBoard->printDetails();
    }

    Ticket* parkVehicle(int gateId,Vehicle *v){

        Entry *gate = nullptr;
        for(Entry *e : entries){
            if(e->id == gateId){
                gate = e;
            }
        }

        if(gate == nullptr){
            cout<<"gate with required id is not found"; return nullptr;
        }

        for(ParkingFloor *pf : parkingFloors){
            ParkingSlot *p = pf->getAnEmptySlot(v);
            if(p != nullptr){
                
                p->bookParkingSlot();
                Ticket *ticket = gate->issueTicket(v,p);
                return ticket;
            }
        }
        return nullptr;
    }

    void releaseVehicle(int gateId, Ticket *t){
        Exit *gate = nullptr;
        for(Exit *e : exits){
            if(e->id == gateId){
                gate = e;
            }
        }

        if(gate == nullptr){
            cout<<"gate with required id is not found"; return;
        }

        gate->acceptPaymentAndCloseTicket(t);
        cout<<"vehicle is released\n";
    }

    bool checkStatusOfSlot(int parkingLotID){
        
        for(ParkingFloor* pf : parkingFloors){
            
            ParkingSlot *p = pf->getSlotByID(parkingLotID);
            if(p != nullptr){
                return p->isVacant;
            }
        }
        return false;
    }

};


int Vehicle::nextID = 0;
int ParkingSlot::nextID = 0;
int Ticket::nextID = 0;
int Entry::nextID = 0;
int Exit::nextID = 0;
int DisplayBoard::nextID = 0;
int ParkingFloor::nextID = 0;
int ParkingLot::nextID = 0;


int main(){

    ParkingLot *parkingLot = new ParkingLot();

    return 0;
}