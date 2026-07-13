/*
 * Entry: 004c475e
 * Name: ControlPanel::FillCmdButton
 * Namespace: ControlPanel
 * Signature: void FillCmdButton(ControlPanel * this, CmdButton * param_1, AiCommand param_2, GameObject * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
ControlPanel::FillCmdButton
          (ControlPanel *this,CmdButton *param_1,AiCommand param_2,GameObject *param_3)

{
  long lVar1;
  
  param_1->command = param_2;
  param_1->object = param_3;
  lVar1 = DisplayInterface::colorGrey;
  if (param_2 != CMD_NONE) {
    if (param_3 == (GameObject *)0x0) {
      lVar1 = DisplayInterface::colorGreen;
      if (param_2 != CMD_GO) {
        lVar1 = DisplayInterface::colorWhite;
      }
    }
    else {
      lVar1 = GameObject::GetColor(param_3);
    }
  }
  param_1->color = lVar1;
  return;
}
