/*
 * Entry: 00551f77
 * Name: MapList::SelectionUp
 * Namespace: MapList
 * Signature: void SelectionUp(MapList * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall MapList::SelectionUp(MapList *this)

{
  LRESULT LVar1;
  
  LVar1 = SendMessageA((HWND)this->hwnd,0x18e,0,0);
  if (0 < LVar1) {
    SendMessageA((HWND)this->hwnd,0x197,LVar1 - 1,0);
  }
  return;
}
