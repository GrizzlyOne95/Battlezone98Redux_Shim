/*
 * Entry: 005524f5
 * Name: PhoneNumberList::Delete
 * Namespace: PhoneNumberList
 * Signature: void Delete(PhoneNumberList * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall PhoneNumberList::Delete(PhoneNumberList *this)

{
  WPARAM wParam;
  LRESULT LVar1;
  
  wParam = SendMessageA((HWND)this->hwnd,0x188,0,0);
  if (wParam != 0xffffffff) {
    LVar1 = SendMessageA((HWND)this->hwnd,0x199,wParam,0);
    if (LVar1 != -1) {
      Delete(this,LVar1);
      SendMessageA((HWND)this->hwnd,0x182,wParam,0);
    }
  }
  SendMessageA((HWND)this->hwnd,0x186,0,0);
  InvalidateRect((HWND)this->hwnd,(RECT *)0x0,1);
  return;
}
