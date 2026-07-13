/*
 * Entry: 00457161
 * Name: PersonGlide::~PersonGlide
 * Namespace: PersonGlide
 * Signature: void ~PersonGlide(PersonGlide * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall PersonGlide::~PersonGlide(PersonGlide *this)

{
  *(undefined ***)this = &_vftable_;
  *(undefined4 *)&this->field_0xc = 0xd;
  UnitTask::~UnitTask((UnitTask *)this);
  return;
}
