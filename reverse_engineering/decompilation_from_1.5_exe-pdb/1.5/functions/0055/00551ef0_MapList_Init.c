/*
 * Entry: 00551ef0
 * Name: MapList::Init
 * Namespace: MapList
 * Signature: void Init(MapList * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall MapList::Init(MapList *this)

{
  ShellBitmap *this_00;
  int iVar1;
  int iVar2;
  
  iVar2 = 0;
  SendMessageA((HWND)this->hwnd,0x184,0,0);
  if (this->s != (_s *)0x0) {
    iVar1 = 0;
    if (0 < (int)this->s) {
      do {
        free(*(void **)((int)&(this[1].hPlayerList)->unused + iVar2));
        free(*(void **)((int)&this[1].hPlayerList[3].unused + iVar2));
        iVar1 = iVar1 + 1;
        iVar2 = iVar2 + 0x14;
      } while (iVar1 < (int)this->s);
    }
    free(this[1].hPlayerList);
  }
  this_00 = this->shellBitmap;
  this[1].hPlayerList = (HWND__ *)0x0;
  this->s = (_s *)0x0;
  if (this_00 != (ShellBitmap *)0x0) {
    ShellBitmap::~ShellBitmap(this_00);
    operator_delete(this_00);
  }
  this->shellBitmap = (ShellBitmap *)0x0;
  return;
}
