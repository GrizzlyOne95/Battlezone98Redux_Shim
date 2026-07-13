/*
 * Entry: 0040d152
 * Name: SLFEnemy::SLFEnemy
 * Namespace: SLFEnemy
 * Signature: SLFEnemy * SLFEnemy(SLFEnemy * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

SLFEnemy * __thiscall SLFEnemy::SLFEnemy(SLFEnemy *this)

{
  ArmoryProcess::ArmoryProcess((ArmoryProcess *)this);
  *(undefined ***)this = &_vftable_;
  return this;
}
