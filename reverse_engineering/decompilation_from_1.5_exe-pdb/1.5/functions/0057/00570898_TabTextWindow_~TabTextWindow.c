/*
 * Entry: 00570898
 * Name: TabTextWindow::~TabTextWindow
 * Namespace: TabTextWindow
 * Signature: void ~TabTextWindow(TabTextWindow * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall TabTextWindow::~TabTextWindow(TabTextWindow *this)

{
  this->_padding_ = (int)&_vftable_;
  DeleteObject((HGDIOBJ)this->_padding_);
  this->_padding_ = 0;
  TextWindow::~TextWindow((TextWindow *)this);
  return;
}
