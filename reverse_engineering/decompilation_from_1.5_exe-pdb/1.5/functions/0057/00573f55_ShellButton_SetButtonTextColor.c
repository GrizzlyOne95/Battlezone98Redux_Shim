/*
 * Entry: 00573f55
 * Name: ShellButton::SetButtonTextColor
 * Namespace: ShellButton
 * Signature: int SetButtonTextColor(ShellButton * this, ulong param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __thiscall ShellButton::SetButtonTextColor(ShellButton *this,ulong param_1,int param_2)

{
  this->textColor = param_1;
  if (param_2 != 0) {
    UpdateButton(this);
  }
  return 1;
}
