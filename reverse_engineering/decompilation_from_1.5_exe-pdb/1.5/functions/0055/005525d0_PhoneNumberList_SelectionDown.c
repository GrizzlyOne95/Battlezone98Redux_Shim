/*
 * Entry: 005525d0
 * Name: PhoneNumberList::SelectionDown
 * Namespace: PhoneNumberList
 * Signature: void SelectionDown(PhoneNumberList * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall PhoneNumberList::SelectionDown(PhoneNumberList *this)

{
  LRESULT LVar1;
  
  LVar1 = SendMessageA((HWND)this->hwnd,0x18e,0,0);
  SendMessageA((HWND)this->hwnd,0x197,LVar1 + 1,0);
  InvalidateRect((HWND)this->hwnd,(RECT *)0x0,1);
  return;
}
