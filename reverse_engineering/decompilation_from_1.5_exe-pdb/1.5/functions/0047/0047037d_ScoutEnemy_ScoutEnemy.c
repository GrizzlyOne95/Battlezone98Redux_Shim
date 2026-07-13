/*
 * Entry: 0047037d
 * Name: ScoutEnemy::ScoutEnemy
 * Namespace: ScoutEnemy
 * Signature: ScoutEnemy * ScoutEnemy(ScoutEnemy * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

ScoutEnemy * __thiscall ScoutEnemy::ScoutEnemy(ScoutEnemy *this)

{
  WingmanProcess::WingmanProcess((WingmanProcess *)this);
  *(undefined ***)this = &_vftable_;
  return this;
}
