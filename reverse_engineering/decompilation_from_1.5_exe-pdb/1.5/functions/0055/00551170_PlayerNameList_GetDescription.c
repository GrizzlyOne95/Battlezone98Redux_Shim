/*
 * Entry: 00551170
 * Name: PlayerNameList::GetDescription
 * Namespace: PlayerNameList
 * Signature: char * GetDescription(PlayerNameList * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

char * __thiscall PlayerNameList::GetDescription(PlayerNameList *this)

{
  WPARAM wParam;
  LRESULT LVar1;
  char *pcVar2;
  
  pcVar2 = "";
  wParam = SendMessageA((HWND)this->hwnd,0x188,0,0);
  if (wParam != 0xffffffff) {
    LVar1 = SendMessageA((HWND)this->hwnd,0x199,wParam,0);
    if (((LVar1 != -1) && (-1 < LVar1)) && (LVar1 < this->count)) {
      pcVar2 = this->description[LVar1];
    }
  }
  return pcVar2;
}
