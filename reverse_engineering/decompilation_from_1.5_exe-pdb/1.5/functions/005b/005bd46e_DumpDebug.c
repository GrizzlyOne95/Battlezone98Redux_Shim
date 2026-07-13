/*
 * Entry: 005bd46e
 * Name: DumpDebug
 * Namespace: Global
 * Signature: void DumpDebug(Proto * param_1, DumpState * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl DumpDebug(Proto *param_1,DumpState *param_2)

{
  void *pvVar1;
  int in_EAX;
  DumpState *unaff_EBX;
  DumpState *pDVar2;
  int iVar3;
  TString *unaff_ESI;
  int unaff_EDI;
  DumpState *pDVar4;
  undefined4 local_8;
  
  pDVar2 = (DumpState *)0x0;
  if (*(int *)(in_EAX + 0xc) == 0) {
    pDVar2 = *(DumpState **)(unaff_EDI + 0x30);
  }
  pvVar1 = *(void **)(unaff_EDI + 0x14);
  pDVar4 = pDVar2;
  DumpInt((int)pDVar2,(DumpState *)&unaff_ESI->tsv);
  DumpBlock(pvVar1,(int)pDVar2 << 2,pDVar4);
  iVar3 = 0;
  if (*(int *)(in_EAX + 0xc) == 0) {
    local_8 = *(int *)(unaff_EDI + 0x38);
  }
  else {
    local_8 = 0;
  }
  DumpInt(local_8,(DumpState *)&unaff_ESI->tsv);
  if (0 < local_8) {
    do {
      DumpString(unaff_ESI,unaff_EBX);
      pDVar2 = *(DumpState **)(iVar3 + 4 + *(int *)(unaff_EDI + 0x18));
      DumpInt((int)pDVar2,(DumpState *)&unaff_ESI->tsv);
      DumpInt(*(int *)(iVar3 + 8 + *(int *)(unaff_EDI + 0x18)),pDVar2);
      iVar3 = iVar3 + 0xc;
      local_8 = local_8 + -1;
    } while (local_8 != 0);
  }
  iVar3 = 0;
  if (*(int *)(in_EAX + 0xc) == 0) {
    local_8 = *(int *)(unaff_EDI + 0x24);
  }
  else {
    local_8 = 0;
  }
  DumpInt(local_8,(DumpState *)&unaff_ESI->tsv);
  if (0 < local_8) {
    do {
      DumpString(unaff_ESI,unaff_EBX);
      iVar3 = iVar3 + 1;
    } while (iVar3 < local_8);
  }
  return;
}
