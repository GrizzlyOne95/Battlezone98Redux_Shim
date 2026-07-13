/*
 * Entry: 0040d3f6
 * Name: ArtilleryFriend::~ArtilleryFriend
 * Namespace: ArtilleryFriend
 * Signature: void ~ArtilleryFriend(ArtilleryFriend * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall ArtilleryFriend::~ArtilleryFriend(ArtilleryFriend *this)

{
  *(undefined ***)this = &OffensiveProcess::_vftable_;
  UnitProcess::CleanState((UnitProcess *)this);
  *(undefined4 *)&this->field_0x18 = 0;
  UnitProcess::~UnitProcess((UnitProcess *)this);
  return;
}
