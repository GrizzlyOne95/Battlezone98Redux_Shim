/*
 * Entry: 0057024b
 * Name: ShellScrollBar::SetScrollRange
 * Namespace: ShellScrollBar
 * Signature: int SetScrollRange(ShellScrollBar * this, int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __thiscall ShellScrollBar::SetScrollRange(ShellScrollBar *this,int param_1)

{
  this->nRange = param_1;
  this->nSectionSize = this->nLength / param_1;
  return 1;
}
