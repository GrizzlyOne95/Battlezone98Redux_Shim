/*
 * Entry: 00412c8c
 * Name: GechProcess::CleanAttack
 * Namespace: GechProcess
 * Signature: void CleanAttack(GechProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall GechProcess::CleanAttack(GechProcess *this)

{
  if (*(undefined4 **)&this->field_0x30 != (undefined4 *)0x0) {
    (**(code **)**(undefined4 **)&this->field_0x30)(1);
  }
  *(undefined4 *)&this->field_0x30 = 0;
  return;
}
