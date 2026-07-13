/*
 * Entry: 00551071
 * Name: PlayerNameList::SelectionDown
 * Namespace: PlayerNameList
 * Signature: void SelectionDown(PlayerNameList * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall PlayerNameList::SelectionDown(PlayerNameList *this)

{
  LRESULT LVar1;
  
  LVar1 = SendMessageA((HWND)this->hwnd,0x18e,0,0);
  SendMessageA((HWND)this->hwnd,0x197,LVar1 + 1,0);
  return;
}
