/*
 * Entry: 00555da3
 * Name: ServerList::SelectionUp
 * Namespace: ServerList
 * Signature: void SelectionUp(ServerList * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall ServerList::SelectionUp(ServerList *this)

{
  LRESULT LVar1;
  
  LVar1 = SendMessageA((HWND)this->hList,0x18e,0,0);
  if (0 < LVar1) {
    SendMessageA((HWND)this->hList,0x197,LVar1 - 1,0);
    Redraw(this);
    return;
  }
  return;
}
