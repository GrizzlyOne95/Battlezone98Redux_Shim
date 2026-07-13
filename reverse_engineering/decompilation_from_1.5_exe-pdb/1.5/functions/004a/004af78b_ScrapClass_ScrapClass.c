/*
 * Entry: 004af78b
 * Name: ScrapClass::ScrapClass
 * Namespace: ScrapClass
 * Signature: ScrapClass * ScrapClass(ScrapClass * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

ScrapClass * __thiscall ScrapClass::ScrapClass(ScrapClass *this)

{
  BuildingClass::BuildingClass((BuildingClass *)this);
  *(undefined ***)this = &_vftable_;
  *(undefined4 *)&this->field_0x20 = 0x53435250;
  *(char **)&this->field_0x24 = "scrap";
  *(undefined4 *)&this->field_0x28 = 7;
  return this;
}
