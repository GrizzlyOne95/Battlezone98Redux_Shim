/*
 * Entry: 0046303b
 * Name: SoldierProcess::SoldierProcess
 * Namespace: SoldierProcess
 * Signature: SoldierProcess * SoldierProcess(SoldierProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

SoldierProcess * __thiscall SoldierProcess::SoldierProcess(SoldierProcess *this)

{
  OffensiveProcess::OffensiveProcess((OffensiveProcess *)this);
  *(undefined ***)this = &_vftable_;
  return this;
}
