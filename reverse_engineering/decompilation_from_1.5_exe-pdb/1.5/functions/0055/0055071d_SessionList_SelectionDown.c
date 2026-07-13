/*
 * Entry: 0055071d
 * Name: SessionList::SelectionDown
 * Namespace: SessionList
 * Signature: void SelectionDown(SessionList * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall SessionList::SelectionDown(SessionList *this)

{
  LRESULT LVar1;
  
  LVar1 = SendMessageA((HWND)this->hList,0x18e,0,0);
  SendMessageA((HWND)this->hList,0x197,LVar1 + 1,0);
  return;
}
