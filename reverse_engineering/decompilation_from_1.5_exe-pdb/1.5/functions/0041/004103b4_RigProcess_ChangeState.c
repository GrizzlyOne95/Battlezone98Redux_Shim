/*
 * Entry: 004103b4
 * Name: RigProcess::ChangeState
 * Namespace: RigProcess
 * Signature: void ChangeState(RigProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall RigProcess::ChangeState(RigProcess *this)

{
  if (*(int *)&this->field_0x1c == 0x10) {
    *(undefined4 *)&this->field_0x38 = *(undefined4 *)(*(int *)&this->field_0x2c + 0xb8);
    this->field_0x3c = 0;
    return;
  }
  if (*(int *)&this->field_0x1c != 0x11) {
    UnitProcess::ChangeState((UnitProcess *)this);
    return;
  }
  *(undefined4 *)&this->field_0x34 = *(undefined4 *)(*(int *)&this->field_0x2c + 0xb4);
  return;
}
