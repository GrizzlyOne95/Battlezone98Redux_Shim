/*
 * Entry: 00555e57
 * Name: FlagList::~FlagList
 * Namespace: FlagList
 * Signature: void ~FlagList(FlagList * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall FlagList::~FlagList(FlagList *this)

{
  ShellBitmap *this_00;
  
  if (this->s != (_s *)0x0) {
    free(this->s);
  }
  this_00 = this->shellBitmap;
  if (this_00 != (ShellBitmap *)0x0) {
    ShellBitmap::~ShellBitmap(this_00);
    operator_delete(this_00);
  }
  return;
}
