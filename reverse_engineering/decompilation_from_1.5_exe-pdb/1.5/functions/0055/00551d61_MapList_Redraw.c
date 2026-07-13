/*
 * Entry: 00551d61
 * Name: MapList::Redraw
 * Namespace: MapList
 * Signature: void Redraw(MapList * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall MapList::Redraw(MapList *this)

{
  InvalidateRect((HWND)this->hwnd,(RECT *)0x0,1);
  UpdateWindow((HWND)this->hwnd);
  return;
}
