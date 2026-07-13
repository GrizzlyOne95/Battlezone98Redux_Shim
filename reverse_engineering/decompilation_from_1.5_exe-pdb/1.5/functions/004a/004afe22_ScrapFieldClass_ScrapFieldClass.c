/*
 * Entry: 004afe22
 * Name: ScrapFieldClass::ScrapFieldClass
 * Namespace: ScrapFieldClass
 * Signature: ScrapFieldClass * ScrapFieldClass(ScrapFieldClass * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

ScrapFieldClass * __thiscall ScrapFieldClass::ScrapFieldClass(ScrapFieldClass *this)

{
  BuildingClass::BuildingClass((BuildingClass *)this);
  *(undefined ***)this = &_vftable_;
  *(undefined4 *)&this->field_0x20 = 0x53464c44;
  *(char **)&this->field_0x24 = "scrapfield";
  return this;
}
