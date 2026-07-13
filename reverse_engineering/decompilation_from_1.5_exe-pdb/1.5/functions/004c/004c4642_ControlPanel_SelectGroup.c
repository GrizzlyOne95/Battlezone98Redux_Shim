/*
 * Entry: 004c4642
 * Name: ControlPanel::SelectGroup
 * Namespace: ControlPanel
 * Signature: void SelectGroup(ControlPanel * this, long param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall ControlPanel::SelectGroup(ControlPanel *this,long param_1)

{
  char cVar1;
  GameObject *pGVar2;
  int iVar3;
  int (*paiVar4) [90];
  int *piVar5;
  int local_8;
  
  iVar3 = 0;
  if (0 < this->selectNum) {
    piVar5 = this->selectList;
    do {
      pGVar2 = GameObject::GetObj(*piVar5);
      GameObject::SetSelected(pGVar2,false);
      iVar3 = iVar3 + 1;
      piVar5 = piVar5 + 1;
    } while (iVar3 < this->selectNum);
  }
  this->selectNum = 0;
  local_8 = 0;
  if (0 < this->groupNum[param_1]) {
    paiVar4 = this->groupList + param_1;
    do {
      pGVar2 = GameObject::GetObj((*paiVar4)[0]);
      if (pGVar2 != (GameObject *)0x0) {
        cVar1 = (**(code **)(pGVar2->_padding_ + 0x38))();
        if (cVar1 != '\0') {
          this->selectList[this->selectNum] = (*paiVar4)[0];
          this->selectNum = this->selectNum + 1;
          GameObject::SetSelected(pGVar2,true);
        }
      }
      local_8 = local_8 + 1;
      paiVar4 = (int (*) [90])(*paiVar4 + 1);
    } while (local_8 < this->groupNum[param_1]);
  }
  this->currentItem = -1;
  this->itemSelected = 0;
  return;
}
