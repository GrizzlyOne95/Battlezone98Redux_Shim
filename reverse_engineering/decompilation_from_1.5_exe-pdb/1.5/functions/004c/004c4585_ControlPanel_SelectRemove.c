/*
 * Entry: 004c4585
 * Name: ControlPanel::SelectRemove
 * Namespace: ControlPanel
 * Signature: void SelectRemove(ControlPanel * this, GameObject * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall ControlPanel::SelectRemove(ControlPanel *this,GameObject *param_1)

{
  GameObject *pGVar1;
  int *piVar2;
  int *piVar3;
  int local_c;
  int local_8;
  
  if (param_1 != (GameObject *)0x0) {
    local_c = 0;
    local_8 = 0;
    if (0 < this->selectNum) {
      piVar2 = this->selectList;
      piVar3 = piVar2;
      do {
        pGVar1 = GameObject::GetObj(*piVar3);
        if (pGVar1 == param_1) {
          GameObject::SetSelected(param_1,false);
          this->currentItem = -1;
          this->itemSelected = 0;
        }
        else {
          local_c = local_c + 1;
          *piVar2 = *piVar3;
          piVar2 = piVar2 + 1;
        }
        local_8 = local_8 + 1;
        piVar3 = piVar3 + 1;
      } while (local_8 < this->selectNum);
    }
    this->selectNum = local_c;
  }
  return;
}
