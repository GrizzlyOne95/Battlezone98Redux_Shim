/*
 * Entry: 00462f3e
 * Name: SoldierProcess::InitWait
 * Namespace: SoldierProcess
 * Signature: void InitWait(SoldierProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall SoldierProcess::InitWait(SoldierProcess *this)

{
  float fVar1;
  
  fVar1 = Get_Time();
  *(float *)&this->field_0x54 = fVar1 + 5.0;
  OffensiveProcess::InitWait((OffensiveProcess *)this);
  return;
}
