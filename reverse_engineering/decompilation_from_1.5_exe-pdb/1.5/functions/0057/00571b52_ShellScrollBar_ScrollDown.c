/*
 * Entry: 00571b52
 * Name: ShellScrollBar::ScrollDown
 * Namespace: ShellScrollBar
 * Signature: int ScrollDown(ShellScrollBar * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __thiscall ShellScrollBar::ScrollDown(ShellScrollBar *this)

{
  SetScrollPos(this,this->nCurrentPos + -1);
  return 1;
}
