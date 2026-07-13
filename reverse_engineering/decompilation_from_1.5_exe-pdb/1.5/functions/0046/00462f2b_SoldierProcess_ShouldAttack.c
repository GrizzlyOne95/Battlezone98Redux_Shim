/*
 * Entry: 00462f2b
 * Name: SoldierProcess::ShouldAttack
 * Namespace: SoldierProcess
 * Signature: bool ShouldAttack(SoldierProcess * this, State param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall SoldierProcess::ShouldAttack(SoldierProcess *this,State param_1)

{
  bool bVar1;
  
  if (param_1 == WAIT) {
    bVar1 = OffensiveProcess::WaitVsAttack((OffensiveProcess *)this);
  }
  else {
    bVar1 = false;
  }
  return bVar1;
}
