/*
 * Entry: 00551fa4
 * Name: MapList::SelectionDown
 * Namespace: MapList
 * Signature: void SelectionDown(MapList * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall MapList::SelectionDown(MapList *this)

{
  LRESULT LVar1;
  
  LVar1 = SendMessageA((HWND)this->hwnd,0x18e,0,0);
  SendMessageA((HWND)this->hwnd,0x197,LVar1 + 1,0);
  return;
}
