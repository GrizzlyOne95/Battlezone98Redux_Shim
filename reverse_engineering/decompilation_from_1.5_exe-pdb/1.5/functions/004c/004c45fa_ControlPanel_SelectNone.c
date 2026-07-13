/*
 * Entry: 004c45fa
 * Name: ControlPanel::SelectNone
 * Namespace: ControlPanel
 * Signature: void SelectNone(ControlPanel * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall ControlPanel::SelectNone(ControlPanel *this)

{
  GameObject *this_00;
  int iVar1;
  int *piVar2;
  
  iVar1 = 0;
  if (0 < this->selectNum) {
    piVar2 = this->selectList;
    do {
      this_00 = GameObject::GetObj(*piVar2);
      GameObject::SetSelected(this_00,false);
      iVar1 = iVar1 + 1;
      piVar2 = piVar2 + 1;
    } while (iVar1 < this->selectNum);
  }
  this->selectNum = 0;
  this->currentItem = -1;
  this->itemSelected = 0;
  return;
}
