/*
 * Entry: 0040bc73
 * Name: APCProcess::CleanAttack
 * Namespace: APCProcess
 * Signature: void CleanAttack(APCProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall APCProcess::CleanAttack(APCProcess *this)

{
  if (*(undefined4 **)&this->field_0x30 != (undefined4 *)0x0) {
    (**(code **)**(undefined4 **)&this->field_0x30)(1);
  }
  *(undefined4 *)&this->field_0x30 = 0;
  return;
}
