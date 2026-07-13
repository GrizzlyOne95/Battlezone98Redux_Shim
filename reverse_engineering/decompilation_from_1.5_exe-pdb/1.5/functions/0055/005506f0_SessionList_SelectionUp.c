/*
 * Entry: 005506f0
 * Name: SessionList::SelectionUp
 * Namespace: SessionList
 * Signature: void SelectionUp(SessionList * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall SessionList::SelectionUp(SessionList *this)

{
  LRESULT LVar1;
  
  LVar1 = SendMessageA((HWND)this->hList,0x18e,0,0);
  if (0 < LVar1) {
    SendMessageA((HWND)this->hList,0x197,LVar1 - 1,0);
  }
  return;
}
