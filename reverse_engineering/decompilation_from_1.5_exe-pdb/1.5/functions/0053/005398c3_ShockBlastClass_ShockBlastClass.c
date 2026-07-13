/*
 * Entry: 005398c3
 * Name: ShockBlastClass::ShockBlastClass
 * Namespace: ShockBlastClass
 * Signature: ShockBlastClass * ShockBlastClass(ShockBlastClass * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

ShockBlastClass * __thiscall ShockBlastClass::ShockBlastClass(ShockBlastClass *this)

{
  ExplosionClass::ExplosionClass((ExplosionClass *)this);
  *(undefined ***)this = &_vftable_;
  *(undefined4 *)&this->field_0x8 = 0x53484b42;
  *(char **)&this->field_0xc = "shockblast";
  return this;
}
