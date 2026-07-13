/*
 * Entry: 00462fdd
 * Name: SoldierProcess::DoUState1
 * Namespace: SoldierProcess
 * Signature: void DoUState1(SoldierProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall SoldierProcess::DoUState1(SoldierProcess *this)

{
  char cVar1;
  
  cVar1 = (**(code **)(**(int **)&this->field_0x30 + 0x18))();
  if (cVar1 != '\0') {
    *(undefined4 *)&this->field_0x1c = 3;
    return;
  }
                    /* WARNING: Could not recover jumptable at 0x00462ffb. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(**(int **)&this->field_0x30 + 0x1c))();
  return;
}
