/*
 * Entry: 0043a30d
 * Name: Misn16Mission::AddObject
 * Namespace: Misn16Mission
 * Signature: void AddObject(Misn16Mission * this, int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Misn16Mission::AddObject(Misn16Mission *this,int param_1)

{
  bool bVar1;
  int iVar2;
  uint uVar3;
  
  iVar2 = GetTeamNum(param_1);
  if (iVar2 != 1) {
    return;
  }
  bVar1 = IsOdf(param_1,"svtank");
  if ((((bVar1) || (bVar1 = IsOdf(param_1,"svturr"), bVar1)) ||
      (bVar1 = IsOdf(param_1,"svfigh"), bVar1)) || (bVar1 = IsOdf(param_1,"svwalk"), bVar1)) {
    uVar3 = rand();
    uVar3 = uVar3 & 0x80000001;
    bVar1 = uVar3 == 0;
    if ((int)uVar3 < 0) {
      bVar1 = (uVar3 - 1 | 0xfffffffe) == 0xffffffff;
    }
    if (bVar1) {
      iVar2 = (this->field18_0x70)._s_0.base1;
    }
    else {
      iVar2 = (this->field18_0x70)._s_0.base2;
    }
    Attack(param_1,iVar2,0);
  }
  else {
    bVar1 = IsOdf(param_1,"svscav");
    if ((!bVar1) && (bVar1 = IsOdf(param_1,"svhaul"), !bVar1)) {
      return;
    }
    uVar3 = rand();
    uVar3 = uVar3 & 0x80000001;
    bVar1 = uVar3 == 0;
    if ((int)uVar3 < 0) {
      bVar1 = (uVar3 - 1 | 0xfffffffe) == 0xffffffff;
    }
    if (bVar1) {
      iVar2 = (this->field18_0x70)._s_0.base1;
    }
    else {
      iVar2 = (this->field18_0x70)._s_0.base2;
    }
    Goto(param_1,iVar2,0);
  }
  (this->field18_0x70)._s_0.newbie = param_1;
  return;
}
