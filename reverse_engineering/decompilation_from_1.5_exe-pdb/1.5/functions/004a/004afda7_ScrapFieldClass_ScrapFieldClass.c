/*
 * Entry: 004afda7
 * Name: ScrapFieldClass::ScrapFieldClass
 * Namespace: ScrapFieldClass
 * Signature: ScrapFieldClass * ScrapFieldClass(ScrapFieldClass * this, ScrapFieldClass * param_1, long64 param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

ScrapFieldClass * __thiscall
ScrapFieldClass::ScrapFieldClass(ScrapFieldClass *this,ScrapFieldClass *param_1,long64 param_2)

{
  undefined4 unaff_ESI;
  
  BuildingClass::BuildingClass
            ((BuildingClass *)this,(BuildingClass *)param_1,CONCAT44(unaff_ESI,(undefined4)param_2))
  ;
  *(undefined ***)this = &_vftable_;
  return this;
}
