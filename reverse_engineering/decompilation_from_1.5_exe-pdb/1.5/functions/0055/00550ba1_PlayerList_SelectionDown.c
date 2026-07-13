/*
 * Entry: 00550ba1
 * Name: PlayerList::SelectionDown
 * Namespace: PlayerList
 * Signature: void SelectionDown(PlayerList * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall PlayerList::SelectionDown(PlayerList *this)

{
  LRESULT LVar1;
  
  LVar1 = SendMessageA((HWND)this->hList,0x18e,0,0);
  SendMessageA((HWND)this->hList,0x197,LVar1 + 1,0);
  Redraw(this);
  return;
}
