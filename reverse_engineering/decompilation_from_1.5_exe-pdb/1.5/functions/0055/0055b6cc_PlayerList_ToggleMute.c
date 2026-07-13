/*
 * Entry: 0055b6cc
 * Name: PlayerList::ToggleMute
 * Namespace: PlayerList
 * Signature: bool ToggleMute(PlayerList * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall PlayerList::ToggleMute(PlayerList *this)

{
  bool bVar1;
  WPARAM wParam;
  LRESULT LVar2;
  
  if ((HWND)this->hList != (HWND)0x0) {
    wParam = SendMessageA((HWND)this->hList,0x188,0,0);
    this->l = wParam;
    if (wParam != 0xffffffff) {
      LVar2 = SendMessageA((HWND)this->hList,0x199,wParam,0);
      this->l = LVar2;
      bVar1 = ToggleMute(this,(ushort)LVar2);
      return bVar1;
    }
  }
  return false;
}
