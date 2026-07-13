/*
 * Entry: 0047073c
 * Name: TankFriend::~TankFriend
 * Namespace: TankFriend
 * Signature: void ~TankFriend(TankFriend * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall TankFriend::~TankFriend(TankFriend *this)

{
  *(undefined ***)this = &WingmanProcess::_vftable_;
  UnitProcess::CleanState((UnitProcess *)this);
  *(undefined4 *)&this->field_0x18 = 0;
  OffensiveProcess::~OffensiveProcess((OffensiveProcess *)this);
  return;
}
