/*
 * Entry: 00470271
 * Name: WingmanProcess::CleanUState1
 * Namespace: WingmanProcess
 * Signature: void CleanUState1(WingmanProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall WingmanProcess::CleanUState1(WingmanProcess *this)

{
  if (*(undefined4 **)&this->field_0x30 != (undefined4 *)0x0) {
    (**(code **)**(undefined4 **)&this->field_0x30)(1);
  }
  *(undefined4 *)&this->field_0x30 = 0;
  return;
}
