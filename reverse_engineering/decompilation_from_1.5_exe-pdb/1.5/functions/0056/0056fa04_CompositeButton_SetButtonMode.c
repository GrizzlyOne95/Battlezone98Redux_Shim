/*
 * Entry: 0056fa04
 * Name: CompositeButton::SetButtonMode
 * Namespace: CompositeButton
 * Signature: int SetButtonMode(CompositeButton * this, int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __thiscall CompositeButton::SetButtonMode(CompositeButton *this,int param_1)

{
  if (param_1 == 0) {
    if (this->nButtonMode != 0) {
      InvalidateRect((HWND)this->hParentHwnd,(RECT *)&this->buttonRect,0);
      this->nButtonMode = 0;
    }
  }
  else if (param_1 == 1) {
    if (this->nButtonMode != 1) {
      InvalidateRect((HWND)this->hParentHwnd,(RECT *)&this->buttonRect,0);
      this->nButtonMode = 1;
    }
  }
  else if ((param_1 == 2) && (this->nButtonMode != 2)) {
    InvalidateRect((HWND)this->hParentHwnd,(RECT *)&this->buttonRect,0);
    this->nButtonMode = 2;
  }
  return 1;
}
