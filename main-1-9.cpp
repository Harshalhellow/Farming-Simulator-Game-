#include <iostream>
#include "User.h"
#include"Day.h"
#include"Waterhole.h"
#include"Store.h"
#include "Seed.h"
#include "Crop.h"
#include "GardenBed.h"
#include"Item.h"

using namespace std;

int main() {
User* User1 = new User();
User1->SetMoney(100);
User1->SetWaterStorage(100);
Day Day1; 
WaterHole waterhole(User1);
GardenBed garden(100);
Store store(5);
Seed* BeetrootSeed = new Seed(User1, "Beetroot", 50, 5, 10);
Crop* BeetrootCrop = new Crop(User1, BeetrootSeed->GetNameOfItem(), BeetrootSeed->GetRewardForHarvesting(),  BeetrootSeed->GetCostOfItem(), 10, BeetrootSeed->GetTImeForHarvesting());
Seed* CarrotSeed = new Seed(User1, "Carrot", 70, 7, 15);
Crop* CarrotCrop = new Crop(User1, CarrotSeed->GetNameOfItem(), CarrotSeed->GetRewardForHarvesting(),  CarrotSeed->GetCostOfItem(), 10, CarrotSeed->GetTImeForHarvesting());
Seed* RadishSeed = new Seed(User1, "Radish", 90, 9, 20);
Crop* RadishCrop = new Crop(User1, RadishSeed->GetNameOfItem(), RadishSeed->GetRewardForHarvesting(),  RadishSeed->GetCostOfItem(), 10, RadishSeed->GetTImeForHarvesting());
Seed* RiceSeed = new Seed(User1, "Rice", 100, 10, 30);
Crop* RiceCrop = new Crop(User1, RiceSeed->GetNameOfItem(), RiceSeed->GetRewardForHarvesting(),  RiceSeed->GetCostOfItem(), 10, RiceSeed->GetTImeForHarvesting());
store.AddItemToStore(BeetrootSeed);
store.AddItemToStore(CarrotSeed);
store.AddItemToStore(RadishSeed);
store.AddItemToStore(RiceSeed);




delete User1;


}