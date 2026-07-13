/*
 * Entry: 004c4549
 * Name: ControlPanel::SelectAdd
 * Namespace: ControlPanel
 * Signature: void SelectAdd(ControlPanel * this, GameObject * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall ControlPanel::SelectAdd(ControlPanel *this,GameObject *param_1)

{
  long *plVar1;
  char cVar2;
  int iVar3;
  
  if (param_1 != (GameObject *)0x0) {
    cVar2 = (**(code **)(param_1->_padding_ + 0x38))();
    if (cVar2 != '\0') {
      GameObject::SetSelected(param_1,true);
      plVar1 = &this->selectNum;
      iVar3 = GameObject::GetHandle(param_1);
      this->selectList[*plVar1] = iVar3;
      *plVar1 = *plVar1 + 1;
    }
  }
  return;
}
