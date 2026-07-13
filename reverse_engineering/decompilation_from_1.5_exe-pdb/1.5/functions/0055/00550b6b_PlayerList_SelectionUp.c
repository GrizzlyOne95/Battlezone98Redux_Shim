/*
 * Entry: 00550b6b
 * Name: PlayerList::SelectionUp
 * Namespace: PlayerList
 * Signature: void SelectionUp(PlayerList * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall PlayerList::SelectionUp(PlayerList *this)

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
