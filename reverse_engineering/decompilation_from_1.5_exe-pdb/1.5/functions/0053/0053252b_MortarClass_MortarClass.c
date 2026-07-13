/*
 * Entry: 0053252b
 * Name: MortarClass::MortarClass
 * Namespace: MortarClass
 * Signature: MortarClass * MortarClass(MortarClass * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

MortarClass * __thiscall MortarClass::MortarClass(MortarClass *this)

{
  CannonClass::CannonClass((CannonClass *)this);
  *(undefined4 *)&this->field_0x78 = 0x3f800000;
  *(undefined ***)this = &_vftable_;
  *(undefined4 *)&this->field_0xc = 0x4d4f5254;
  *(char **)&this->field_0x10 = "mortar";
  strncpy(&this->field_0x58,"wcbl.wav",0x10);
  return this;
}
