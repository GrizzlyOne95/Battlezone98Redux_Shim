/*
 * Entry: 00551fcd
 * Name: MapList::SetBitmap
 * Namespace: MapList
 * Signature: void SetBitmap(MapList * this, char * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: _alloca_probe_16 replaced with injection: alloca_probe */
/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* WARNING: Unable to track spacebase fully for stack */

void __thiscall MapList::SetBitmap(MapList *this,char *param_1)

{
  char cVar1;
  int iVar2;
  int iVar3;
  char *pcVar4;
  int iVar5;
  ShellBitmap *pSVar6;
  undefined4 uStack_30;
  int aiStack_2c [2];
  int aiStack_24 [2];
  
  pSVar6 = this->shellBitmap;
  if (pSVar6 != (ShellBitmap *)0x0) {
    ShellBitmap::~ShellBitmap(pSVar6);
    aiStack_24[1] = 0x551ff5;
    operator_delete(pSVar6);
  }
  this->shellBitmap = (ShellBitmap *)0x0;
  pcVar4 = param_1;
  do {
    cVar1 = *pcVar4;
    pcVar4 = pcVar4 + 1;
  } while (cVar1 != '\0');
  iVar2 = -(int)(pcVar4 + (5 - (int)(param_1 + 1)));
  *(char **)(&stack0xffffffe4 + iVar2) = param_1;
  *(char **)((int)aiStack_24 + iVar2 + 4) = "%s.bmp";
  *(undefined1 **)((int)aiStack_24 + iVar2) = &stack0xffffffe8 + iVar2;
  *(undefined4 *)((int)aiStack_2c + iVar2 + 4) = 0x552029;
  sprintf(*(char **)((int)aiStack_24 + iVar2),*(char **)((int)aiStack_24 + iVar2 + 4));
  *(undefined4 *)(&stack0xffffffe4 + iVar2) = 0x552034;
  iVar3 = -(int)(pcVar4 + (0xf - (int)(param_1 + 1)));
  *(undefined1 **)(&stack0xffffffe4 + iVar3 + iVar2) = &stack0xffffffe8 + iVar2;
  *(char **)((int)aiStack_24 + iVar3 + iVar2 + 4) = "bitmap\\%s";
  *(undefined1 **)((int)aiStack_24 + iVar3 + iVar2) = &stack0xffffffe8 + iVar3 + iVar2;
  *(undefined4 *)((int)aiStack_2c + iVar3 + iVar2 + 4) = 0x552041;
  sprintf(*(char **)((int)aiStack_24 + iVar3 + iVar2),
          *(char **)((int)aiStack_24 + iVar3 + iVar2 + 4));
  *(undefined4 *)((int)aiStack_2c + iVar3 + iVar2 + 4) = 4;
  *(undefined1 **)((int)aiStack_2c + iVar3 + iVar2) = &stack0xffffffe8 + iVar3 + iVar2;
  *(undefined4 *)((int)&uStack_30 + iVar3 + iVar2) = 0x55204a;
  iVar5 = _access(*(char **)((int)aiStack_2c + iVar3 + iVar2),
                  *(int *)((int)aiStack_2c + iVar3 + iVar2 + 4));
  if (iVar5 != 0) {
    *(undefined1 **)(&stack0xffffffe4 + iVar3 + iVar2) = &stack0xffffffe8 + iVar2;
    *(undefined4 *)((int)aiStack_24 + iVar3 + iVar2 + 4) = 0x552059;
    iVar5 = ItemExists(*(char **)(&stack0xffffffe4 + iVar3 + iVar2));
    if (iVar5 == 0) goto LAB_0055207f;
  }
  *(undefined4 *)(&stack0xffffffe4 + iVar3 + iVar2) = 0x20;
  *(undefined4 *)((int)aiStack_24 + iVar3 + iVar2 + 4) = 0x552065;
  pSVar6 = operator_new(*(uint *)(&stack0xffffffe4 + iVar3 + iVar2));
  if (pSVar6 == (ShellBitmap *)0x0) {
    pSVar6 = (ShellBitmap *)0x0;
  }
  else {
    *(ulong *)(&stack0xffffffe4 + iVar3 + iVar2) = (this->mop).dwCallback;
    *(int *)((int)aiStack_24 + iVar3 + iVar2 + 4) = this->yPos;
    *(undefined1 **)((int)aiStack_24 + iVar3 + iVar2) = &stack0xffffffe8 + iVar3 + iVar2;
    *(undefined4 *)((int)aiStack_2c + iVar3 + iVar2 + 4) = 0x552078;
    pSVar6 = ShellBitmap::ShellBitmap
                       (pSVar6,*(char **)((int)aiStack_24 + iVar3 + iVar2),
                        *(int *)((int)aiStack_24 + iVar3 + iVar2 + 4),
                        *(int *)(&stack0xffffffe4 + iVar3 + iVar2));
  }
  this->shellBitmap = pSVar6;
LAB_0055207f:
  *(undefined4 *)(&stack0xffffffe4 + iVar3 + iVar2) = 0;
  *(long **)((int)aiStack_24 + iVar3 + iVar2 + 4) = &(this->rect).top;
  *(HWND__ **)((int)aiStack_24 + iVar3 + iVar2) = this->hDlg;
  *(undefined4 *)((int)aiStack_2c + iVar3 + iVar2 + 4) = 0x55208e;
  InvalidateRect(*(HWND *)((int)aiStack_24 + iVar3 + iVar2),
                 *(RECT **)((int)aiStack_24 + iVar3 + iVar2 + 4),
                 *(BOOL *)(&stack0xffffffe4 + iVar3 + iVar2));
  return;
}
