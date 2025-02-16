#include "Seed.h"
#include"User.h"
#include"Store.h"
#include"Item.h"
#include <iostream>
//creates the seed consturctor

Seed::Seed(User* User1, string NameOfItem, int RewardForHarvesting, int CostOfItem, int TimeRequiredToHarvesting) : Item(NameOfItem,CostOfItem), User1(User1)  {
    SetNameOfItem(NameOfItem); //sets the name of the item to be what was given as the paramater 
    SetCostOfItem(CostOfItem);//sets the cost of the item to be what was given as the paraamter 
    this->RewardForHarvesting = RewardForHarvesting; //sets the reward for harvesting to be what was given as the paramater
    this->TimeRequiredToHarvesting = TimeRequiredToHarvesting;  //sets the time required for harvesting to be what was given as the paramater 
    SetIsBought(false);
    StopThread = false;  //sets the thread to true 
};
//seed destructor 
Seed::~Seed() {
     StopThread = true;
}

void Seed::HowManyDayTillHarvest() { //gives the user how long is required to harvest the seed once planted
    std::cout << "Time required for harvesting: " << TimeRequiredToHarvesting << " days" << std::endl;
}

void Seed::StartPlantingTimer() {
    if (!GetIsBought()) {//starts planting timer if onnly the seed is bought  
        std::cout << "You need to buy the seed first!" << std::endl; 
        return;
    }

    startTime = std::chrono::system_clock::now(); //starts a timer this variable hold the current time of when the  start timer funciton is called 
    StopThread = false; //sets teh stop thread to false 
}



void Seed::BuyThisItem()  {
    int Cost = GetCostOfItem();
    if (User1->GetMoney() >= Cost) {
        User1->SetMoney(User1->GetMoney() - Cost);
        User1->AddSeed(1);  // add one seed to inventory
        std::cout << "Seed bought successfully!" << std::endl;
        // You might or might not want to call SetIsBought(true) here.
    } else {
        std::cout << "Not enough money to buy this item." << std::endl;
    }
}

int Seed::GetRewardForHarvesting(){
    return RewardForHarvesting; //geter for reward for harvesting 
    } 

int Seed::GetTImeForHarvesting(){
    return TimeRequiredToHarvesting; //geter for the timer required for harvesting 
    }
