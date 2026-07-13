/*
 * Entry: 0040bc89
 * Name: APCProcess::CleanReload
 * Namespace: APCProcess
 * Signature: void CleanReload(APCProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall APCProcess::CleanReload(APCProcess *this)

{
  if (*(undefined4 **)&this->field_0x30 != (undefined4 *)0x0) {
    (**(code **)**(undefined4 **)&this->field_0x30)(1);
  }
  *(undefined4 *)&this->field_0x30 = 0;
  return;
}
