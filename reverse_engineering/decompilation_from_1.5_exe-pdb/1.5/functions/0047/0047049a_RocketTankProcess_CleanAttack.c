/*
 * Entry: 0047049a
 * Name: RocketTankProcess::CleanAttack
 * Namespace: RocketTankProcess
 * Signature: void CleanAttack(RocketTankProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall RocketTankProcess::CleanAttack(RocketTankProcess *this)

{
  if (*(undefined4 **)&this->field_0x30 != (undefined4 *)0x0) {
    (**(code **)**(undefined4 **)&this->field_0x30)(1);
  }
  *(undefined4 *)&this->field_0x30 = 0;
  return;
}
