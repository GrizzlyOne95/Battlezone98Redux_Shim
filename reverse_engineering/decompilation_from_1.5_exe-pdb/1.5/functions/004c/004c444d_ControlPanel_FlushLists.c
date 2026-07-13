/*
 * Entry: 004c444d
 * Name: ControlPanel::FlushLists
 * Namespace: ControlPanel
 * Signature: void FlushLists(ControlPanel * this, int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall ControlPanel::FlushLists(ControlPanel *this,int param_1)

{
  GameObject *this_00;
  long *plVar1;
  int *piVar2;
  int iVar3;
  int *piVar4;
  long lVar5;
  int (*paiVar6) [90];
  int (*paiVar7) [90];
  int local_14;
  int (*local_c) [90];
  int local_8;
  
  lVar5 = 0;
  local_8 = 0;
  if (0 < this->selectNum) {
    piVar2 = this->selectList;
    local_c = &piVar2;
    do {
      if ((*local_c)[0] == param_1) {
        this_00 = GameObject::GetObj(param_1);
        if (this_00 != (GameObject *)0x0) {
          GameObject::SetSelected(this_00,false);
        }
        this->currentItem = -1;
        this->itemSelected = 0;
      }
      else {
        *piVar2 = (*local_c)[0];
        lVar5 = lVar5 + 1;
        piVar2 = piVar2 + 1;
      }
      local_8 = local_8 + 1;
      local_c = (int (*) [90])((int)local_c + 4);
    } while (local_8 < this->selectNum);
  }
  paiVar6 = this->groupList;
  this->selectNum = lVar5;
  plVar1 = this->groupNum;
  local_14 = 10;
  do {
    iVar3 = 0;
    local_8 = 0;
    paiVar7 = paiVar6;
    local_c = paiVar6;
    if (0 < *plVar1) {
      do {
        if ((*paiVar7)[0] != param_1) {
          iVar3 = iVar3 + 1;
          (*local_c)[0] = (*paiVar7)[0];
          local_c = (int (*) [90])(*local_c + 1);
        }
        local_8 = local_8 + 1;
        paiVar7 = (int (*) [90])(*paiVar7 + 1);
      } while (local_8 < *plVar1);
    }
    *plVar1 = iVar3;
    paiVar6 = paiVar6 + 1;
    plVar1 = plVar1 + 1;
    local_14 = local_14 + -1;
  } while (local_14 != 0);
  iVar3 = 0;
  lVar5 = 0;
  if (0 < this->targetNum) {
    piVar2 = this->targetList;
    piVar4 = piVar2;
    do {
      if (*piVar4 != param_1) {
        *piVar2 = *piVar4;
        lVar5 = lVar5 + 1;
        piVar2 = piVar2 + 1;
      }
      iVar3 = iVar3 + 1;
      piVar4 = piVar4 + 1;
    } while (iVar3 < this->targetNum);
  }
  this->targetNum = lVar5;
  return;
}
