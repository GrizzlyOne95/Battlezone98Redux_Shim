/*
 * Entry: 00413268
 * Name: GotoGeyser::PostLoad
 * Namespace: GotoGeyser
 * Signature: bool PostLoad(GotoGeyser * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall GotoGeyser::PostLoad(GotoGeyser *this)

{
  bool bVar1;
  
  bVar1 = UnitTask::PostLoad((UnitTask *)this);
  return bVar1;
}
