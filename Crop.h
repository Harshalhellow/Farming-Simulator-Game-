#ifndef CROPS_H
#define CROPS_H
#include"Store.h"
#include"Seed.h"
#include"Item.h"

//inherits from seed
class Crop: public Seed {
    private: 
        int WaterRequired; //holds the water required 
        bool watered = false;
        int plantedDay = -1;
    public:
        Crop(User* User1, std::string name, int RewardForHarvesting, int costofitem, int Wateramount, int TimeRequiredForHarvesting);  //constructors 
        int GetWaterRequired();
        void Water();
        ~Crop();//destructor 
        void SetPlantedDay(int dayNumber);
        void CropFinishedGrowing();
};

#endif