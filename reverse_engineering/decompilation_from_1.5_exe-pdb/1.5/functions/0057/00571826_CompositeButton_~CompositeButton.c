/*
 * Entry: 00571826
 * Name: CompositeButton::~CompositeButton
 * Namespace: CompositeButton
 * Signature: void ~CompositeButton(CompositeButton * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall CompositeButton::~CompositeButton(CompositeButton *this)

{
  ShellBitmap *pSVar1;
  
  pSVar1 = this->offButton;
  if (pSVar1 != (ShellBitmap *)0x0) {
    ShellBitmap::~ShellBitmap(pSVar1);
    operator_delete(pSVar1);
    this->offButton = (ShellBitmap *)0x0;
  }
  pSVar1 = this->onButton;
  if (pSVar1 != (ShellBitmap *)0x0) {
    ShellBitmap::~ShellBitmap(pSVar1);
    operator_delete(pSVar1);
    this->onButton = (ShellBitmap *)0x0;
  }
  pSVar1 = this->clickButton;
  if (pSVar1 != (ShellBitmap *)0x0) {
    ShellBitmap::~ShellBitmap(pSVar1);
    operator_delete(pSVar1);
    this->clickButton = (ShellBitmap *)0x0;
  }
  return;
}
