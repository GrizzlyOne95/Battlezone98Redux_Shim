/*
 * Entry: 00412cf7
 * Name: GechEnemy::GechEnemy
 * Namespace: GechEnemy
 * Signature: GechEnemy * GechEnemy(GechEnemy * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GechEnemy * __thiscall GechEnemy::GechEnemy(GechEnemy *this)

{
  OffensiveProcess::OffensiveProcess((OffensiveProcess *)this);
  *(undefined ***)this = &_vftable_;
  return this;
}
