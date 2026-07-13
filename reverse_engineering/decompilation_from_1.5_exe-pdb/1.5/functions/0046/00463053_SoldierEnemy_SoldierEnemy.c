/*
 * Entry: 00463053
 * Name: SoldierEnemy::SoldierEnemy
 * Namespace: SoldierEnemy
 * Signature: SoldierEnemy * SoldierEnemy(SoldierEnemy * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

SoldierEnemy * __thiscall SoldierEnemy::SoldierEnemy(SoldierEnemy *this)

{
  OffensiveProcess::OffensiveProcess((OffensiveProcess *)this);
  *(undefined ***)this = &_vftable_;
  return this;
}
