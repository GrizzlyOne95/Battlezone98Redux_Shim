/*
 * Entry: 0057295a
 * Name: TextLabel::ShowLabelText
 * Namespace: TextLabel
 * Signature: int ShowLabelText(TextLabel * this, int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __thiscall TextLabel::ShowLabelText(TextLabel *this,int param_1)

{
  int iVar1;
  
  if (this->nTextVisible == 0) {
    this->nTextVisible = 1;
    if (param_1 != 0) {
      DrawLabelText(this,(char *)0x0,0);
    }
    iVar1 = 1;
  }
  else {
    iVar1 = 0;
  }
  return iVar1;
}
