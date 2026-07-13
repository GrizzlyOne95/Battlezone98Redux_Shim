/*
 * Entry: 005523c1
 * Name: PhoneNumberList::Redraw
 * Namespace: PhoneNumberList
 * Signature: void Redraw(PhoneNumberList * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall PhoneNumberList::Redraw(PhoneNumberList *this)

{
  InvalidateRect((HWND)this->hwnd,(RECT *)0x0,1);
  return;
}
