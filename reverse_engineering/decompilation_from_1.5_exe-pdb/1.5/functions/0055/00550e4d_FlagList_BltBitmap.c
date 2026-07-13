/*
 * Entry: 00550e4d
 * Name: FlagList::BltBitmap
 * Namespace: FlagList
 * Signature: void BltBitmap(FlagList * this, HDC__ * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall FlagList::BltBitmap(FlagList *this,HDC__ *param_1)

{
  if (this->shellBitmap != (ShellBitmap *)0x0) {
    ShellBitmap::BltBitmap(this->shellBitmap,param_1);
    return;
  }
  return;
}
