/*
 * Entry: 005560c7
 * Name: PlayerNameList::Delete
 * Namespace: PlayerNameList
 * Signature: void Delete(PlayerNameList * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall PlayerNameList::Delete(PlayerNameList *this)

{
  WPARAM wParam;
  LRESULT LVar1;
  
  wParam = SendMessageA((HWND)this->hwnd,0x188,0,0);
  if (wParam != 0xffffffff) {
    LVar1 = SendMessageA((HWND)this->hwnd,0x199,wParam,0);
    if (LVar1 != -1) {
      Delete(this,LVar1);
      SendMessageA((HWND)this->hwnd,0x182,wParam,0);
      SetWindowTextA((HWND)this->hwndMail," ");
      SetWindowTextA((HWND)this->hwndURL," ");
      SetWindowTextA((HWND)this->hwndDescription," ");
    }
  }
  SendMessageA((HWND)this->hwnd,0x186,0,0);
  SelectionChanged(this);
  return;
}
