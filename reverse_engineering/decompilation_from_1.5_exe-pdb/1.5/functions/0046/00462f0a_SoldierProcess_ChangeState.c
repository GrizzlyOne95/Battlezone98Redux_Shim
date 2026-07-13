/*
 * Entry: 00462f0a
 * Name: SoldierProcess::ChangeState
 * Namespace: SoldierProcess
 * Signature: void ChangeState(SoldierProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall SoldierProcess::ChangeState(SoldierProcess *this)

{
  if (*(int *)&this->field_0x1c == 0x11) {
    *(undefined4 *)&this->field_0x34 = *(undefined4 *)(*(int *)&this->field_0x2c + 0xb4);
    *(undefined4 *)&this->field_0x38 = *(undefined4 *)(*(int *)&this->field_0x2c + 0xb8);
    return;
  }
  UnitProcess::ChangeState((UnitProcess *)this);
  return;
}
