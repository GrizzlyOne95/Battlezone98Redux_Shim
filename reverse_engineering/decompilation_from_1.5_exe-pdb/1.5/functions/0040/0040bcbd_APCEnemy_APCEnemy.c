/*
 * Entry: 0040bcbd
 * Name: APCEnemy::APCEnemy
 * Namespace: APCEnemy
 * Signature: APCEnemy * APCEnemy(APCEnemy * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

APCEnemy * __thiscall APCEnemy::APCEnemy(APCEnemy *this)

{
  UnitProcess::UnitProcess((UnitProcess *)this);
  *(undefined ***)this = &_vftable_;
  return this;
}
