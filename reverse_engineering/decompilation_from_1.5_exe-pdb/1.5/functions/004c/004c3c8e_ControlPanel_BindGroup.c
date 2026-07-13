/*
 * Entry: 004c3c8e
 * Name: ControlPanel::BindGroup
 * Namespace: ControlPanel
 * Signature: void BindGroup(ControlPanel * this, long param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall ControlPanel::BindGroup(ControlPanel *this,long param_1)

{
  int *piVar1;
  int (*paiVar2) [90];
  int iVar3;
  
  iVar3 = 0;
  this->groupNum[param_1] = this->selectNum;
  if (0 < this->selectNum) {
    paiVar2 = this->groupList + param_1;
    piVar1 = this->selectList;
    do {
      (*paiVar2)[0] = *piVar1;
      iVar3 = iVar3 + 1;
      piVar1 = piVar1 + 1;
      paiVar2 = (int (*) [90])(*paiVar2 + 1);
    } while (iVar3 < this->selectNum);
  }
  return;
}
