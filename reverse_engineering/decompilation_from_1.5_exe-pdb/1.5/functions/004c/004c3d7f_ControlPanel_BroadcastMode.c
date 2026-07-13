/*
 * Entry: 004c3d7f
 * Name: ControlPanel::BroadcastMode
 * Namespace: ControlPanel
 * Signature: bool BroadcastMode(ControlPanel * this, int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall ControlPanel::BroadcastMode(ControlPanel *this,int param_1)

{
  char cVar1;
  GameObject *pGVar2;
  int *piVar3;
  bool bVar4;
  int local_c;
  bool local_5;
  
  local_c = 0;
  local_5 = true;
  if (0 < this->selectNum) {
    piVar3 = this->selectList;
    do {
      pGVar2 = GameObject::GetObj(*piVar3);
      cVar1 = (**(code **)(pGVar2->_padding_ + 0x38))();
      if ((cVar1 != '\0') &&
         ((cVar1 = (**(code **)(pGVar2->_padding_ + 0x2c))(param_1), cVar1 == '\0' ||
          (bVar4 = local_5 == false, local_5 = true, bVar4)))) {
        local_5 = false;
      }
      local_c = local_c + 1;
      piVar3 = piVar3 + 1;
    } while (local_c < this->selectNum);
  }
  return local_5;
}
