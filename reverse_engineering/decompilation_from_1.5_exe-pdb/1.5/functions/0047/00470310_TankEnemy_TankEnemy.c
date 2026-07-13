/*
 * Entry: 00470310
 * Name: TankEnemy::TankEnemy
 * Namespace: TankEnemy
 * Signature: TankEnemy * TankEnemy(TankEnemy * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

TankEnemy * __thiscall TankEnemy::TankEnemy(TankEnemy *this)

{
  WingmanProcess::WingmanProcess((WingmanProcess *)this);
  *(undefined ***)this = &_vftable_;
  return this;
}
