/*
 * Entry: 00532564
 * Name: MortarClass::MortarClass
 * Namespace: MortarClass
 * Signature: MortarClass * MortarClass(MortarClass * this, MortarClass * param_1, long64 param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

MortarClass * __thiscall
MortarClass::MortarClass(MortarClass *this,MortarClass *param_1,long64 param_2)

{
  undefined4 unaff_ESI;
  
  CannonClass::CannonClass
            ((CannonClass *)this,(CannonClass *)param_1,CONCAT44(unaff_ESI,(undefined4)param_2));
  *(undefined ***)this = &_vftable_;
  return this;
}
