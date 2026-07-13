/*
 * Entry: 00412d09
 * Name: GechEnemy::~GechEnemy
 * Namespace: GechEnemy
 * Signature: void ~GechEnemy(GechEnemy * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall GechEnemy::~GechEnemy(GechEnemy *this)

{
  *(undefined ***)this = &GechProcess::_vftable_;
  UnitProcess::CleanState((UnitProcess *)this);
  *(undefined4 *)&this->field_0x18 = 0;
  OffensiveProcess::~OffensiveProcess((OffensiveProcess *)this);
  return;
}
