/*
 * Entry: 00571b07
 * Name: ShellScrollBar::UpdateScroll
 * Namespace: ShellScrollBar
 * Signature: int UpdateScroll(ShellScrollBar * this, HDC__ * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __thiscall ShellScrollBar::UpdateScroll(ShellScrollBar *this,HDC__ *param_1)

{
  int iVar1;
  
  iVar1 = SetScrollPos(this,param_1,this->nCurrentPos);
  return iVar1;
}
