/*
 * Entry: 0052ff43
 * Name: GrenadeClass::GrenadeClass
 * Namespace: GrenadeClass
 * Signature: GrenadeClass * GrenadeClass(GrenadeClass * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GrenadeClass * __thiscall GrenadeClass::GrenadeClass(GrenadeClass *this)

{
  RocketClass::RocketClass((RocketClass *)this);
  *(undefined4 *)&this->field_0x4c = 0x7149f2ca;
  *(undefined4 *)&this->field_0x54 = 0x43fa0000;
  *(undefined2 *)&this->field_0x58 = 2;
  *(undefined ***)this = &_vftable_;
  *(undefined4 *)&this->field_0x50 = 0x42480000;
  *(undefined4 *)&this->field_0xc = 0x4752454e;
  *(char **)&this->field_0x10 = "grenade";
  this->field_0x5a = 1;
  *(undefined4 *)&this->field_0x48 = 10;
  return this;
}
