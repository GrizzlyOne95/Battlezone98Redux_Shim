/*
 * Entry: 0047bf3a
 * Name: AnimBuildingClass::AnimBuildingClass
 * Namespace: AnimBuildingClass
 * Signature: AnimBuildingClass * AnimBuildingClass(AnimBuildingClass * this, AnimBuildingClass * param_1, long64 param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

AnimBuildingClass * __thiscall
AnimBuildingClass::AnimBuildingClass
          (AnimBuildingClass *this,AnimBuildingClass *param_1,long64 param_2)

{
  undefined4 unaff_ESI;
  
  BuildingClass::BuildingClass
            ((BuildingClass *)this,(BuildingClass *)param_1,CONCAT44(unaff_ESI,(undefined4)param_2))
  ;
  *(undefined ***)this = &_vftable_;
  return this;
}
