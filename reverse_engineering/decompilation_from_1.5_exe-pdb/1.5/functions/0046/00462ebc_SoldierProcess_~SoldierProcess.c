/*
 * Entry: 00462ebc
 * Name: SoldierProcess::~SoldierProcess
 * Namespace: SoldierProcess
 * Signature: void ~SoldierProcess(SoldierProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall SoldierProcess::~SoldierProcess(SoldierProcess *this)

{
  *(undefined ***)this = &_vftable_;
  UnitProcess::CleanState((UnitProcess *)this);
  *(undefined4 *)&this->field_0x18 = 0;
  OffensiveProcess::~OffensiveProcess((OffensiveProcess *)this);
  return;
}
