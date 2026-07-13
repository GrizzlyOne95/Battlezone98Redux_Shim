/*
 * Entry: 004571b0
 * Name: PersonStraight::~PersonStraight
 * Namespace: PersonStraight
 * Signature: void ~PersonStraight(PersonStraight * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall PersonStraight::~PersonStraight(PersonStraight *this)

{
  *(undefined ***)this = &_vftable_;
  *(undefined4 *)&this->field_0xc = 0xd;
  UnitTask::~UnitTask((UnitTask *)this);
  return;
}
