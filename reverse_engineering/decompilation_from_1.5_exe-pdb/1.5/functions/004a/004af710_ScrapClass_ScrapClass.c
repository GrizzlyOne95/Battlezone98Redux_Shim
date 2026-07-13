/*
 * Entry: 004af710
 * Name: ScrapClass::ScrapClass
 * Namespace: ScrapClass
 * Signature: ScrapClass * ScrapClass(ScrapClass * this, ScrapClass * param_1, long64 param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

ScrapClass * __thiscall ScrapClass::ScrapClass(ScrapClass *this,ScrapClass *param_1,long64 param_2)

{
  undefined4 unaff_ESI;
  
  BuildingClass::BuildingClass
            ((BuildingClass *)this,(BuildingClass *)param_1,CONCAT44(unaff_ESI,(undefined4)param_2))
  ;
  *(undefined ***)this = &_vftable_;
  return this;
}
