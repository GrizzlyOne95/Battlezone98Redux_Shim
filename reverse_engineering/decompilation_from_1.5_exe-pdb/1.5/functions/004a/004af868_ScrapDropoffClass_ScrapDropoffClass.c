/*
 * Entry: 004af868
 * Name: ScrapDropoffClass::ScrapDropoffClass
 * Namespace: ScrapDropoffClass
 * Signature: ScrapDropoffClass * ScrapDropoffClass(ScrapDropoffClass * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

ScrapDropoffClass * __thiscall ScrapDropoffClass::ScrapDropoffClass(ScrapDropoffClass *this)

{
  PowerUpClass::PowerUpClass((PowerUpClass *)this);
  *(undefined ***)this = &_vftable_;
  *(undefined4 *)&this->field_0x20 = 0x53445250;
  *(char **)&this->field_0x24 = "dropoff";
  return this;
}
