/*
 * Entry: 00570499
 * Name: TextWindow::~TextWindow
 * Namespace: TextWindow
 * Signature: void ~TextWindow(TextWindow * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall TextWindow::~TextWindow(TextWindow *this)

{
  this->_padding_ = (int)&_vftable_;
  DeleteObject(this->hTextFont);
  DeleteObject(this->hTextBack);
  this->hTextBack = (HBITMAP__ *)0x0;
  return;
}
