/*
 * Entry: 00410695
 * Name: RigProcess::CleanUState2
 * Namespace: RigProcess
 * Signature: void CleanUState2(RigProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall RigProcess::CleanUState2(RigProcess *this)

{
  ConstructionRig::CancelUnbuild(*(ConstructionRig **)&this->field_0x2c);
  if (*(undefined4 **)&this->field_0x30 != (undefined4 *)0x0) {
    (**(code **)**(undefined4 **)&this->field_0x30)(1);
  }
  *(undefined4 *)&this->field_0x30 = 0;
  return;
}
