/*
 * Entry: 00550b58
 * Name: PlayerList::Redraw
 * Namespace: PlayerList
 * Signature: void Redraw(PlayerList * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall PlayerList::Redraw(PlayerList *this)

{
  if ((HWND)this->hList != (HWND)0x0) {
    InvalidateRect((HWND)this->hList,(RECT *)0x0,1);
  }
  return;
}
