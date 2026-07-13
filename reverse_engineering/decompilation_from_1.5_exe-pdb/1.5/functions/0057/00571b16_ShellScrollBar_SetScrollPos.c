/*
 * Entry: 00571b16
 * Name: ShellScrollBar::SetScrollPos
 * Namespace: ShellScrollBar
 * Signature: int SetScrollPos(ShellScrollBar * this, int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __thiscall ShellScrollBar::SetScrollPos(ShellScrollBar *this,int param_1)

{
  HDC hDC;
  int iVar1;
  
  hDC = GetDC((HWND)this->hParentHwnd);
  iVar1 = SetScrollPos(this,(HDC__ *)hDC,param_1);
  ReleaseDC((HWND)this->hParentHwnd,hDC);
  return iVar1;
}
