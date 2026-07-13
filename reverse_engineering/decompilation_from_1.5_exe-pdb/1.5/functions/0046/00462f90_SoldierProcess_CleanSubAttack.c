/*
 * Entry: 00462f90
 * Name: SoldierProcess::CleanSubAttack
 * Namespace: SoldierProcess
 * Signature: void CleanSubAttack(SoldierProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall SoldierProcess::CleanSubAttack(SoldierProcess *this)

{
  if (*(undefined4 **)&this->field_0x30 != (undefined4 *)0x0) {
    (**(code **)**(undefined4 **)&this->field_0x30)(1);
  }
  *(undefined4 *)&this->field_0x30 = 0;
  return;
}
