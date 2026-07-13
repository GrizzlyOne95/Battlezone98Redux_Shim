/*
 * Entry: 0056fa6a
 * Name: CompositeButton::PaintButton
 * Namespace: CompositeButton
 * Signature: void PaintButton(CompositeButton * this, HDC__ * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall CompositeButton::PaintButton(CompositeButton *this,HDC__ *param_1)

{
  int iVar1;
  ShellBitmap *this_00;
  
  iVar1 = this->nButtonMode;
  if (iVar1 == 0) {
    this_00 = this->offButton;
  }
  else if (iVar1 == 1) {
    this_00 = this->onButton;
  }
  else {
    if (iVar1 != 2) {
      return;
    }
    this_00 = this->clickButton;
  }
  ShellBitmap::PaintBitmap(this_00,param_1);
  return;
}
