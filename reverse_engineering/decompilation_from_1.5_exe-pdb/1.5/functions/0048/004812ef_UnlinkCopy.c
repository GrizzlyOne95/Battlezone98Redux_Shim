/*
 * Entry: 004812ef
 * Name: UnlinkCopy
 * Namespace: Global
 * Signature: void UnlinkCopy(_gas_object * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl UnlinkCopy(_gas_object *param_1)

{
  int iVar1;
  int iVar2;
  CopyInfo *pCVar3;
  CopyInfo *pCVar4;
  int unaff_EBX;
  CopyInfo *pCVar5;
  
  iVar1 = *(int *)(unaff_EBX + 0x6c);
  if (iVar1 != -1) {
    freeCopies = freeCopies + 1;
    pCVar3 = copies + iVar1;
    if (pCVar3->prev == -1) {
      pCVar4 = (CopyInfo *)0x0;
    }
    else {
      pCVar4 = copies + pCVar3->prev;
    }
    iVar2 = copies[iVar1].next;
    if (iVar2 == -1) {
      pCVar5 = (CopyInfo *)0x0;
    }
    else {
      pCVar5 = copies + iVar2;
    }
    if (pCVar4 != (CopyInfo *)0x0) {
      pCVar4->next = iVar2;
    }
    if (pCVar5 != (CopyInfo *)0x0) {
      pCVar5->prev = pCVar3->prev;
    }
    pCVar3->prev = -1;
    copies[iVar1].count = 0;
    copies[iVar1].go = (_gas_object *)0x0;
    copies[iVar1].next = freeCopy;
    freeCopy = *(int *)(unaff_EBX + 0x6c);
    *(undefined4 *)(unaff_EBX + 0x6c) = 0xffffffff;
  }
  return;
}
