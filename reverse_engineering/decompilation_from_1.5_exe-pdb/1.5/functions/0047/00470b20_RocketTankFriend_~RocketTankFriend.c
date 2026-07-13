/*
 * Entry: 00470b20
 * Name: RocketTankFriend::~RocketTankFriend
 * Namespace: RocketTankFriend
 * Signature: void ~RocketTankFriend(RocketTankFriend * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall RocketTankFriend::~RocketTankFriend(RocketTankFriend *this)

{
  *(undefined ***)this = &WingmanProcess::_vftable_;
  UnitProcess::CleanState((UnitProcess *)this);
  *(undefined4 *)&this->field_0x18 = 0;
  OffensiveProcess::~OffensiveProcess((OffensiveProcess *)this);
  return;
}
