/*
 * Entry: 005507e6
 * Name: SessionList::DeleteListItem
 * Namespace: SessionList
 * Signature: void DeleteListItem(SessionList * this, short param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall SessionList::DeleteListItem(SessionList *this,short param_1)

{
  WPARAM wParam;
  LRESULT LVar1;
  
  wParam = FindItemIndex(this,param_1);
  if (wParam != 0xffffffff) {
    LVar1 = SendMessageA((HWND)this->hList,0x182,wParam,0);
    this->l = LVar1;
  }
  return;
}
