#ifndef SEED_H
#define SEED_H
#include "Store.h"
#include "User.h"
#include"Item.h"
#include<iostream>
#include <thread>
#include <string>

class Seed : public Item {
protected: 
    int RewardForHarvesting; //variable to hold the reward given to the user for harvesting the seed 
    int TimeRequiredToHarvesting; //variable for time required to harvest the seed 
    User* User1;   // pointer to the user 
    bool StopThread; // bool about status of the thread 
    std::chrono::system_clock::time_point startTime; //variable called starttime which when intialsed holds the current time 
public:
    Seed(User* User1, string NameOfItem, int RewardForHarvesting, int CostOfItem, int TimeRequiredtoHarvesting);  //constructor 
    ~Seed(); //destructor 
    void HowManyDayTillHarvest();
    void StartPlantingTimer();
    void CropFinishedGrowing();
    void BuyThisItem() override;
    int GetRewardForHarvesting();
    int GetTImeForHarvesting();
};

#endif