/*
 * Entry: 00539a2d
 * Name: SniperGunClass::SniperGunClass
 * Namespace: SniperGunClass
 * Signature: SniperGunClass * SniperGunClass(SniperGunClass * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

SniperGunClass * __thiscall SniperGunClass::SniperGunClass(SniperGunClass *this)

{
  CannonClass::CannonClass((CannonClass *)this);
  *(undefined ***)this = &_vftable_;
  *(undefined4 *)&this->field_0xc = 0x534e4950;
  *(char **)&this->field_0x10 = "snipergun";
  return this;
}
