/*
 * Entry: 00550789
 * Name: SessionList::FindItemIndex
 * Namespace: SessionList
 * Signature: long FindItemIndex(SessionList * this, short param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

long __thiscall SessionList::FindItemIndex(SessionList *this,short param_1)

{
  LRESULT LVar1;
  LRESULT LVar2;
  WPARAM wParam;
  
  wParam = 0;
  LVar1 = SendMessageA((HWND)this->hList,0x18b,0,0);
  this->l = LVar1;
  if ((LVar1 != -1) && (0 < LVar1)) {
    do {
      LVar2 = SendMessageA((HWND)this->hList,0x199,wParam,0);
      this->l = LVar2;
      if (param_1 == LVar2) {
        return wParam;
      }
      wParam = wParam + 1;
    } while ((int)wParam < LVar1);
  }
  return -1;
}
