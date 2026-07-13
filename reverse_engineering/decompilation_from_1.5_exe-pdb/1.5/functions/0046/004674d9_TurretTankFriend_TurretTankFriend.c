/*
 * Entry: 004674d9
 * Name: TurretTankFriend::TurretTankFriend
 * Namespace: TurretTankFriend
 * Signature: TurretTankFriend * TurretTankFriend(TurretTankFriend * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

TurretTankFriend * __thiscall TurretTankFriend::TurretTankFriend(TurretTankFriend *this)

{
  TurretTankProcess::TurretTankProcess((TurretTankProcess *)this);
  *(undefined ***)this = &_vftable_;
  return this;
}
