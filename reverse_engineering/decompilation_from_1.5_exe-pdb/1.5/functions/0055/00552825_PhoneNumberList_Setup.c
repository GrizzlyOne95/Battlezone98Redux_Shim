/*
 * Entry: 00552825
 * Name: PhoneNumberList::Setup
 * Namespace: PhoneNumberList
 * Signature: void Setup(PhoneNumberList * this, HWND__ * param_1, HWND__ * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall PhoneNumberList::Setup(PhoneNumberList *this,HWND__ *param_1,HWND__ *param_2)

{
  WPARAM wParam;
  LRESULT LVar1;
  
  if (this->edit == false) {
    SetWindowTextA((HWND)param_1,"");
    SetWindowTextA((HWND)param_2,"");
  }
  else {
    wParam = SendMessageA((HWND)this->hwnd,0x188,0,0);
    if (wParam != 0xffffffff) {
      LVar1 = SendMessageA((HWND)this->hwnd,0x199,wParam,0);
      if (LVar1 != -1) {
        SetWindowTextA((HWND)param_1,this->name[LVar1]);
        SetWindowTextA((HWND)param_2,this->number[LVar1]);
      }
    }
  }
  return;
}
