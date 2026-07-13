/*
 * Entry: 00462ffe
 * Name: SoldierProcess::CleanUState2
 * Namespace: SoldierProcess
 * Signature: void CleanUState2(SoldierProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall SoldierProcess::CleanUState2(SoldierProcess *this)

{
  if (*(undefined4 **)&this->field_0x30 != (undefined4 *)0x0) {
    (**(code **)**(undefined4 **)&this->field_0x30)(1);
  }
  *(undefined4 *)&this->field_0x30 = 0;
  return;
}
