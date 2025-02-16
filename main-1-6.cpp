#include <iostream>
#include "User.h"
#include "Seed.h"
#include "Crop.h"
#include "GardenBed.h"
#include"Item.h"
#include"Shovel.h"
#include"Store.h"
using namespace std;
int main (){
User* User1 = new User();
User1->SetMoney(100);
User1->SetWaterStorage(100);

GardenBed* Garden1 = new GardenBed(5); 
Store store(5);
Shovel* Shovel1 = new Shovel(User1,Garden1); 
store.AddItemToStore(Shovel1);
store.GetListOfItemsInStore();
Shovel1->BuyThisItem();
Shovel1->ShovelTheGround();


Seed* GenericSeed = new Seed(User1, "GenericSeed",100,20,10);
Crop* GenericCrop = new Crop(User1, GenericSeed->GetNameOfItem(),GenericSeed->GetRewardForHarvesting(), GenericSeed->GetCostOfItem(),10,GenericSeed->GetTImeForHarvesting());

Garden1->AddCropToGardenBed(GenericCrop);

Seed* GenericSeed2 = new Seed(User1, "GenericSeed2", 100, 20, 10);
Crop* GenericCrop2 = new Crop(User1, GenericSeed2->GetNameOfItem(), GenericSeed2->GetRewardForHarvesting(),  GenericSeed2->GetCostOfItem(), 10, GenericSeed2->GetTImeForHarvesting());
Garden1->AddCropToGardenBed(GenericCrop2);


Garden1->GetListOfCrops();
Garden1->RemoveCropFromGardenBed(0); 
Garden1->GetListOfCrops();

return 0;
}