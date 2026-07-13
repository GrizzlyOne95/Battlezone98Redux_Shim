/*
 * Entry: 00551046
 * Name: PlayerNameList::SelectionUp
 * Namespace: PlayerNameList
 * Signature: void SelectionUp(PlayerNameList * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall PlayerNameList::SelectionUp(PlayerNameList *this)

{
  LRESULT LVar1;
  
  LVar1 = SendMessageA((HWND)this->hwnd,0x18e,0,0);
  if (0 < LVar1) {
    SendMessageA((HWND)this->hwnd,0x197,LVar1 - 1,0);
  }
  return;
}
