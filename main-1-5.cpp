#include "User.h"
#include "Seed.h"
#include "Crop.h"
#include"Store.h"
#include <thread>
#include <chrono>
using namespace std;
int main (){   
User* User1 = new User ();
User1->SetMoney(100);
User1->SetWaterStorage(100);
Seed* GenericSeed = new Seed(User1, "GenericSeed",100,20,10);
Crop * GenericCrop = new Crop(User1, GenericSeed->GetNameOfItem(),GenericSeed->GetRewardForHarvesting(), GenericSeed->GetCostOfItem(),10,GenericSeed->GetTImeForHarvesting());

GenericSeed->BuyThisItem();
std::cout<<"the required water for this crop is:" << GenericCrop->GetWaterRequired() << endl;
GenericCrop->Water();
GenericCrop->CropFinishedGrowing();
std::this_thread::sleep_for(std::chrono::seconds(5));
GenericCrop->CropFinishedGrowing();

return 0;
}