/*
 * Entry: 00552553
 * Name: PhoneNumberList::GetNumber
 * Namespace: PhoneNumberList
 * Signature: char * GetNumber(PhoneNumberList * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

char * __thiscall PhoneNumberList::GetNumber(PhoneNumberList *this)

{
  WPARAM wParam;
  LRESULT LVar1;
  
  wParam = SendMessageA((HWND)this->hwnd,0x188,0,0);
  if ((((wParam != 0xffffffff) &&
       (LVar1 = SendMessageA((HWND)this->hwnd,0x199,wParam,0), LVar1 != -1)) && (-1 < LVar1)) &&
     (LVar1 < this->count)) {
    return this->number[LVar1];
  }
  return "";
}
