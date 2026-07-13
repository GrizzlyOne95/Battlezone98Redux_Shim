/*
 * Entry: 00559306
 * Name: PlayerList::GetNameSelectedPlayers
 * Namespace: PlayerList
 * Signature: char * GetNameSelectedPlayers(PlayerList * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

char * __thiscall PlayerList::GetNameSelectedPlayers(PlayerList *this)

{
  WPARAM wParam;
  LRESULT LVar1;
  Player *pPVar2;
  
  wParam = SendMessageA((HWND)this->hList,0x188,0,0);
  this->l = wParam;
  if (wParam != 0xffffffff) {
    LVar1 = SendMessageA((HWND)this->hList,0x199,wParam,0);
    this->l = LVar1;
    pPVar2 = FindPlayer(this,(ushort)LVar1);
    if (pPVar2 != (Player *)0x0) {
      return pPVar2->caName;
    }
  }
  return (char *)0x0;
}
