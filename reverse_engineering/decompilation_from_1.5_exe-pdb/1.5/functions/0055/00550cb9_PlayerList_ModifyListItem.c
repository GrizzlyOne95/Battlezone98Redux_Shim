/*
 * Entry: 00550cb9
 * Name: PlayerList::ModifyListItem
 * Namespace: PlayerList
 * Signature: void ModifyListItem(PlayerList * this, Player * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall PlayerList::ModifyListItem(PlayerList *this,Player *param_1)

{
  if ((HWND)this->hList != (HWND)0x0) {
    InvalidateRect((HWND)this->hList,(RECT *)0x0,1);
  }
  return;
}
