/*
 * Entry: 0040bf83
 * Name: APCFriend::~APCFriend
 * Namespace: APCFriend
 * Signature: void ~APCFriend(APCFriend * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall APCFriend::~APCFriend(APCFriend *this)

{
  *(undefined ***)this = &APCProcess::_vftable_;
  UnitProcess::CleanState((UnitProcess *)this);
  *(undefined4 *)&this->field_0x18 = 0;
  UnitProcess::~UnitProcess((UnitProcess *)this);
  return;
}
