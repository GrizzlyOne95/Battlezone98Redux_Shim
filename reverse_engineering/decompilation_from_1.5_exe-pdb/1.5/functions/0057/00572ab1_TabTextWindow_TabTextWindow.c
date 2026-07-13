/*
 * Entry: 00572ab1
 * Name: TabTextWindow::TabTextWindow
 * Namespace: TabTextWindow
 * Signature: TabTextWindow * TabTextWindow(TabTextWindow * this, HWND__ * param_1, char * param_2, int param_3, int param_4, int param_5, int param_6, int param_7)
 * Symbol source: IMPORTED
 * Export status: ok
 */

TabTextWindow * __thiscall
TabTextWindow::TabTextWindow
          (TabTextWindow *this,HWND__ *param_1,char *param_2,int param_3,int param_4,int param_5,
          int param_6,int param_7)

{
  TextWindow::TextWindow((TextWindow *)this,param_1,param_2,param_3,param_4,param_5,param_6,param_7)
  ;
  this->_padding_ = (int)&_vftable_;
  return this;
}
