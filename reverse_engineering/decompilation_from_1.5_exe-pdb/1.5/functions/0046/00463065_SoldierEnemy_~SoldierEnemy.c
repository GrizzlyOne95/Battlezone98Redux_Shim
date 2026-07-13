/*
 * Entry: 00463065
 * Name: SoldierEnemy::~SoldierEnemy
 * Namespace: SoldierEnemy
 * Signature: void ~SoldierEnemy(SoldierEnemy * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall SoldierEnemy::~SoldierEnemy(SoldierEnemy *this)

{
  *(undefined ***)this = &SoldierProcess::_vftable_;
  UnitProcess::CleanState((UnitProcess *)this);
  *(undefined4 *)&this->field_0x18 = 0;
  OffensiveProcess::~OffensiveProcess((OffensiveProcess *)this);
  return;
}
