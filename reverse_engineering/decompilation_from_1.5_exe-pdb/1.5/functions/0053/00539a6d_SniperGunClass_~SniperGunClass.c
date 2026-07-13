/*
 * Entry: 00539a6d
 * Name: SniperGunClass::~SniperGunClass
 * Namespace: SniperGunClass
 * Signature: void ~SniperGunClass(SniperGunClass * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall SniperGunClass::~SniperGunClass(SniperGunClass *this)

{
  *(undefined ***)this = &_vftable_;
  CannonClass::~CannonClass((CannonClass *)this);
  return;
}
