/*
 * Entry: 00462f7a
 * Name: SoldierProcess::CleanAttack
 * Namespace: SoldierProcess
 * Signature: void CleanAttack(SoldierProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall SoldierProcess::CleanAttack(SoldierProcess *this)

{
  if (*(undefined4 **)&this->field_0x30 != (undefined4 *)0x0) {
    (**(code **)**(undefined4 **)&this->field_0x30)(1);
  }
  *(undefined4 *)&this->field_0x30 = 0;
  return;
}
