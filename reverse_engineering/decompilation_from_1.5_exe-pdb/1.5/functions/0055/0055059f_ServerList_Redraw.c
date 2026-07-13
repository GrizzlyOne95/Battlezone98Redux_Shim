/*
 * Entry: 0055059f
 * Name: ServerList::Redraw
 * Namespace: ServerList
 * Signature: void Redraw(ServerList * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall ServerList::Redraw(ServerList *this)

{
  InvalidateRect((HWND)this->hParent,(RECT *)&this->rList,1);
  InvalidateRect((HWND)this->hList,(RECT *)0x0,1);
  return;
}
