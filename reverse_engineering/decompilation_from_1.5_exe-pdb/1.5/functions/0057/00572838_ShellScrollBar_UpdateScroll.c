/*
 * Entry: 00572838
 * Name: ShellScrollBar::UpdateScroll
 * Namespace: ShellScrollBar
 * Signature: int UpdateScroll(ShellScrollBar * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __thiscall ShellScrollBar::UpdateScroll(ShellScrollBar *this)

{
  int iVar1;
  
  iVar1 = SetScrollPos(this,this->nCurrentPos);
  return iVar1;
}
