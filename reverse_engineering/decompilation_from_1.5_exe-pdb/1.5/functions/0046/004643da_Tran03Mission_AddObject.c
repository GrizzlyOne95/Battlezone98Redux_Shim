/*
 * Entry: 004643da
 * Name: Tran03Mission::AddObject
 * Namespace: Tran03Mission
 * Signature: void AddObject(Tran03Mission * this, int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Tran03Mission::AddObject(Tran03Mission *this,int param_1)

{
  bool bVar1;
  int iVar2;
  
  iVar2 = GetTeamNum(param_1);
  if (iVar2 == 1) {
    bVar1 = IsOdf(param_1,"avscav");
    if (bVar1) {
      (this->field16_0x40)._s_0.found = true;
      (this->field18_0x64)._s_0.scav = param_1;
    }
  }
  return;
}
