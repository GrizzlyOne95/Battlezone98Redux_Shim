/*
 * Entry: 0052ff90
 * Name: GrenadeClass::GrenadeClass
 * Namespace: GrenadeClass
 * Signature: GrenadeClass * GrenadeClass(GrenadeClass * this, GrenadeClass * param_1, long64 param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GrenadeClass * __thiscall
GrenadeClass::GrenadeClass(GrenadeClass *this,GrenadeClass *param_1,long64 param_2)

{
  undefined4 unaff_ESI;
  
  RocketClass::RocketClass
            ((RocketClass *)this,(RocketClass *)param_1,CONCAT44(unaff_ESI,(undefined4)param_2));
  *(undefined ***)this = &_vftable_;
  return this;
}
