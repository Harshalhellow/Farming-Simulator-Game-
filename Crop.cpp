#include"Crop.h"
#include"Day.h"
#include"Seed.h"
#include"User.h"
#include <iostream>

//creates the crop constructor
Crop::Crop(User* User1, std::string name, int RewardForHarvesting, int CostOfItem,int WaterRequired, int TimeRequiredForHarvesting) : Seed(User1, name,RewardForHarvesting, CostOfItem, TimeRequiredForHarvesting) {
    this->WaterRequired = WaterRequired;  //sets the water required to the given parameter 
};

void Crop::Water(){
    // Check that the user has at least the required water.
    if (User1->GetWaterStorage() >= WaterRequired) {
        User1->SetWaterStorage(User1->GetWaterStorage() - WaterRequired);
        watered = true;  // mark as watered
        this->StartPlantingTimer();
    } else {
        std::cout << "Not enough water, you need " << WaterRequired 
                  << " but you have " << User1->GetWaterStorage() << std::endl;
    }
}

int Crop::GetWaterRequired(){ //returns water required
    return WaterRequired;
};

void Crop::SetPlantedDay(int dayNumber) {
    plantedDay = dayNumber;
}

void Crop::CropFinishedGrowing() {
    if (!watered) {
        std::cout << "You must water the crop before it can grow." << std::endl;
        return;
    }
  
    extern Day* currentDayCounter;  
    int daysPassed = currentDayCounter->GetCurrentDay() - plantedDay;
    if (daysPassed < TimeRequiredToHarvesting) {
        std::cout << "The crop is not ready to harvest yet. You need to wait " 
                  << (TimeRequiredToHarvesting - daysPassed) << " more day(s)." << std::endl;
        return;
    } else {
        User1->SetMoney(User1->GetMoney() + RewardForHarvesting);
        std::cout << "The crop has been harvested!" << std::endl;
    }
}







//crop destructor     
Crop::~Crop(){};