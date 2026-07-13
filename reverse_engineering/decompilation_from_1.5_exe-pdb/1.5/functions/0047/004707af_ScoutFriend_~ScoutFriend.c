/*
 * Entry: 004707af
 * Name: ScoutFriend::~ScoutFriend
 * Namespace: ScoutFriend
 * Signature: void ~ScoutFriend(ScoutFriend * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall ScoutFriend::~ScoutFriend(ScoutFriend *this)

{
  *(undefined ***)this = &WingmanProcess::_vftable_;
  UnitProcess::CleanState((UnitProcess *)this);
  *(undefined4 *)&this->field_0x18 = 0;
  OffensiveProcess::~OffensiveProcess((OffensiveProcess *)this);
  return;
}
