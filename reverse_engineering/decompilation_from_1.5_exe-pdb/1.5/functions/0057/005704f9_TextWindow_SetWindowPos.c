/*
 * Entry: 005704f9
 * Name: TextWindow::SetWindowPos
 * Namespace: TextWindow
 * Signature: int SetWindowPos(TextWindow * this, int param_1, int param_2, int param_3, int param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __thiscall
TextWindow::SetWindowPos(TextWindow *this,int param_1,int param_2,int param_3,int param_4)

{
  long *plVar1;
  int iVar2;
  int iVar3;
  
  iVar2 = (this->twRect).left;
  plVar1 = &(this->twRect).top;
  iVar3 = *plVar1;
  (this->twRect).left = param_1;
  *plVar1 = param_2;
  if (param_3 == 0) {
    (this->twRect).right = ((this->twRect).right - iVar2) + param_1;
  }
  else {
    (this->twRect).right = param_1 + param_3;
  }
  if (param_4 == 0) {
    (this->twRect).bottom = ((this->twRect).bottom - iVar3) + param_2;
  }
  else {
    (this->twRect).bottom = param_2 + param_4;
  }
  return 1;
}
