

#ifndef WATERHOLE_H
#define WATERHOLE_H
#include <thread>
#include "User.h"

class User;

class WaterHole{
  private: 
    int WaterHoleStorage; //decleres the Water storage for the waterhole itself 
    User* User1; // a pointer to the user it self 
    std::thread WaterHoleThread; // a thread called waterholethread
    bool StopThread; // a boolean that either
  public:
    WaterHole(User* User1);  
    ~WaterHole();    
    void WaterHoleStorageDailyTimer(); 
    int GetWaterHoleStorage();
    void GiveUserWater();
};
#endif