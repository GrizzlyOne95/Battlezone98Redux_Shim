/*
 * Entry: 004572cd
 * Name: PersonEnemy::~PersonEnemy
 * Namespace: PersonEnemy
 * Signature: void ~PersonEnemy(PersonEnemy * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall PersonEnemy::~PersonEnemy(PersonEnemy *this)

{
  *(undefined ***)this = &PersonProcess::_vftable_;
  UnitProcess::CleanState((UnitProcess *)this);
  *(undefined4 *)&this->field_0x18 = 0;
  OffensiveProcess::~OffensiveProcess((OffensiveProcess *)this);
  return;
}
