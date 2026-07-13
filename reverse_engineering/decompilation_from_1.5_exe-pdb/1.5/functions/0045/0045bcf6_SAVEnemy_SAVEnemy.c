/*
 * Entry: 0045bcf6
 * Name: SAVEnemy::SAVEnemy
 * Namespace: SAVEnemy
 * Signature: SAVEnemy * SAVEnemy(SAVEnemy * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

SAVEnemy * __thiscall SAVEnemy::SAVEnemy(SAVEnemy *this)

{
  UnitProcess::UnitProcess((UnitProcess *)this);
  *(undefined ***)this = &_vftable_;
  return this;
}
