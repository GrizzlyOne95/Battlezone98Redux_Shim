/*
 * Entry: 00445342
 * Name: Misns6Mission::AddObject
 * Namespace: Misns6Mission
 * Signature: void AddObject(Misns6Mission * this, int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Misns6Mission::AddObject(Misns6Mission *this,int param_1)

{
  int iVar1;
  bool bVar2;
  int iVar3;
  float fVar4;
  
  iVar1 = param_1;
  iVar3 = GetTeamNum(param_1);
  if ((iVar3 == 2) && (bVar2 = IsOdf(param_1,"avmine"), bVar2)) {
    param_1 = 0x47c34f80;
    fVar4 = GetDistance(iVar1,"m1",1);
    if (99999.0 <= fVar4) {
      iVar3 = 0x47c34f80;
    }
    else {
      iVar3 = 0;
      Goto(iVar1,"s1",1);
      param_1 = (int)fVar4;
    }
    fVar4 = GetDistance(iVar1,"m2",1);
    if (fVar4 < (float)param_1) {
      Goto(iVar1,"s2",1);
      iVar3 = 1;
      param_1 = (int)fVar4;
    }
    fVar4 = GetDistance(iVar1,"m3",1);
    if (fVar4 < (float)param_1) {
      iVar3 = 2;
      Goto(iVar1,"s3",1);
    }
    *(int *)((int)&this->field18_0x6c + iVar3 * 4 + 0x28) = iVar1;
    (this->field19_0xb0)._s_0.next_target = iVar3;
  }
  return;
}
