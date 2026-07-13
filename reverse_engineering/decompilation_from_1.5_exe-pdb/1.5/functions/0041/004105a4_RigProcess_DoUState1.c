/*
 * Entry: 004105a4
 * Name: RigProcess::DoUState1
 * Namespace: RigProcess
 * Signature: void DoUState1(RigProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall RigProcess::DoUState1(RigProcess *this)

{
  bool bVar1;
  char cVar2;
  
  if (*(int *)(*(int *)&this->field_0x30 + 0x150) == 3) {
    bVar1 = Producer::IsBusy(*(Producer **)&this->field_0x2c);
    if (!bVar1) {
      Say(*(Craft **)&this->field_0x2c,USER2_MSG,0);
    }
  }
  cVar2 = (**(code **)(**(int **)&this->field_0x30 + 0x18))();
  if (cVar2 != '\0') {
    *(undefined4 *)&this->field_0x1c = 3;
    return;
  }
                    /* WARNING: Could not recover jumptable at 0x004105e9. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(**(int **)&this->field_0x30 + 0x1c))();
  return;
}
