#ifndef GARDENBED_H
#define GARDENBED_H
#include"Crop.h"
class GardenBed {
private:
Crop** Crops; //a pointer to an array of pointer that point to crops  
int CurrentNumberOfCrops; // holds the current number of crops in the garden 
int MaxCrops;  // holds hte max crops 
bool Shoveled; // is the garden shoveled or not 
public:
GardenBed(int MaxAmountOfCrops); //the garden bed constructor 
~GardenBed();//destructor 
void AddCropToGardenBed(Crop* Crop_Add); 
void RemoveCropFromGardenBed(int Index);
void GetListOfCrops();
void SetShoveled(bool Shoveled);
bool GetShoveled();
int GetCropCount();
Crop* GetCropAt(int index);
};
#endif