/*
 * Entry: 004701f6
 * Name: WingmanProcess::ChangeState
 * Namespace: WingmanProcess
 * Signature: void ChangeState(WingmanProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall WingmanProcess::ChangeState(WingmanProcess *this)

{
  if (*(int *)&this->field_0x1c == 0x10) {
    *(undefined4 *)&this->field_0x38 = *(undefined4 *)(*(int *)&this->field_0x2c + 0xb8);
    this->field_0x3c = 0;
    return;
  }
  UnitProcess::ChangeState((UnitProcess *)this);
  return;
}
