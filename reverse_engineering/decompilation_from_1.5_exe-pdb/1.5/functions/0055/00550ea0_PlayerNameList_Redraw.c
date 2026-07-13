/*
 * Entry: 00550ea0
 * Name: PlayerNameList::Redraw
 * Namespace: PlayerNameList
 * Signature: void Redraw(PlayerNameList * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall PlayerNameList::Redraw(PlayerNameList *this)

{
  InvalidateRect((HWND)this->hwnd,(RECT *)0x0,1);
  return;
}
