/*
 * Entry: 005314c5
 * Name: MachineGunClass::MachineGunClass
 * Namespace: MachineGunClass
 * Signature: MachineGunClass * MachineGunClass(MachineGunClass * this, MachineGunClass * param_1, long64 param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

MachineGunClass * __thiscall
MachineGunClass::MachineGunClass(MachineGunClass *this,MachineGunClass *param_1,long64 param_2)

{
  undefined4 unaff_ESI;
  
  CannonClass::CannonClass
            ((CannonClass *)this,(CannonClass *)param_1,CONCAT44(unaff_ESI,(undefined4)param_2));
  *(undefined ***)this = &_vftable_;
  return this;
}
