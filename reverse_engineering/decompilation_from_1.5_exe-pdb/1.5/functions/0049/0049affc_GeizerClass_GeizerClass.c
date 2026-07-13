/*
 * Entry: 0049affc
 * Name: GeizerClass::GeizerClass
 * Namespace: GeizerClass
 * Signature: GeizerClass * GeizerClass(GeizerClass * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GeizerClass * __thiscall GeizerClass::GeizerClass(GeizerClass *this)

{
  BuildingClass::BuildingClass((BuildingClass *)this);
  *(undefined ***)this = &_vftable_;
  *(undefined4 *)&this->field_0x20 = 0x4745495a;
  *(char **)&this->field_0x24 = "geyser";
  return this;
}
