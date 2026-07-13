/*
 * Entry: 00412cb8
 * Name: GechProcess::DoSubAttack
 * Namespace: GechProcess
 * Signature: void DoSubAttack(GechProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall GechProcess::DoSubAttack(GechProcess *this)

{
  char cVar1;
  
  cVar1 = (**(code **)(**(int **)&this->field_0x30 + 0x18))();
  if (cVar1 != '\0') {
    *(undefined4 *)&this->field_0x1c = 3;
    return;
  }
                    /* WARNING: Could not recover jumptable at 0x00412cd6. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(**(int **)&this->field_0x30 + 0x1c))();
  return;
}
