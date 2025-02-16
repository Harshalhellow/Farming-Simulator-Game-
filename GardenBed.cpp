#include"GardenBed.h"
#include"Seed.h"
#include"Crop.h"

#include<iostream>
GardenBed::GardenBed(int MaxAmountOfCrop){
    Shoveled = false; 
     CurrentNumberOfCrops = 0; //sets the current number of crops to 0 
     MaxCrops = MaxAmountOfCrop; // sets the max crops to the paramater 
     Crops = new Crop*[MaxCrops]; //creates an array  of crop pointers for the garden bed and sets a pointer that points to first pointer in that array 

};

GardenBed::~GardenBed(){
      for (int i = 0; i < CurrentNumberOfCrops; ++i) {
        delete Crops[i];
    }
    delete[] Crops;
};
   //destructor for the garden bed and the pointers created in the constructors 



void GardenBed::AddCropToGardenBed(Crop* Crop_Add){
    if(!Shoveled){//if the ground has not been shoveled using the shoveling tooling then the User1 cant plant anything.
        std::cout << "The ground has not yet been shoveled" << std::endl; //displays this message if the ground is not shoveled
        return;
    }
     
    if(CurrentNumberOfCrops < MaxCrops) { //the User1 cant plant anything if there is no room
        Crops[CurrentNumberOfCrops] = Crop_Add;//takes the crop the User1 wants to plant and plants it in the garden bed by assigning the crop pointer in the paramater to the next free index in the arary found using pointer arthimtic by adding the current number to pointer 
        CurrentNumberOfCrops++; //increases the number of crops by 1 
            std::cout << "That seed has been added to the garden " << std::endl; //displays this message to say the seed has been added 
    }
    else {
        std::cout << "The Garden is full!" <<std::endl; //if there is no room then displaays this message 
    }//if the plant was not succesfull 

};




void GardenBed::RemoveCropFromGardenBed(int Index){ 
if(Index < 0 || Index >= CurrentNumberOfCrops){ // makes sure that the crop is actuallly in the garden bed
    std::cout << "That seed does not exit in the garden " << std::endl;  // if not then this message
    return;
}

delete Crops[Index]; //removes the crop from the list of array of pointers 

for(int i = Index; i<CurrentNumberOfCrops - 1; i++){ // moves every crop after that crop in the array  one position  to the left to fill the gap left
    Crops[i] = Crops[i+1];
}
CurrentNumberOfCrops--; //reduces the total number of crops by 1 in the garden
 std::cout << "That seed has been removed from   the garden " << std::endl; //displays this message to confirm 

};




void GardenBed::GetListOfCrops(){
    for(int i =0; i < CurrentNumberOfCrops; i++){//displays the list of crops in the garden bed and thier name 
        std::cout << "Seed " << 1+i << Crops[i]->GetNameOfItem() << std::endl; // displays their name and what postion they are in the garden bed 
    }
};

void GardenBed::SetShoveled(bool Shoveled){ //seter for the shoveld 
       this->Shoveled = Shoveled; 
};
bool GardenBed::GetShoveled(){
    return Shoveled; //getter for the shoveled these wont be used by garden bed but instead by the shovel
};


int GardenBed::GetCropCount()  { 
    return CurrentNumberOfCrops; };


Crop* GardenBed::GetCropAt(int index)  { 
    return Crops[index]; };