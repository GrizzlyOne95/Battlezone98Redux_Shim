/*
 * Entry: 004384b1
 * Name: Misn14Mission::AddObject
 * Namespace: Misn14Mission
 * Signature: void AddObject(Misn14Mission * this, int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Misn14Mission::AddObject(Misn14Mission *this,int param_1)

{
  bool bVar1;
  int iVar2;
  
  bVar1 = IsOdf(param_1,"avapc");
  if (bVar1) {
    iVar2 = GetTeamNum(param_1);
    if (iVar2 == 1) {
      (this->field16_0x40)._s_0.found = true;
      (this->field18_0x88)._s_0.apc = param_1;
    }
  }
  return;
}
