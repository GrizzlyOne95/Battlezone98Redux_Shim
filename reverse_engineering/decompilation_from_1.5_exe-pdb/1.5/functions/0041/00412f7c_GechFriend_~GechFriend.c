/*
 * Entry: 00412f7c
 * Name: GechFriend::~GechFriend
 * Namespace: GechFriend
 * Signature: void ~GechFriend(GechFriend * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall GechFriend::~GechFriend(GechFriend *this)

{
  *(undefined ***)this = &GechProcess::_vftable_;
  UnitProcess::CleanState((UnitProcess *)this);
  *(undefined4 *)&this->field_0x18 = 0;
  OffensiveProcess::~OffensiveProcess((OffensiveProcess *)this);
  return;
}
