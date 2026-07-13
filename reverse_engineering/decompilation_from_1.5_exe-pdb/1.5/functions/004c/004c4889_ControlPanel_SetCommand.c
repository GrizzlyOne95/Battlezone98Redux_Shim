/*
 * Entry: 004c4889
 * Name: ControlPanel::SetCommand
 * Namespace: ControlPanel
 * Signature: void SetCommand(ControlPanel * this, AiCommand param_1, VECTOR_3D * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall ControlPanel::SetCommand(ControlPanel *this,AiCommand param_1,VECTOR_3D *param_2)

{
  int iVar1;
  
  iVar1 = UserPref_arcadeMode();
  if (iVar1 != 0) {
    param_1 = CMD_NONE;
  }
  FillCmdButton(this,&this->cmdButton,param_1,(GameObject *)0x0);
  (this->cmdButton).pos = param_2;
  return;
}
