/*
 * Entry: 00420d4c
 * Name: Misn04Mission::AddObject
 * Namespace: Misn04Mission
 * Signature: void AddObject(Misn04Mission * this, int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Misn04Mission::AddObject(Misn04Mission *this,int param_1)

{
  bool bVar1;
  int iVar2;
  
  iVar2 = GetTeamNum(param_1);
  if (iVar2 == 1) {
    bVar1 = IsOdf(param_1,"avhaul");
    if (bVar1) {
      (this->field16_0x40)._s_0.found = true;
      (this->field18_0x104)._s_0.tug = param_1;
    }
  }
  return;
}
