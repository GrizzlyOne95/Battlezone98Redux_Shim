/*
 * Entry: 00470212
 * Name: WingmanProcess::CleanSubAttack
 * Namespace: WingmanProcess
 * Signature: void CleanSubAttack(WingmanProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall WingmanProcess::CleanSubAttack(WingmanProcess *this)

{
  if (*(undefined4 **)&this->field_0x30 != (undefined4 *)0x0) {
    (**(code **)**(undefined4 **)&this->field_0x30)(1);
  }
  *(undefined4 *)&this->field_0x30 = 0;
  return;
}
