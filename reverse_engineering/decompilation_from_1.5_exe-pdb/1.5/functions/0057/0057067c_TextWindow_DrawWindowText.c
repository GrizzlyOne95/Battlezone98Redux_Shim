/*
 * Entry: 0057067c
 * Name: TextWindow::DrawWindowText
 * Namespace: TextWindow
 * Signature: int DrawWindowText(TextWindow * this, int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __thiscall TextWindow::DrawWindowText(TextWindow *this,int param_1)

{
  HDC hDC;
  int iVar1;
  
  hDC = GetDC((HWND)this->hParentHwnd);
  iVar1 = (**(code **)this->_padding_)(hDC,param_1);
  ReleaseDC((HWND)this->hParentHwnd,hDC);
  return iVar1;
}
