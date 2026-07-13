/*
 * Entry: 0052ac1c
 * Name: BeamGunClass::BeamGunClass
 * Namespace: BeamGunClass
 * Signature: BeamGunClass * BeamGunClass(BeamGunClass * this, BeamGunClass * param_1, long64 param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

BeamGunClass * __thiscall
BeamGunClass::BeamGunClass(BeamGunClass *this,BeamGunClass *param_1,long64 param_2)

{
  undefined4 unaff_ESI;
  
  CannonClass::CannonClass
            ((CannonClass *)this,(CannonClass *)param_1,CONCAT44(unaff_ESI,(undefined4)param_2));
  *(undefined ***)this = &_vftable_;
  return this;
}
