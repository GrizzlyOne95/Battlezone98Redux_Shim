/*
 * Entry: 0055064b
 * Name: ServerList::DeleteListItem
 * Namespace: ServerList
 * Signature: void DeleteListItem(ServerList * this, Server * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: _alloca_probe_16 replaced with injection: alloca_probe */
/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* WARNING: Unable to track spacebase fully for stack */

void __thiscall ServerList::DeleteListItem(ServerList *this,Server *param_1)

{
  int iVar1;
  char *pcVar2;
  Server *pSVar3;
  LRESULT LVar4;
  undefined4 auStack_24 [2];
  UINT UStack_1c;
  WPARAM WStack_18;
  LPARAM LStack_14;
  
  pSVar3 = param_1;
  do {
    pcVar2 = pSVar3->caName;
    pSVar3 = (Server *)(pSVar3->caName + 1);
  } while (*pcVar2 != '\0');
  LStack_14 = 0x550674;
  iVar1 = -(int)((int)pSVar3 + (2 - (int)(param_1->caName + 1)));
  *(Server **)((int)&LStack_14 + iVar1) = param_1;
  *(char **)((int)&WStack_18 + iVar1) = "%s ";
  *(undefined1 **)((int)&UStack_1c + iVar1) = &stack0xfffffff0 + iVar1;
  *(undefined4 *)((int)auStack_24 + iVar1 + 4) = 0x550685;
  sprintf(*(char **)((int)&UStack_1c + iVar1),*(char **)((int)&WStack_18 + iVar1));
  *(undefined1 **)((int)&LStack_14 + iVar1) = &stack0xfffffff0 + iVar1;
  *(undefined4 *)((int)&WStack_18 + iVar1) = 0xffffffff;
  *(undefined4 *)((int)&UStack_1c + iVar1) = 399;
  *(HWND__ **)((int)auStack_24 + iVar1 + 4) = this->hList;
  *(undefined4 *)((int)auStack_24 + iVar1) = 0x55069b;
  LVar4 = SendMessageA(*(HWND *)((int)auStack_24 + iVar1 + 4),*(UINT *)((int)&UStack_1c + iVar1),
                       *(WPARAM *)((int)&WStack_18 + iVar1),*(LPARAM *)((int)&LStack_14 + iVar1));
  this->l = LVar4;
  if (LVar4 != -1) {
    *(undefined4 *)((int)&LStack_14 + iVar1) = 0;
    *(LRESULT *)((int)&WStack_18 + iVar1) = LVar4;
    *(undefined4 *)((int)&UStack_1c + iVar1) = 0x182;
    *(HWND__ **)((int)auStack_24 + iVar1 + 4) = this->hList;
    *(undefined4 *)((int)auStack_24 + iVar1) = 0x5506b0;
    LVar4 = SendMessageA(*(HWND *)((int)auStack_24 + iVar1 + 4),*(UINT *)((int)&UStack_1c + iVar1),
                         *(WPARAM *)((int)&WStack_18 + iVar1),*(LPARAM *)((int)&LStack_14 + iVar1));
    this->l = LVar4;
    *(undefined4 *)((int)&LStack_14 + iVar1) = 0x5506ba;
    Redraw(this);
  }
  return;
}
