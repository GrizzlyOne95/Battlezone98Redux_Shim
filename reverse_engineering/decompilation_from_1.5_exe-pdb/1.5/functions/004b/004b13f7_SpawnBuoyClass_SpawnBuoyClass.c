/*
 * Entry: 004b13f7
 * Name: SpawnBuoyClass::SpawnBuoyClass
 * Namespace: SpawnBuoyClass
 * Signature: SpawnBuoyClass * SpawnBuoyClass(SpawnBuoyClass * this, SpawnBuoyClass * param_1, long64 param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

SpawnBuoyClass * __thiscall
SpawnBuoyClass::SpawnBuoyClass(SpawnBuoyClass *this,SpawnBuoyClass *param_1,long64 param_2)

{
  undefined4 unaff_ESI;
  
  BuildingClass::BuildingClass
            ((BuildingClass *)this,(BuildingClass *)param_1,CONCAT44(unaff_ESI,(undefined4)param_2))
  ;
  *(undefined ***)this = &_vftable_;
  return this;
}
