/*
 * Entry: 0056f953
 * Name: CompositeButton::CompositeButton
 * Namespace: CompositeButton
 * Signature: CompositeButton * CompositeButton(CompositeButton * this, HWND__ * param_1, char * param_2, char * param_3, char * param_4, int param_5, int param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

CompositeButton * __thiscall
CompositeButton::CompositeButton
          (CompositeButton *this,HWND__ *param_1,char *param_2,char *param_3,char *param_4,
          int param_5,int param_6)

{
  ShellBitmap *pSVar1;
  
  this->nButtonMode = 0;
  this->hParentHwnd = param_1;
  pSVar1 = operator_new(0x20);
  if (pSVar1 == (ShellBitmap *)0x0) {
    pSVar1 = (ShellBitmap *)0x0;
  }
  else {
    pSVar1 = ShellBitmap::ShellBitmap(pSVar1,param_2,param_5,param_6);
  }
  this->offButton = pSVar1;
  pSVar1 = operator_new(0x20);
  if (pSVar1 == (ShellBitmap *)0x0) {
    pSVar1 = (ShellBitmap *)0x0;
  }
  else {
    pSVar1 = ShellBitmap::ShellBitmap(pSVar1,param_3,param_5,param_6);
  }
  this->onButton = pSVar1;
  pSVar1 = operator_new(0x20);
  if (pSVar1 == (ShellBitmap *)0x0) {
    pSVar1 = (ShellBitmap *)0x0;
  }
  else {
    pSVar1 = ShellBitmap::ShellBitmap(pSVar1,param_4,param_5,param_6);
  }
  this->clickButton = pSVar1;
  pSVar1 = this->offButton;
  (this->buttonRect).left = (pSVar1->bmRect).left;
  (this->buttonRect).top = (pSVar1->bmRect).top;
  (this->buttonRect).right = (pSVar1->bmRect).right;
  (this->buttonRect).bottom = (pSVar1->bmRect).bottom;
  return this;
}
