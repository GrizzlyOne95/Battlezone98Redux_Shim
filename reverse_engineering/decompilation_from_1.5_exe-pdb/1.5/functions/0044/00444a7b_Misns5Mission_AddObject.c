/*
 * Entry: 00444a7b
 * Name: Misns5Mission::AddObject
 * Namespace: Misns5Mission
 * Signature: void AddObject(Misns5Mission * this, int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Misns5Mission::AddObject(Misns5Mission *this,int param_1)

{
  bool bVar1;
  int iVar2;
  
  iVar2 = GetTeamNum(param_1);
  if (iVar2 == 2) {
    bVar1 = IsOdf(param_1,"avwalk");
    if (bVar1) {
      (this->field18_0x68)._s_0.commander = param_1;
    }
    bVar1 = IsOdf(param_1,"bvltnk");
    if (((!bVar1) && (bVar1 = IsOdf(param_1,"bvhraz"), !bVar1)) &&
       (bVar1 = IsOdf(param_1,"avfigh"), !bVar1)) {
      return;
    }
    Goto(param_1,(this->field18_0x68)._s_0.recy,1);
  }
  return;
}
