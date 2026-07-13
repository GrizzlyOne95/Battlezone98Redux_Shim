/*
 * Entry: 00570107
 * Name: ShellScrollBar::~ShellScrollBar
 * Namespace: ShellScrollBar
 * Signature: void ~ShellScrollBar(ShellScrollBar * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall ShellScrollBar::~ShellScrollBar(ShellScrollBar *this)

{
  DeleteObject(this->hBitmap);
  DeleteObject(this->hScrollBitmap);
  this->hBitmap = (HBITMAP__ *)0x0;
  this->hScrollBitmap = (HBITMAP__ *)0x0;
  return;
}
