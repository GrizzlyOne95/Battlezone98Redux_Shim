/*
 * Entry: 0049f8fe
 * Name: HowitzerClass::HowitzerClass
 * Namespace: HowitzerClass
 * Signature: HowitzerClass * HowitzerClass(HowitzerClass * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

HowitzerClass * __thiscall HowitzerClass::HowitzerClass(HowitzerClass *this)

{
  TurretTankClass::TurretTankClass((TurretTankClass *)this);
  *(undefined ***)this = &_vftable_;
  *(undefined4 *)&this->field_0x20 = 0x4857545a;
  *(char **)&this->field_0x24 = "howitzer";
  *(undefined4 *)&this->field_0x144 = 0xf;
  *(undefined4 *)&this->field_0x148 = 0x18;
  return this;
}
