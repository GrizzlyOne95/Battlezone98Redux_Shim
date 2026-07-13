/*
 * Entry: 0055236d
 * Name: MapList::BltBitmap
 * Namespace: MapList
 * Signature: void BltBitmap(MapList * this, HDC__ * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall MapList::BltBitmap(MapList *this,HDC__ *param_1)

{
  if (this->shellBitmap != (ShellBitmap *)0x0) {
    ShellBitmap::BltBitmap(this->shellBitmap,param_1);
    return;
  }
  return;
}
