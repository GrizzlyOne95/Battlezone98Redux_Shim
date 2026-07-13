/*
 * Entry: 005523ae
 * Name: PhoneNumberList::PhoneNumberList
 * Namespace: PhoneNumberList
 * Signature: PhoneNumberList * PhoneNumberList(PhoneNumberList * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

PhoneNumberList * __thiscall PhoneNumberList::PhoneNumberList(PhoneNumberList *this)

{
  this->hwnd = (HWND__ *)0x0;
  this->count = 0;
  this->name = (char **)0x0;
  this->number = (char **)0x0;
  this->edit = false;
  return this;
}
