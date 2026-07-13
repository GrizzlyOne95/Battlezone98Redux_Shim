/*
 * Entry: 00470814
 * Name: BomberFriend::~BomberFriend
 * Namespace: BomberFriend
 * Signature: void ~BomberFriend(BomberFriend * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall BomberFriend::~BomberFriend(BomberFriend *this)

{
  *(undefined ***)this = &WingmanProcess::_vftable_;
  UnitProcess::CleanState((UnitProcess *)this);
  *(undefined4 *)&this->field_0x18 = 0;
  OffensiveProcess::~OffensiveProcess((OffensiveProcess *)this);
  return;
}
