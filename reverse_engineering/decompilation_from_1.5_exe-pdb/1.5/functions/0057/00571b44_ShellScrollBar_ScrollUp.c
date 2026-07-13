/*
 * Entry: 00571b44
 * Name: ShellScrollBar::ScrollUp
 * Namespace: ShellScrollBar
 * Signature: int ScrollUp(ShellScrollBar * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __thiscall ShellScrollBar::ScrollUp(ShellScrollBar *this)

{
  SetScrollPos(this,this->nCurrentPos + 1);
  return 1;
}
