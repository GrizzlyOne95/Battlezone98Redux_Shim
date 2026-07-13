/*
 * Entry: 00555dd9
 * Name: ServerList::SelectionDown
 * Namespace: ServerList
 * Signature: void SelectionDown(ServerList * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall ServerList::SelectionDown(ServerList *this)

{
  LRESULT LVar1;
  
  LVar1 = SendMessageA((HWND)this->hList,0x18e,0,0);
  SendMessageA((HWND)this->hList,0x197,LVar1 + 1,0);
  Redraw(this);
  return;
}
