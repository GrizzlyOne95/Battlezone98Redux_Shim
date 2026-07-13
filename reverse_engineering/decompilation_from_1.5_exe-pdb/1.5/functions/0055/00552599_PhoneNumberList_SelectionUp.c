/*
 * Entry: 00552599
 * Name: PhoneNumberList::SelectionUp
 * Namespace: PhoneNumberList
 * Signature: void SelectionUp(PhoneNumberList * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall PhoneNumberList::SelectionUp(PhoneNumberList *this)

{
  LRESULT LVar1;
  
  LVar1 = SendMessageA((HWND)this->hwnd,0x18e,0,0);
  if (0 < LVar1) {
    SendMessageA((HWND)this->hwnd,0x197,LVar1 - 1,0);
    InvalidateRect((HWND)this->hwnd,(RECT *)0x0,1);
  }
  return;
}
