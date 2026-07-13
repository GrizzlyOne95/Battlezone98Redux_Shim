/*
 * Entry: 0053002d
 * Name: GroundBlastClass::GroundBlastClass
 * Namespace: GroundBlastClass
 * Signature: GroundBlastClass * GroundBlastClass(GroundBlastClass * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GroundBlastClass * __thiscall GroundBlastClass::GroundBlastClass(GroundBlastClass *this)

{
  ExplosionClass::ExplosionClass((ExplosionClass *)this);
  *(undefined ***)this = &_vftable_;
  *(undefined4 *)&this->field_0x8 = 0x474e4442;
  *(char **)&this->field_0xc = "groundblast";
  return this;
}
