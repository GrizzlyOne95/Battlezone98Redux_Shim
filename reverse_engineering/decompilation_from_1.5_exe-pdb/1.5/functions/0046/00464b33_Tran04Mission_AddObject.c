/*
 * Entry: 00464b33
 * Name: Tran04Mission::AddObject
 * Namespace: Tran04Mission
 * Signature: void AddObject(Tran04Mission * this, int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Tran04Mission::AddObject(Tran04Mission *this,int param_1)

{
  bool bVar1;
  int iVar2;
  
  iVar2 = GetTeamNum(param_1);
  if (iVar2 == 1) {
    bVar1 = IsOdf(param_1,"avmuf");
    if (bVar1) {
      (this->field16_0x40)._s_0.found1 = true;
      (this->field18_0x64)._s_0.muf = param_1;
    }
  }
  iVar2 = GetTeamNum(param_1);
  if (iVar2 == 1) {
    bVar1 = IsOdf(param_1,"avfigh");
    if (bVar1) {
      (this->field16_0x40)._s_0.found2 = true;
      (this->field18_0x64)._s_0.wing = param_1;
    }
  }
  return;
}
