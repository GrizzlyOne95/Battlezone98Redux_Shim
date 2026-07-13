/*
 * Entry: 00410587
 * Name: RigProcess::CleanUState1
 * Namespace: RigProcess
 * Signature: void CleanUState1(RigProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall RigProcess::CleanUState1(RigProcess *this)

{
  if (*(undefined4 **)&this->field_0x30 != (undefined4 *)0x0) {
    (**(code **)**(undefined4 **)&this->field_0x30)(1);
  }
  *(undefined4 *)&this->field_0x30 = 0;
                    /* WARNING: Could not recover jumptable at 0x004105a1. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(**(int **)&this->field_0x2c + 0x60))();
  return;
}
