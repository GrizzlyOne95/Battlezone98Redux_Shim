/*
 * Entry: 0049af81
 * Name: GeizerClass::GeizerClass
 * Namespace: GeizerClass
 * Signature: GeizerClass * GeizerClass(GeizerClass * this, GeizerClass * param_1, long64 param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GeizerClass * __thiscall
GeizerClass::GeizerClass(GeizerClass *this,GeizerClass *param_1,long64 param_2)

{
  undefined4 unaff_ESI;
  
  BuildingClass::BuildingClass
            ((BuildingClass *)this,(BuildingClass *)param_1,CONCAT44(unaff_ESI,(undefined4)param_2))
  ;
  *(undefined ***)this = &_vftable_;
  return this;
}
