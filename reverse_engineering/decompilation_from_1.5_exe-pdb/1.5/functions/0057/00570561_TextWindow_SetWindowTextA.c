/*
 * Entry: 00570561
 * Name: TextWindow::SetWindowTextA
 * Namespace: TextWindow
 * Signature: int SetWindowTextA(TextWindow * this, char * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __thiscall TextWindow::SetWindowTextA(TextWindow *this,char *param_1)

{
  char cVar1;
  int iVar2;
  
  iVar2 = 8 - (int)param_1;
  do {
    cVar1 = *param_1;
    param_1[(int)this + iVar2] = cVar1;
    param_1 = param_1 + 1;
  } while (cVar1 != '\0');
  return 1;
}
