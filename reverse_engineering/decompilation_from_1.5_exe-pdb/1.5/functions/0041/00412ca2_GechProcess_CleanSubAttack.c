/*
 * Entry: 00412ca2
 * Name: GechProcess::CleanSubAttack
 * Namespace: GechProcess
 * Signature: void CleanSubAttack(GechProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall GechProcess::CleanSubAttack(GechProcess *this)

{
  if (*(undefined4 **)&this->field_0x30 != (undefined4 *)0x0) {
    (**(code **)**(undefined4 **)&this->field_0x30)(1);
  }
  *(undefined4 *)&this->field_0x30 = 0;
  return;
}
