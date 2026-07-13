/*
 * Entry: 004572b6
 * Name: PersonFriend::~PersonFriend
 * Namespace: PersonFriend
 * Signature: void ~PersonFriend(PersonFriend * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall PersonFriend::~PersonFriend(PersonFriend *this)

{
  *(undefined ***)this = &PersonProcess::_vftable_;
  UnitProcess::CleanState((UnitProcess *)this);
  *(undefined4 *)&this->field_0x18 = 0;
  OffensiveProcess::~OffensiveProcess((OffensiveProcess *)this);
  return;
}
