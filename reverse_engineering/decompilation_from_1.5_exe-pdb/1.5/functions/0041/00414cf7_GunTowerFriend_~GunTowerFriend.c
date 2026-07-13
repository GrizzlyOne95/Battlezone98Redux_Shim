/*
 * Entry: 00414cf7
 * Name: GunTowerFriend::~GunTowerFriend
 * Namespace: GunTowerFriend
 * Signature: void ~GunTowerFriend(GunTowerFriend * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall GunTowerFriend::~GunTowerFriend(GunTowerFriend *this)

{
  *(undefined ***)this = &GunTowerProcess::_vftable_;
  UnitProcess::CleanState((UnitProcess *)this);
  *(undefined4 *)&this->field_0x18 = 0;
  UnitProcess::~UnitProcess((UnitProcess *)this);
  return;
}
