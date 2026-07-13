/*
 * Entry: 0044426b
 * Name: Misns4Mission::AddObject
 * Namespace: Misns4Mission
 * Signature: void AddObject(Misns4Mission * this, int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Misns4Mission::AddObject(Misns4Mission *this,int param_1)

{
  int *piVar1;
  bool bVar2;
  int iVar3;
  
  iVar3 = GetTeamNum(param_1);
  if (iVar3 == 1) {
    bVar2 = IsOdf(param_1,"svhaul");
    if (bVar2) {
      piVar1 = &(this->field19_0xd4)._s_0.convoy_count;
      *(int *)((int)&this->field18_0x7c + *piVar1 * 4) = param_1;
      *piVar1 = *piVar1 + 1;
      Goto(param_1,"escort",1);
    }
  }
  return;
}
