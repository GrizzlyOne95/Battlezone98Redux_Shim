/*
 * Entry: 0047038f
 * Name: ScoutEnemy::~ScoutEnemy
 * Namespace: ScoutEnemy
 * Signature: void ~ScoutEnemy(ScoutEnemy * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall ScoutEnemy::~ScoutEnemy(ScoutEnemy *this)

{
  *(undefined ***)this = &WingmanProcess::_vftable_;
  UnitProcess::CleanState((UnitProcess *)this);
  *(undefined4 *)&this->field_0x18 = 0;
  OffensiveProcess::~OffensiveProcess((OffensiveProcess *)this);
  return;
}
