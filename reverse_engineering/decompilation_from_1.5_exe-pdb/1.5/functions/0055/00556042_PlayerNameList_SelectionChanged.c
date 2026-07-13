/*
 * Entry: 00556042
 * Name: PlayerNameList::SelectionChanged
 * Namespace: PlayerNameList
 * Signature: void SelectionChanged(PlayerNameList * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall PlayerNameList::SelectionChanged(PlayerNameList *this)

{
  WPARAM wParam;
  LRESULT LVar1;
  
  wParam = SendMessageA((HWND)this->hwnd,0x188,0,0);
  if (wParam != 0xffffffff) {
    LVar1 = SendMessageA((HWND)this->hwnd,0x199,wParam,0);
    if (((LVar1 != -1) && (-1 < LVar1)) && (LVar1 < this->count)) {
      SetWindowTextA((HWND)this->hwndMail,this->email[LVar1]);
      SetWindowTextA((HWND)this->hwndURL,this->url[LVar1]);
      SetWindowTextA((HWND)this->hwndDescription,this->description[LVar1]);
      if (this->flagList != (FlagList *)0x0) {
        FlagList::SetSelection(this->flagList,this->flag[LVar1]);
      }
    }
  }
  InvalidateRect((HWND)this->hwnd,(RECT *)0x0,1);
  return;
}
