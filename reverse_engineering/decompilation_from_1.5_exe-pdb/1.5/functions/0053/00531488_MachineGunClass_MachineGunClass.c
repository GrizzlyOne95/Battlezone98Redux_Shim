/*
 * Entry: 00531488
 * Name: MachineGunClass::MachineGunClass
 * Namespace: MachineGunClass
 * Signature: MachineGunClass * MachineGunClass(MachineGunClass * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

MachineGunClass * __thiscall MachineGunClass::MachineGunClass(MachineGunClass *this)

{
  CannonClass::CannonClass((CannonClass *)this);
  *(undefined4 *)&this->field_0x78 = 0x3e4ccccd;
  *(undefined ***)this = &_vftable_;
  *(undefined4 *)&this->field_0xc = 0x4d47554e;
  *(char **)&this->field_0x10 = "machinegun";
  strncpy(&this->field_0x58,"wlmgun.wav",0x10);
  return this;
}
