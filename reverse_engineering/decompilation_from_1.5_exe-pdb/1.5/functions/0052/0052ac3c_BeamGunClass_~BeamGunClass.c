/*
 * Entry: 0052ac3c
 * Name: BeamGunClass::~BeamGunClass
 * Namespace: BeamGunClass
 * Signature: void ~BeamGunClass(BeamGunClass * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall BeamGunClass::~BeamGunClass(BeamGunClass *this)

{
  *(undefined ***)this = &_vftable_;
  CannonClass::~CannonClass((CannonClass *)this);
  return;
}
