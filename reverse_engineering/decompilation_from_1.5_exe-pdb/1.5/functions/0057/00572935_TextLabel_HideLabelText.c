/*
 * Entry: 00572935
 * Name: TextLabel::HideLabelText
 * Namespace: TextLabel
 * Signature: int HideLabelText(TextLabel * this, int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __thiscall TextLabel::HideLabelText(TextLabel *this,int param_1)

{
  int iVar1;
  
  if (this->nTextVisible == 0) {
    iVar1 = 0;
  }
  else {
    this->nTextVisible = 0;
    if (param_1 != 0) {
      DrawLabelText(this,(char *)0x0,0);
    }
    iVar1 = 1;
  }
  return iVar1;
}
