/*
 * Entry: 005722e9
 * Name: ShellButton::UpdateButton
 * Namespace: ShellButton
 * Signature: int UpdateButton(ShellButton * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __thiscall ShellButton::UpdateButton(ShellButton *this)

{
  BOOL BVar1;
  HDC hDC;
  int iVar2;
  
  BVar1 = IsWindow((HWND)this->hParentHwnd);
  if (BVar1 == 0) {
    return 0;
  }
  hDC = GetDC((HWND)this->hParentHwnd);
  iVar2 = UpdateButton(this,(HDC__ *)hDC);
  ReleaseDC((HWND)this->hParentHwnd,hDC);
  return iVar2;
}
