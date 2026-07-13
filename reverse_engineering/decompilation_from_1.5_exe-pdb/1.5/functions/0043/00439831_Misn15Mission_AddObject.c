/*
 * Entry: 00439831
 * Name: Misn15Mission::AddObject
 * Namespace: Misn15Mission
 * Signature: void AddObject(Misn15Mission * this, int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Misn15Mission::AddObject(Misn15Mission *this,int param_1)

{
  int *piVar1;
  bool bVar2;
  int iVar3;
  
  iVar3 = GetTeamNum(param_1);
  if (iVar3 == 1) {
    bVar2 = IsOdf(param_1,"avscav");
    if (bVar2) {
      (this->field16_0x40)._s_0.found = true;
      (this->field18_0x80)._s_0.scav_du_jour = param_1;
    }
    else {
      bVar2 = IsOdf(param_1,"absilo");
      if (bVar2) {
        piVar1 = &(this->field19_0x288)._s_0.silocount;
        *piVar1 = *piVar1 + 1;
      }
    }
  }
  return;
}
