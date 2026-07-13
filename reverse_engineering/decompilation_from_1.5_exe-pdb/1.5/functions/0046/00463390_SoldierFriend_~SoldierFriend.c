/*
 * Entry: 00463390
 * Name: SoldierFriend::~SoldierFriend
 * Namespace: SoldierFriend
 * Signature: void ~SoldierFriend(SoldierFriend * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall SoldierFriend::~SoldierFriend(SoldierFriend *this)

{
  *(undefined ***)this = &SoldierProcess::_vftable_;
  UnitProcess::CleanState((UnitProcess *)this);
  *(undefined4 *)&this->field_0x18 = 0;
  OffensiveProcess::~OffensiveProcess((OffensiveProcess *)this);
  return;
}
