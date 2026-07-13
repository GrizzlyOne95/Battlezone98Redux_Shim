/*
 * Entry: 004c48bc
 * Name: ControlPanel::SetCommand
 * Namespace: ControlPanel
 * Signature: void SetCommand(ControlPanel * this, AiCommand param_1, GameObject * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall ControlPanel::SetCommand(ControlPanel *this,AiCommand param_1,GameObject *param_2)

{
  int iVar1;
  VECTOR_3D *pVVar2;
  
  iVar1 = UserPref_arcadeMode();
  if (iVar1 != 0) {
    param_1 = CMD_SELECT;
  }
  FillCmdButton(this,&this->cmdButton,param_1,param_2);
  if (param_2 == (GameObject *)0x0) {
    (this->cmdButton).pos = (VECTOR_3D *)0x0;
  }
  else {
    pVVar2 = (VECTOR_3D *)(**(code **)(param_2->_padding_ + 0xc))();
    (this->cmdButton).pos = pVVar2;
  }
  return;
}
