/*
 * Entry: 00573e4b
 * Name: SetKeyInput
 * Namespace: Global
 * Signature: void SetKeyInput(char * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl SetKeyInput(char *param_1)

{
  void *pvVar1;
  int iVar2;
  
  iVar2 = KeyConfig::set_key(myConfig,currentCommandName,param_1);
  if (iVar2 == 0) {
    if (messageTwo != (void *)0x0) {
      TextLabel::ShowLabelText(messageTwo,1);
    }
  }
  else {
    if (messageOne != (void *)0x0) {
      TextLabel::HideLabelText(messageOne,1);
    }
    if (messageTwo != (void *)0x0) {
      TextLabel::HideLabelText(messageTwo,1);
    }
    pvVar1 = currentBox;
    if (currentBox != (void *)0x0) {
      TextLabel::SetLabelText(currentBox,param_1);
      read_text_label("keyboard",param_1,(char *)((int)pvVar1 + 4));
      TextLabel::DrawLabelText(currentBox,(char *)0x0,0);
      UpdateWindow((HWND)hInputConfig);
    }
    write_input_map_key(currentCommandName,param_1);
    bWaitForKey = 0;
  }
  return;
}
