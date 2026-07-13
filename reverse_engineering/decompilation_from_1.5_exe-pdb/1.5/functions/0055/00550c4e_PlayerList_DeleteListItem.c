/*
 * Entry: 00550c4e
 * Name: PlayerList::DeleteListItem
 * Namespace: PlayerList
 * Signature: void DeleteListItem(PlayerList * this, ushort param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall PlayerList::DeleteListItem(PlayerList *this,ushort param_1)

{
  LRESULT LVar1;
  uint uVar2;
  WPARAM wParam;
  
  wParam = 0;
  if ((HWND)this->hList != (HWND)0x0) {
    LVar1 = SendMessageA((HWND)this->hList,0x18b,0,0);
    this->l = LVar1;
    if (LVar1 != -1) {
      if (0 < LVar1) {
        do {
          uVar2 = SendMessageA((HWND)this->hList,0x199,wParam,0);
          this->l = uVar2;
          if (param_1 == uVar2) {
            LVar1 = SendMessageA((HWND)this->hList,0x182,wParam,0);
            this->l = LVar1;
            break;
          }
          wParam = wParam + 1;
        } while ((int)wParam < LVar1);
      }
      Redraw(this);
    }
  }
  return;
}
