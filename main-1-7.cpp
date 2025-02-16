#include"Store.h"
#include"Seed.h"
#include"Crop.h"
#include"User.h"
#include"Item.h"
#include"Shovel.h"
int main (){
 User* User1 = new User();
 GardenBed* garden = new GardenBed(5);
 Seed* BeetrootSeed = new Seed(User1, "Beetroot", 50, 5, 10);
    Crop* BeetrootCrop = new Crop(User1, BeetrootSeed->GetNameOfItem(), BeetrootSeed->GetRewardForHarvesting(),  BeetrootSeed->GetCostOfItem(), 10, BeetrootSeed->GetTImeForHarvesting());
    Seed* CarrotSeed = new Seed(User1, "Carrot", 70, 7, 15);
    Crop* CarrotCrop = new Crop(User1, CarrotSeed->GetNameOfItem(), CarrotSeed->GetRewardForHarvesting(),  CarrotSeed->GetCostOfItem(), 10, CarrotSeed->GetTImeForHarvesting());
    Seed* RadishSeed = new Seed(User1, "Radish", 90, 9, 20);
    Crop* RadishCrop = new Crop(User1, RadishSeed->GetNameOfItem(), RadishSeed->GetRewardForHarvesting(),  RadishSeed->GetCostOfItem(), 10, RadishSeed->GetTImeForHarvesting());
    Seed* RiceSeed = new Seed(User1, "Rice", 100, 10, 30);
    Crop* RiceCrop = new Crop(User1, RiceSeed->GetNameOfItem(), RiceSeed->GetRewardForHarvesting(),  RiceSeed->GetCostOfItem(), 10, RiceSeed->GetTImeForHarvesting());
Shovel* shovel = new Shovel(User1,garden); 

Store store(5);
store.AddItemToStore(BeetrootSeed);
store.AddItemToStore(CarrotSeed);
store.AddItemToStore(RadishSeed);
store.AddItemToStore(RiceSeed);
store.AddItemToStore(shovel);
store.GetListOfItemsInStore();
store.BuyThisItem(1);
store.BuyThisItem(5);
return 0;




}