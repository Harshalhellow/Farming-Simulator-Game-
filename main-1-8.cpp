#include <iostream>
#include "GardenBed.h"
#include "Shovel.h"
#include"Store.h"

int main() {
    User* User1 = new User();
User1->SetMoney(100);
User1->SetWaterStorage(100);
Seed* GenericSeed = new Seed(User1, "GenericSeed", 100, 20, 10);
Crop* GenericCrop = new Crop(User1, GenericSeed->GetNameOfItem(), GenericSeed->GetRewardForHarvesting(),  GenericSeed->GetCostOfItem(), 10, GenericSeed->GetTImeForHarvesting());
Seed* GenericSeed2 = new Seed(User1, "GenericSeed2", 100, 20, 10);
Crop* GenericCrop2 = new Crop(User1, GenericSeed2->GetNameOfItem(), GenericSeed2->GetRewardForHarvesting(),  GenericSeed2->GetCostOfItem(), 10, GenericSeed2->GetTImeForHarvesting());

 // Create a garden bed with a maximum capacity of 5 crops
    GardenBed* garden = new GardenBed(5);
    
garden->AddCropToGardenBed(GenericCrop);
garden->AddCropToGardenBed(GenericCrop2);
garden->GetListOfCrops();
Store store(5);


 Shovel* shovel = new Shovel(User1,garden); // Create a shovel

 store.AddItemToStore(shovel);
  store.GetListOfItemsInStore();
 shovel->ShovelTheGround();
 shovel->BuyThisItem();

    // Shovel the ground
shovel->ShovelTheGround();
garden->AddCropToGardenBed(GenericCrop);
garden->AddCropToGardenBed(GenericCrop2);
 

    // Get the list of crops in the garden bed
    garden->GetListOfCrops();

    // Remove a crop from the garden bed
    garden->RemoveCropFromGardenBed(1);

    // Get the updated list of crops in the garden bed
    garden->GetListOfCrops();



   
    return 0;
}
