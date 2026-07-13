/*
 * Entry: 00572983
 * Name: TextLabel::SetLabelTextColor
 * Namespace: TextLabel
 * Signature: int SetLabelTextColor(TextLabel * this, ulong param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __thiscall TextLabel::SetLabelTextColor(TextLabel *this,ulong param_1,int param_2)

{
  this->textColor = param_1;
  if (param_2 != 0) {
    DrawLabelText(this,(char *)0x0,0);
  }
  return 1;
}
