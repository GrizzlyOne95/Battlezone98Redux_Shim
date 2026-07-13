/*
 * Entry: 005708bc
 * Name: TabTextWindow::DrawWindowText
 * Namespace: TabTextWindow
 * Signature: int DrawWindowText(TabTextWindow * this, int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __thiscall TabTextWindow::DrawWindowText(TabTextWindow *this,int param_1)

{
  int iVar1;
  HDC hDC;
  
  if (hCurrentBackground == (HBITMAP__ *)0x0) {
    iVar1 = 0;
  }
  else {
    hDC = GetDC((HWND)this->_padding_);
    iVar1 = (**(code **)this->_padding_)(hDC,param_1);
    ReleaseDC((HWND)this->_padding_,hDC);
  }
  return iVar1;
}
