#include "User.h"
#include "Seed.h"
#include <iostream>
#include <thread>

int main() {


    User User1;
    
    Seed Seed1(&User1,"Apple",100,10,10);

    
    std::cout <<"Did the intitalisation work should be apple 100 10 10 " << Seed1.GetCostOfItem() << Seed1.GetNameOfItem() <<"you are :" << Seed1.GetRewardForHarvesting() << "you are " << Seed1.GetTImeForHarvesting() << std::endl;
    std::cout << "User1's initial money: " << User1.GetMoney() << std::endl;
User1.SetMoney(100);
std::cout << "User1's initial money: " << User1.GetMoney() << std::endl;
    Seed1.BuyThisItem();
    std::cout << "User1's money after buying seed: " << User1.GetMoney() << std::endl;
    Seed1.StartPlantingTimer();
    std::this_thread::sleep_for(std::chrono::seconds(1)); 
    Seed1.CropFinishedGrowing();
    std::cout << "User1's money after premature harvest attempt: " << User1.GetMoney() << std::endl;    
    std::this_thread::sleep_for(std::chrono::seconds(11)); 
    Seed1.CropFinishedGrowing();
    std::cout << "User1's money after harvest: " << User1.GetMoney() << std::endl;

    return 0;
}