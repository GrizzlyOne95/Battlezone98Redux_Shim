/*
 * Entry: 005523ce
 * Name: PhoneNumberList::Init
 * Namespace: PhoneNumberList
 * Signature: void Init(PhoneNumberList * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall PhoneNumberList::Init(PhoneNumberList *this)

{
  int iVar1;
  
  if ((HWND)this->hwnd != (HWND)0x0) {
    SendMessageA((HWND)this->hwnd,0x184,0,0);
  }
  if (this->count != 0) {
    iVar1 = 0;
    if (0 < this->count) {
      do {
        free(this->name[iVar1]);
        free(this->number[iVar1]);
        iVar1 = iVar1 + 1;
      } while (iVar1 < this->count);
    }
    free(this->name);
    free(this->number);
    this->name = (char **)0x0;
    this->number = (char **)0x0;
  }
  this->count = 0;
  if ((HWND)this->hwnd != (HWND)0x0) {
    InvalidateRect((HWND)this->hwnd,(RECT *)0x0,1);
  }
  return;
}
