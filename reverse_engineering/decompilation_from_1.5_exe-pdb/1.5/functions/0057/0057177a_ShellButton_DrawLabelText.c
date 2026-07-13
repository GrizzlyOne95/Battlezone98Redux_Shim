/*
 * Entry: 0057177a
 * Name: ShellButton::DrawLabelText
 * Namespace: ShellButton
 * Signature: int DrawLabelText(ShellButton * this, char * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __thiscall ShellButton::DrawLabelText(ShellButton *this,char *param_1)

{
  BOOL BVar1;
  HDC hDC;
  int iVar2;
  
  BVar1 = IsWindow((HWND)this->hParentHwnd);
  iVar2 = 0;
  if (BVar1 != 0) {
    hDC = GetDC((HWND)this->hParentHwnd);
    iVar2 = DrawLabelText(this,(HDC__ *)hDC,param_1);
    ReleaseDC((HWND)this->hParentHwnd,hDC);
  }
  return iVar2;
}
