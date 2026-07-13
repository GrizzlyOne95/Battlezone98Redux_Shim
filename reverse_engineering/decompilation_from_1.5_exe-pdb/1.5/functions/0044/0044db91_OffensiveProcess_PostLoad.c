/*
 * Entry: 0044db91
 * Name: OffensiveProcess::PostLoad
 * Namespace: OffensiveProcess
 * Signature: bool PostLoad(OffensiveProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall OffensiveProcess::PostLoad(OffensiveProcess *this)

{
  bool bVar1;
  
  bVar1 = UnitProcess::PostLoad((UnitProcess *)this);
  return bVar1;
}
