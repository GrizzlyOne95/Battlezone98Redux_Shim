/*
 * Entry: 00551e24
 * Name: MapList::Filter
 * Namespace: MapList
 * Signature: void Filter(MapList * this, int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall MapList::Filter(MapList *this,int param_1)

{
  bool bVar1;
  WPARAM wParam;
  int iVar2;
  int local_4;
  
  iVar2 = 0;
  bVar1 = false;
  SendMessageA((HWND)this->hwnd,0x184,0,0);
  local_4 = 0;
  if (0 < (int)this->s) {
    do {
      if (((mapFilter[param_1].type == '\0') ||
          (mapFilter[param_1].type == *(char *)((int)&this[1].hPlayerList[4].unused + iVar2))) &&
         ((mapFilter[param_1].players == '\0' ||
          ((int)mapFilter[param_1].players == *(int *)((int)&this[1].hPlayerList[2].unused + iVar2))
          ))) {
        bVar1 = true;
        wParam = SendMessageA((HWND)this->hwnd,0x180,0,
                              *(LPARAM *)((int)&this[1].hPlayerList[3].unused + iVar2));
        if ((wParam != 0xffffffff) && (wParam != 0xfffffffe)) {
          SendMessageA((HWND)this->hwnd,0x19a,wParam,local_4);
        }
      }
      local_4 = local_4 + 1;
      iVar2 = iVar2 + 0x14;
    } while (local_4 < (int)this->s);
    if (bVar1) {
      SendMessageA((HWND)this->hwnd,0x186,0,0);
    }
  }
  return;
}
