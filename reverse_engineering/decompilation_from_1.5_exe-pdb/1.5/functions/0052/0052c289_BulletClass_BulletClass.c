/*
 * Entry: 0052c289
 * Name: BulletClass::BulletClass
 * Namespace: BulletClass
 * Signature: BulletClass * BulletClass(BulletClass * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

BulletClass * __thiscall BulletClass::BulletClass(BulletClass *this)

{
  OrdnanceClass::OrdnanceClass((OrdnanceClass *)this);
  *(undefined4 *)&this->field_0x4c = 0x40a00000;
  *(undefined4 *)&this->field_0x54 = 0x41200000;
  *(undefined4 *)&this->field_0x48 = 1;
  *(undefined2 *)&this->field_0x58 = 1;
  *(undefined4 *)&this->field_0x50 = 0x43480000;
  *(undefined ***)this = &_vftable_;
  *(undefined4 *)&this->field_0xc = 0x424c4c54;
  *(char **)&this->field_0x10 = "bullet";
  return this;
}
