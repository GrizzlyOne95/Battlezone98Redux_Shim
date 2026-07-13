/*
 * Entry: 004c3cd3
 * Name: ControlPanel::BroadcastCommand
 * Namespace: ControlPanel
 * Signature: void BroadcastCommand(ControlPanel * this, AiCommand param_1, GameObject * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
ControlPanel::BroadcastCommand(ControlPanel *this,AiCommand param_1,GameObject *param_2)

{
  char cVar1;
  GameObject *this_00;
  int *piVar2;
  int local_8;
  
  local_8 = 0;
  if (0 < this->selectNum) {
    piVar2 = this->selectList;
    do {
      this_00 = GameObject::GetObj(*piVar2);
      cVar1 = (**(code **)(this_00->_padding_ + 0x38))();
      if (cVar1 != '\0') {
        GameObject::SetCommand(this_00,param_1,param_2);
      }
      local_8 = local_8 + 1;
      piVar2 = piVar2 + 1;
    } while (local_8 < this->selectNum);
  }
  return;
}
