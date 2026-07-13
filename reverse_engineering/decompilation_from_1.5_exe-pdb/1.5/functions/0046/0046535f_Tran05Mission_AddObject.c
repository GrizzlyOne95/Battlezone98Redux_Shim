/*
 * Entry: 0046535f
 * Name: Tran05Mission::AddObject
 * Namespace: Tran05Mission
 * Signature: void AddObject(Tran05Mission * this, int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Tran05Mission::AddObject(Tran05Mission *this,int param_1)

{
  bool bVar1;
  int iVar2;
  int *piVar3;
  float fVar4;
  
  iVar2 = GetTeamNum(param_1);
  if (((iVar2 == 1) && (bVar1 = IsOdf(param_1,"avscav"), bVar1)) &&
     (piVar3 = &(this->field18_0x7c)._s_0.bscav, *piVar3 == 0)) {
    (this->field16_0x40)._s_0.found = true;
    *piVar3 = param_1;
  }
  iVar2 = GetTeamNum(param_1);
  if ((iVar2 == 2) && (bVar1 = IsOdf(param_1,"svfigh"), bVar1)) {
    if ((this->field16_0x40)._s_0.found2 == false) {
      (this->field16_0x40)._s_0.found2 = true;
      piVar3 = &(this->field18_0x7c)._s_0.bscout;
      *piVar3 = param_1;
      Goto(param_1,"patrol1",0);
      SetObjectiveOn(*piVar3);
    }
    else {
      fVar4 = GetDistance((this->field18_0x7c)._s_0.bscav,(this->field18_0x7c)._s_0.bgoal);
      if (200.0 <= fVar4) {
        Goto(param_1,"patrol2",0);
      }
      else {
        Attack(param_1,(this->field18_0x7c)._s_0.bscav,1);
      }
    }
  }
  return;
}
