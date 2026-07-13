/*
 * Entry: 0045b9f6
 * Name: SAVProcess::ChangesState
 * Namespace: SAVProcess
 * Signature: bool ChangesState(SAVProcess * this, AiCommand param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall SAVProcess::ChangesState(SAVProcess *this,AiCommand param_1)

{
  bool bVar1;
  
  if (param_1 == CMD_NONE) {
    return false;
  }
  bVar1 = UnitProcess::ChangesState((UnitProcess *)this,param_1);
  return bVar1;
}
