#include "WaterHole.h"
#include "User.h"
#include <iostream>
#include <thread>

WaterHole::~WaterHole() {
    StopThread = true; //sets the  stop thread to  true  when the destructor is called when the object is out of scope 
    if (WaterHoleThread.joinable()) { //makes the thread rejoin the main therad of the program hence stoppiing the timer
        WaterHoleThread.join();
    }
}

WaterHole::WaterHole(User* User1) :  WaterHoleStorage(10), User1(User1), StopThread(false){
    WaterHoleThread = std::thread(&WaterHole::WaterHoleStorageDailyTimer, this); //constuctor for the waterhole, sets the stopthread to false passes a user pointer(useful later) sets teh waterholestorage  starting value to 10 calls the waterholestorage timer. 
}

void WaterHole::WaterHoleStorageDailyTimer() {
    while (!StopThread) { // so while stop therad is off then thread will sleep for x peiod of time and then execute the following code. THis ususally makes the terminal unacccesable however since its a different thread code can exsecute in the background while this runs. 
        std::this_thread::sleep_for(std::chrono::seconds(1)); 
        WaterHoleStorage += 10;//so every second the waterholestorage increases by 10
    }
}

int WaterHole::GetWaterHoleStorage(){
    return WaterHoleStorage; //gets the waterholestorage 
};

void WaterHole::GiveUserWater(){
int Total_Water = WaterHoleStorage + User1->GetWaterStorage();  //sets the total water to the waterholestorage and the existing user waterstorage
    User1->SetWaterStorage(Total_Water);  //gives the waterholesotrage to the user 
    WaterHoleStorage = 0; //sets the wateholestorage to 0
    Total_Water = 0; //sets the total water to 0 
};
