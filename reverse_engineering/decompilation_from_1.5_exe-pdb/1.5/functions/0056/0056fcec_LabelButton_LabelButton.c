/*
 * Entry: 0056fcec
 * Name: LabelButton::LabelButton
 * Namespace: LabelButton
 * Signature: LabelButton * LabelButton(LabelButton * this, HWND__ * param_1, int param_2, int param_3, int param_4, int param_5, int param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

LabelButton * __thiscall
LabelButton::LabelButton
          (LabelButton *this,HWND__ *param_1,int param_2,int param_3,int param_4,int param_5,
          int param_6)

{
  HWND hWnd;
  
  this->hParentHwnd = param_1;
  hWnd = GetDlgItem((HWND)param_1,param_2);
  this->nButtonMode = 0;
  this->nHideFlag = 0;
  (this->buttonRect).right = param_3 + param_5;
  this->hButtonHwnd = (HWND__ *)hWnd;
  (this->buttonRect).left = param_3;
  (this->buttonRect).top = param_4;
  (this->buttonRect).bottom = param_6 + param_4;
  MoveWindow(hWnd,param_3,param_4,param_5,param_6,1);
  return this;
}
