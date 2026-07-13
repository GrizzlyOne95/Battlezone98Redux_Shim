/*
 * Entry: 00539a4d
 * Name: SniperGunClass::SniperGunClass
 * Namespace: SniperGunClass
 * Signature: SniperGunClass * SniperGunClass(SniperGunClass * this, SniperGunClass * param_1, long64 param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

SniperGunClass * __thiscall
SniperGunClass::SniperGunClass(SniperGunClass *this,SniperGunClass *param_1,long64 param_2)

{
  undefined4 unaff_ESI;
  
  CannonClass::CannonClass
            ((CannonClass *)this,(CannonClass *)param_1,CONCAT44(unaff_ESI,(undefined4)param_2));
  *(undefined ***)this = &_vftable_;
  return this;
}
