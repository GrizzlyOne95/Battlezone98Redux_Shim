/*
 * Entry: 00573e16
 * Name: PromptKeyInput
 * Namespace: Global
 * Signature: void PromptKeyInput(TextLabel * * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl PromptKeyInput(TextLabel **param_1)

{
  currentBox = *param_1;
  TextLabel::SetLabelText(currentBox,"_");
  TextLabel::DrawLabelText(*param_1,(char *)0x0,0);
  if (messageOne != (void *)0x0) {
    TextLabel::ShowLabelText(messageOne,1);
  }
  return;
}
