/*
 * Entry: 0056f3bb
 * Name: ShellButton::~ShellButton
 * Namespace: ShellButton
 * Signature: void ~ShellButton(ShellButton * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall ShellButton::~ShellButton(ShellButton *this)

{
  DeleteObject(this->hLabelFont);
  DeleteObject(this->hButtonOff);
  DeleteObject(this->hButtonOn);
  DeleteObject(this->hButtonClick);
  return;
}
