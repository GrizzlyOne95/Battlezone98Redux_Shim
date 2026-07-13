/*
 * Entry: 00463014
 * Name: SoldierProcess::DoUState2
 * Namespace: SoldierProcess
 * Signature: void DoUState2(SoldierProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall SoldierProcess::DoUState2(SoldierProcess *this)

{
  char cVar1;
  
  cVar1 = (**(code **)(**(int **)&this->field_0x30 + 0x18))();
  if (cVar1 != '\0') {
    *(undefined4 *)&this->field_0x1c = 3;
    return;
  }
                    /* WARNING: Could not recover jumptable at 0x00463032. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(**(int **)&this->field_0x30 + 0x1c))();
  return;
}
