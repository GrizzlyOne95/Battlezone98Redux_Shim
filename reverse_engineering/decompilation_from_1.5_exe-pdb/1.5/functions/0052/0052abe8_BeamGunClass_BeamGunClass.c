/*
 * Entry: 0052abe8
 * Name: BeamGunClass::BeamGunClass
 * Namespace: BeamGunClass
 * Signature: BeamGunClass * BeamGunClass(BeamGunClass * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

BeamGunClass * __thiscall BeamGunClass::BeamGunClass(BeamGunClass *this)

{
  CannonClass::CannonClass((CannonClass *)this);
  *(undefined ***)this = &_vftable_;
  *(undefined4 *)&this->field_0xc = 0x4247554e;
  *(char **)&this->field_0x10 = "beamgun";
  strncpy(&this->field_0x58,"wlflame.wav",0x10);
  return this;
}
