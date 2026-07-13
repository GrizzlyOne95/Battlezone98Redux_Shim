/*
 * Entry: 0047072a
 * Name: TankFriend::TankFriend
 * Namespace: TankFriend
 * Signature: TankFriend * TankFriend(TankFriend * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

TankFriend * __thiscall TankFriend::TankFriend(TankFriend *this)

{
  WingmanProcess::WingmanProcess((WingmanProcess *)this);
  *(undefined ***)this = &_vftable_;
  return this;
}
