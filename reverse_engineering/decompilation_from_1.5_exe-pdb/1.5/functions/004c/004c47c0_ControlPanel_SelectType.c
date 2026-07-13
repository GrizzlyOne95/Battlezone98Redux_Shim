/*
 * Entry: 004c47c0
 * Name: ControlPanel::SelectType
 * Namespace: ControlPanel
 * Signature: void SelectType(ControlPanel * this, int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall ControlPanel::SelectType(ControlPanel *this,int param_1)

{
  long *plVar1;
  Team *this_00;
  char cVar2;
  GameObject *this_01;
  int iVar3;
  int iVar4;
  
  SelectNone(this);
  this_00 = GameObject::userTeamList;
  iVar4 = MENU_ITEM[param_1].minSlot;
  if (iVar4 <= MENU_ITEM[param_1].maxSlot) {
    do {
      this_01 = Team::GetSlot(this_00,iVar4);
      if ((this_01 != (GameObject *)0x0) &&
         (cVar2 = (**(code **)(this_01->_padding_ + 0x38))(), cVar2 != '\0')) {
        GameObject::SetSelected(this_01,true);
        plVar1 = &this->selectNum;
        iVar3 = GameObject::GetHandle(this_01);
        this->selectList[*plVar1] = iVar3;
        *plVar1 = *plVar1 + 1;
      }
      iVar4 = iVar4 + 1;
    } while (iVar4 <= MENU_ITEM[param_1].maxSlot);
  }
  return;
}
