/*
 * Entry: 005314e5
 * Name: MachineGunClass::~MachineGunClass
 * Namespace: MachineGunClass
 * Signature: void ~MachineGunClass(MachineGunClass * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall MachineGunClass::~MachineGunClass(MachineGunClass *this)

{
  *(undefined ***)this = &_vftable_;
  CannonClass::~CannonClass((CannonClass *)this);
  return;
}
