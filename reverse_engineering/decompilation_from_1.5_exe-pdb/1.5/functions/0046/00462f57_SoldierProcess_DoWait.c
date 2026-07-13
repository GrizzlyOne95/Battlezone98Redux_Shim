/*
 * Entry: 00462f57
 * Name: SoldierProcess::DoWait
 * Namespace: SoldierProcess
 * Signature: void DoWait(SoldierProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall SoldierProcess::DoWait(SoldierProcess *this)

{
  float fVar1;
  
  fVar1 = Get_Time();
  if (*(float *)&this->field_0x54 < fVar1) {
    *(undefined4 *)&this->field_0x1c = 0x10;
    return;
  }
  UnitProcess::DoWait((UnitProcess *)this);
  return;
}
