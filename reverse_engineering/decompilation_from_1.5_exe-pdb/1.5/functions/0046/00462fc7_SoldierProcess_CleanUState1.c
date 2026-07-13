/*
 * Entry: 00462fc7
 * Name: SoldierProcess::CleanUState1
 * Namespace: SoldierProcess
 * Signature: void CleanUState1(SoldierProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall SoldierProcess::CleanUState1(SoldierProcess *this)

{
  if (*(undefined4 **)&this->field_0x30 != (undefined4 *)0x0) {
    (**(code **)**(undefined4 **)&this->field_0x30)(1);
  }
  *(undefined4 *)&this->field_0x30 = 0;
  return;
}
