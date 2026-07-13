/*
 * Entry: 0045ba07
 * Name: SAVProcess::CleanAttack
 * Namespace: SAVProcess
 * Signature: void CleanAttack(SAVProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall SAVProcess::CleanAttack(SAVProcess *this)

{
  if (*(undefined4 **)&this->field_0x30 != (undefined4 *)0x0) {
    (**(code **)**(undefined4 **)&this->field_0x30)(1);
  }
  *(undefined4 *)&this->field_0x30 = 0;
  return;
}
