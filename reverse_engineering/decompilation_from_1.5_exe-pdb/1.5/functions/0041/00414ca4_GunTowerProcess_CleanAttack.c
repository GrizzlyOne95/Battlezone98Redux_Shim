/*
 * Entry: 00414ca4
 * Name: GunTowerProcess::CleanAttack
 * Namespace: GunTowerProcess
 * Signature: void CleanAttack(GunTowerProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall GunTowerProcess::CleanAttack(GunTowerProcess *this)

{
  if (*(undefined4 **)&this->field_0x30 != (undefined4 *)0x0) {
    (**(code **)**(undefined4 **)&this->field_0x30)(1);
  }
  *(undefined4 *)&this->field_0x30 = 0;
  return;
}
