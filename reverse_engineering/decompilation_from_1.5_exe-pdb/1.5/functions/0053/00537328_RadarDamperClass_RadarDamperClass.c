/*
 * Entry: 00537328
 * Name: RadarDamperClass::RadarDamperClass
 * Namespace: RadarDamperClass
 * Signature: RadarDamperClass * RadarDamperClass(RadarDamperClass * this, RadarDamperClass * param_1, long64 param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

RadarDamperClass * __thiscall
RadarDamperClass::RadarDamperClass(RadarDamperClass *this,RadarDamperClass *param_1,long64 param_2)

{
  undefined4 unaff_ESI;
  
  SpecialItemClass::SpecialItemClass
            ((SpecialItemClass *)this,(SpecialItemClass *)param_1,
             CONCAT44(unaff_ESI,(undefined4)param_2));
  *(undefined ***)this = &_vftable_;
  return this;
}
