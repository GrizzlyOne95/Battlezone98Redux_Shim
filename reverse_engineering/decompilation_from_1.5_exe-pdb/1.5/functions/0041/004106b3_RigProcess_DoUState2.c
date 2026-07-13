/*
 * Entry: 004106b3
 * Name: RigProcess::DoUState2
 * Namespace: RigProcess
 * Signature: void DoUState2(RigProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall RigProcess::DoUState2(RigProcess *this)

{
  char cVar1;
  
  cVar1 = (**(code **)(**(int **)&this->field_0x30 + 0x18))();
  if (cVar1 != '\0') {
    *(undefined4 *)&this->field_0x1c = 3;
    return;
  }
                    /* WARNING: Could not recover jumptable at 0x004106d1. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(**(int **)&this->field_0x30 + 0x1c))();
  return;
}
