/*
 * Entry: 004674eb
 * Name: TurretTankFriend::~TurretTankFriend
 * Namespace: TurretTankFriend
 * Signature: void ~TurretTankFriend(TurretTankFriend * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall TurretTankFriend::~TurretTankFriend(TurretTankFriend *this)

{
  *(undefined ***)this = &TurretTankProcess::_vftable_;
  UnitProcess::CleanState((UnitProcess *)this);
  *(undefined4 *)&this->field_0x18 = 0;
  UnitProcess::~UnitProcess((UnitProcess *)this);
  return;
}
