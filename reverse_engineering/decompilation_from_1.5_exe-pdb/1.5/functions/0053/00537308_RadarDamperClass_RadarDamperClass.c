/*
 * Entry: 00537308
 * Name: RadarDamperClass::RadarDamperClass
 * Namespace: RadarDamperClass
 * Signature: RadarDamperClass * RadarDamperClass(RadarDamperClass * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

RadarDamperClass * __thiscall RadarDamperClass::RadarDamperClass(RadarDamperClass *this)

{
  SpecialItemClass::SpecialItemClass((SpecialItemClass *)this);
  *(undefined ***)this = &_vftable_;
  *(undefined4 *)&this->field_0xc = 0x52444d50;
  *(char **)&this->field_0x10 = "radardamper";
  return this;
}
